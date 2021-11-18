
#include "SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CSpriteComponent::CSpriteComponent()
{
	SetTypeID<CSpriteComponent>();
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& com)	:
	CSceneComponent(com)
{
	*this = com;
}

CSpriteComponent::~CSpriteComponent()
{
}

bool CSpriteComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	m_pMesh = dynamic_cast<CSpriteMesh*>(m_pScene->GetResource()->FindMesh("SpriteMesh"));
	m_pMaterial = m_pScene->GetResource()->FindMaterial("Color");

	return true;
}

void CSpriteComponent::Update(float fTime)
{
	CSceneComponent::Update(fTime);
}

void CSpriteComponent::PostUpdate(float fTime)
{
	CSceneComponent::PostUpdate(fTime);
}

void CSpriteComponent::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CSpriteComponent::Render()
{
	CSceneComponent::Render();
}

void CSpriteComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CSpriteComponent* CSpriteComponent::Clone()
{
	return new CSpriteComponent(*this);
}
