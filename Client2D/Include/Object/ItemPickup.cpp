
#include "ItemPickup.h"
#include "ItemPickupAnim.h"
#include "Component/SpriteComponent.h"

CItemPickup::CItemPickup()
{
	SetTypeID<CItemPickup>();
}

CItemPickup::CItemPickup(const CItemPickup& obj)	:
	CGameObject(obj)
{
	SetTypeID<CItemPickup>();
}

CItemPickup::~CItemPickup()
{
}

bool CItemPickup::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("Pickup");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->CreateAnimationInstance<CItemPickupAnim>();

	SetRootComponent(m_Sprite);

	return true;
}

void CItemPickup::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Sprite->IsEnd())
	{
		m_Sprite->SetRender(false);

		Destroy();
	}
}

CItemPickup* CItemPickup::Clone()
{
	return DBG_NEW CItemPickup(*this);
}
