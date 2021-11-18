
#include "Component.h"

CComponent::CComponent()	:
	m_pScene(nullptr),
	m_pObject(nullptr),
	m_eComponentType(Component_Type::ObjectComponent)
{
}

CComponent::CComponent(const CComponent& com)
{
	*this = com;
	m_iRefCount = 0;

	m_pObject = nullptr;
}

CComponent::~CComponent()
{
}

bool CComponent::Init()
{
	return true;
}
