
#include "ShaderInfo.fx"

cbuffer	ParticleCBuffer : register(b11)
{
	uint	g_ParticleSpawnEnable;	// ��ƼŬ ��������
	float3	g_ParticleStartMin;		// ��ƼŬ�� ������ ������ Min
	float3	g_ParticleStartMax;		// ��ƼŬ�� ������ ������ Max
	uint	g_ParticleSpawnCountMax;	// ������ ��ƼŬ�� �ִ�
	float3	g_ParticleScaleMin;		// ������ ��ƼŬ ũ���� Min
	float	g_ParticleLifeTimeMin;	// ������ ��ƼŬ�� ������� �ּҽð�
	float3	g_ParticleScaleMax;		// ������ ��ƼŬ ũ���� Max
	float	g_ParticleLifeTimeMax;	// ������ ��ƼŬ�� ������� �ִ�ð�
	float4	g_ParticleColorMin;		// ������ ��ƼŬ�� ���� Min
	float4	g_ParticleColorMax;		// ������ ��ƼŬ�� ���� Max
	float	g_ParticleSpeedMin;		// ��ƼŬ�� �ּ� �̵��ӵ�
	float	g_ParticleSpeedMax;		// ��ƼŬ�� �ִ� �̵��ӵ�
	int		g_ParticleMove;			// �̵��� �ϴ��� ���ϴ���
	int		g_ParticleGravity;		// �߷� ������ �޴��� �ȹ޴���
	float3	g_ParticleMoveDir;		// �̵��� �Ѵٸ� ������ �� �̵� ����
	int		g_Particle2D;			// 2D�� ��ƼŬ����
	float3	g_ParticleMoveAngle;	// �̵��� �Ѵٸ� ������ �� �������κ��� x, y, z �� ����� ������ŭ Ʋ���� ������ ������ ���Ѵ�.
	float	g_ParticleEmpty;
};

#define	GRAVITY	9.8f

struct ParticleInfo
{
	float3	WorldPos;
	float3	Dir;
	float	Speed;
	float	LifeTime;
	float	LifeTimeMax;
	int		Alive;
	float	FallTime;
	float	FallStartY;
};

struct ParticleInfoShared
{
	uint	SpawnEnable;

	float3	ScaleMin;
	float3	ScaleMax;

	float4	ColorMin;
	float4	ColorMax;

	int		GravityEnable;
};

RWStructuredBuffer<ParticleInfo>		g_ParticleArray	: register(u0);
RWStructuredBuffer<ParticleInfoShared>	g_ParticleShare	: register(u1);

