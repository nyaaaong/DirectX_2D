
#include "ShaderInfo.fx"

cbuffer	ParticleCBuffer : register(b11)
{
	uint	g_ParticleSpawnCount;	// 현재 파티클이 생성된 수
	float3	g_ParticleStartMin;		// 파티클이 생성될 영역의 Min
	float3	g_ParticleStartMax;		// 파티클이 생성될 영역의 Max
	uint	g_ParticleSpawnCountMax;	// 생성될 파티클의 최대
	float3	g_ParticleScaleMin;		// 생성될 파티클 크기의 Min
	float	g_ParticleLifeTimeMin;	// 생성될 파티클이 살아있을 최소시간
	float3	g_ParticleScaleMax;		// 새성될 파티클 크기의 Max
	float	g_ParticleLifeTimeMax;	// 생성될 파티클이 살아있을 최대시간
	float4	g_ParticleColorMin;		// 생성될 파티클의 색상 Min
	float4	g_ParticleColorMax;		// 생성될 파티클의 색상 Max
	float	g_ParticleSpeedMin;		// 파티클의 최소 이동속도
	float	g_ParticleSpeedMax;		// 파티클의 최대 이동속도
	int		g_ParticleMove;			// 이동을 하는지 안하는지
	int		g_ParticleGravity;		// 중력 적용을 받는지 안받는지
	float3	g_ParticleMoveDir;		// 이동을 한다면 기준이 될 이동 방향
	int		g_Particle2D;			// 2D용 파티클인지
	float3	g_ParticleMoveAngle;	// 이동을 한다면 기준이 될 방향으로부터 x, y, z 에 저장된 각도만큼 틀어진 랜덤한 방향을 구한다.
	float	g_Empty;
};

#define	GRAVITY	9.8f
