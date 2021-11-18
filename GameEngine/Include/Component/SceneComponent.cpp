
#include "SceneComponent.h"

CSceneComponent::CSceneComponent()	:
	m_bRender(false)
{
	SetTypeID<CSceneComponent>();
	m_eComponentType = Component_Type::SceneComponent;
}

CSceneComponent::CSceneComponent(const CSceneComponent& com)	:
	CComponent(com)
{
	*this = com;
}

CSceneComponent::~CSceneComponent()
{
}

bool CSceneComponent::Init()
{
	if (!CComponent::Init())
		return false;

	return true;
}

void CSceneComponent::Update(float fTime)
{
}

void CSceneComponent::PostUpdate(float fTime)
{
}

void CSceneComponent::PrevRender()
{
}

void CSceneComponent::Render()
{
}

void CSceneComponent::PostRender()
{
}

CSceneComponent* CSceneComponent::Clone()
{
	return new CSceneComponent(*this);
}
