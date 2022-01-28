
#include "BubbleParticle.h"
#include "Component/ParticleComponent.h"

CBubbleParticle::CBubbleParticle()
{
	SetTypeID<CBubbleParticle>();
}

CBubbleParticle::CBubbleParticle(const CBubbleParticle& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleComponent*)FindComponent("Particle");
}

CBubbleParticle::~CBubbleParticle()
{
}

bool CBubbleParticle::Init()
{
	m_Particle = CreateComponent<CParticleComponent>("Particle");

	SetRootComponent(m_Particle);

	m_Particle->SetParticle("Bubble");
	//m_Particle->SetSpawnTime(0.1f);

	return true;
}

CBubbleParticle* CBubbleParticle::Clone()
{
	return DBG_NEW CBubbleParticle(*this);
}
