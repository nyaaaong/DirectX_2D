
#include "ShaderInfo.fx"

cbuffer	ParticleCBuffer : register(b11)
{
	uint	g_ParticleSpawnCount;	// ���� ��ƼŬ�� ������ ��
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
	float	g_Empty;
};

#define	GRAVITY	9.8f
