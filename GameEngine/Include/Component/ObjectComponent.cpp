
#include "ObjectComponent.h"

CObjectComponent::CObjectComponent()
{
	SetTypeID<CObjectComponent>();
	m_eComponentType = Component_Type::ObjectComponent;
}

CObjectComponent::CObjectComponent(const CObjectComponent& com) :
	CComponent(com)
{
	*this = com;
}

CObjectComponent::~CObjectComponent()
{
}
