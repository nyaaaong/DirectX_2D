
#include "ParticleComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CParticleComponent::CParticleComponent()
{
	SetTypeID<CParticleComponent>();
	m_Render = true;
}

CParticleComponent::CParticleComponent(const CParticleComponent& com) :
	CSceneComponent(com)
{
}

CParticleComponent::~CParticleComponent()
{
}

void CParticleComponent::Start()
{
	CSceneComponent::Start();
}

bool CParticleComponent::Init()
{
	return true;
}

void CParticleComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CParticleComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CParticleComponent::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CParticleComponent::Render()
{
	CSceneComponent::Render();
}

void CParticleComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CParticleComponent* CParticleComponent::Clone()
{
	return DBG_NEW CParticleComponent(*this);
}

void CParticleComponent::Save(FILE* File)
{
	CSceneComponent::Save(File);
}

void CParticleComponent::Load(FILE* File)
{
	CSceneComponent::Load(File);
}
