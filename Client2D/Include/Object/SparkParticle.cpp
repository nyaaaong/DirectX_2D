
#include "SparkParticle.h"
#include "Component/ParticleComponent.h"

CSparkParticle::CSparkParticle()	:
	m_LifeTime(0.f),
	m_LifeTimeMax(0.5f)
{
	SetTypeID<CSparkParticle>();
}

CSparkParticle::CSparkParticle(const CSparkParticle& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleComponent*)FindComponent("Particle");

	m_LifeTime = 0.f;
	m_LifeTimeMax = obj.m_LifeTimeMax;
}

CSparkParticle::~CSparkParticle()
{
}

bool CSparkParticle::Init()
{
	m_Particle = CreateComponent<CParticleComponent>("Particle");

	SetRootComponent(m_Particle);

	m_Particle->SetParticle("Spark");

	return true;
}

void CSparkParticle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_LifeTime += DeltaTime;

	if (m_LifeTime >= m_LifeTimeMax)
		Destroy();
}

CSparkParticle* CSparkParticle::Clone()
{
	return DBG_NEW CSparkParticle(*this);
}
