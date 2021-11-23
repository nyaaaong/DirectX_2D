
#include "Component.h"

CComponent::CComponent()	:
	m_Scene(nullptr),
	m_Object(nullptr),
	m_ComponentType(Component_Type::SceneComponent)
{
}

CComponent::CComponent(const CComponent& com)
{
	*this = com;
	m_RefCount = 0;

	m_Object = nullptr;
}

CComponent::~CComponent()
{
}

void CComponent::SetScene(CScene* Scene)
{
	m_Scene = Scene;
}

void CComponent::SetGameObject(CGameObject* Object)
{
	m_Object = Object;
}

bool CComponent::Init()
{
	return true;
}
