
#include "SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CSpriteComponent::CSpriteComponent()
{
	SetTypeID<CSpriteComponent>();
	m_Render = true;
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& com)	:
	CSceneComponent(com)
{
	m_Mesh = com.m_Mesh;
}

CSpriteComponent::~CSpriteComponent()
{
}

void CSpriteComponent::Start()
{
	CSceneComponent::Start();
}

void CSpriteComponent::SetMaterial(CMaterial* Material)
{
	m_Material = Material->Clone();
}

bool CSpriteComponent::Init()
{
	m_Mesh = (CSpriteMesh*)m_Scene->GetResource()->FindMesh("SpriteMesh");
	SetMaterial(m_Scene->GetResource()->FindMaterial("BaseTexture"));

	SetMeshSize(1.f, 1.f, 0.f);

	return true;
}

void CSpriteComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CSpriteComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CSpriteComponent::PrevRender()
{
	CSceneComponent::PrevRender();
}

void CSpriteComponent::Render()
{
	CSceneComponent::Render();

	m_Material->Render();

	m_Mesh->Render();
}

void CSpriteComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CSpriteComponent* CSpriteComponent::Clone()
{
	return new CSpriteComponent(*this);
}