[numthreads(64, 1, 1)]	// ������ �׷� ������ ���� �����Ѵ�.
void ParticleUpdate(uint3 ThreadID : SV_DispatchThreadID)
{
	g_ParticleShare[0].SpawnEnable = g_ParticleSpawnEnable;
	g_ParticleShare[0].ScaleMin = g_ParticleScaleMin;
	g_ParticleShare[0].ScaleMax = g_ParticleScaleMax;
	g_ParticleShare[0].ColorMin = g_ParticleColorMin;
	g_ParticleShare[0].ColorMax = g_ParticleColorMax;
	g_ParticleShare[0].GravityEnable = g_ParticleGravity;

	// ���۵Ǵ� �������� ���� �����Ǵ� ��ƼŬ�� �ִ� �� ���� ũ�ų� ���ٸ�
	// �߸��� �ε����� �����ϱ� ������ ó���� �����ش�.
	if (g_ParticleSpawnCountMax <= ThreadID.x)
		return;

	// ��ƼŬ�� ����ִ� ��ƼŬ���� �Ǵ��Ѵ�.
	if (g_ParticleArray[ThreadID.x].Alive == 0)
	{
		int	SpawnEnable = g_ParticleShare[0].SpawnEnable;
		int	Exchange = 0;

		if (g_ParticleShare[0].SpawnEnable == 1)
		{
			int	InputValue = SpawnEnable - 1;

			// �Լ��� ���ڴ� in, in, out���� �����Ǿ� �ִ�.
			// in�� �Ϲ������� ������ ���� �Ѱ��ٶ� ����Ѵ�.
			// out�� ����¥�� ���۷���ó�� ������� ������ ������ �޾ƿö� ����Ѵ�.
			InterlockedExchange(g_ParticleShare[0].SpawnEnable, InputValue, Exchange);

			if (Exchange == SpawnEnable)
				g_ParticleArray[ThreadID.x].Alive = 1;
		}

		if (g_ParticleArray[ThreadID.x].Alive == 0)
			return;

		// ����� �ϴ� ��ƼŬ�̶�� ��ƼŬ ���������� ������.
		float	key = ThreadID.x / g_ParticleSpawnCountMax;

		// Rand�� 0 ~ 25������ ���̴�.
		float3	RandomPos = float3(Rand(key), Rand(key * 2.f), Rand(key * 3.f));

		RandomPos /= 25.f;

		float3	StartRange = g_ParticleStartMax - g_ParticleStartMin;

		g_ParticleArray[ThreadID.x].WorldPos = RandomPos * StartRange + g_ParticleStartMin;

		g_ParticleArray[ThreadID.x].FallTime = 0.f;
		g_ParticleArray[ThreadID.x].FallStartY = g_ParticleArray[ThreadID.x].WorldPos.y;

		g_ParticleArray[ThreadID.x].LifeTime = 0.f;
		g_ParticleArray[ThreadID.x].LifeTimeMax = RandomPos.x * (g_ParticleLifeTimeMax - g_ParticleLifeTimeMin) + g_ParticleLifeTimeMin;

		if (g_ParticleMove == 1)
		{
			g_ParticleArray[ThreadID.x].Speed = RandomPos.x * (g_ParticleSpeedMax - g_ParticleSpeedMin) + g_ParticleSpeedMin;
			g_ParticleArray[ThreadID.x].Dir = normalize(RandomPos.xyz * 2.f - 1.f + g_ParticleMoveDir);

			// ������ ó���Ѵٸ� x, y, z �� ������ ������ 3�� ������ ���� ������ �߽����� ȸ���� ����� ���ؼ�'
			// ȸ���� ������ �����ֵ��� �Ѵ�.
		}
	}

	// ���� ������ �Ǿ� �ִ� ��ƼŬ�� ���
	else
	{
		g_ParticleArray[ThreadID.x].LifeTime += g_DeltaTime;

		if (g_ParticleMove == 1)
		{
			g_ParticleArray[ThreadID.x].WorldPos += g_ParticleArray[ThreadID.x].Dir *
				g_ParticleArray[ThreadID.x].Speed * g_DeltaTime;
		}

		// �߷� ����
		if (g_ParticleShare[0].GravityEnable)
		{
		}

		if (g_ParticleArray[ThreadID.x].LifeTime >= g_ParticleArray[ThreadID.x].LifeTimeMax)
		{
			g_ParticleArray[ThreadID.x].Alive = 0;
		}
	}
}

struct VertexParticle
{
	float3	Pos	: POSITION;
	uint InstanceID : SV_InstanceID;	// �������ۿ� ���� �־��ִ°��� �ƴϴ�.
};

struct VertexParticleOutput
{
	uint	InstanceID : TEXCOORD;
};

VertexParticleOutput ParticleVS(VertexParticle input)
{
	VertexParticleOutput	output = (VertexParticleOutput)0;

	output.InstanceID = input.InstanceID;

	return output;
}

struct GeometryParticleOutput
{
	float4	Pos : SV_POSITION;
	float4	Color : COLOR;
	float2	UV	: TEXCOORD;
	float4	ProjPos : POSITION;
};

// in : ���� �Լ� ������ �Ѱ��ٶ�
// out : �Լ��ȿ��� ����� �Ѱܹ�����. �� �Լ� �ȿ��� �� ���� ����� ������ �� �� ����.
// inout : �׳� ���۷���.
[maxvertexcount(6)]
void ParticleGS(point VertexParticleOutput input[1],
	inout TriangleStream<GeometryParticleOutput> output)
{
}

PSOutput_Single ParticlePS(GeometryParticleOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	return output;
}
