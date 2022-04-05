
#include "ItemRifle.h"
#include "Player2D.h"

CItemRifle::CItemRifle()
{
	SetTypeID<CItemRifle>();
}

CItemRifle::CItemRifle(const CItemRifle& obj)	:
	CItem(obj)
{
	SetTypeID<CItemRifle>();

	m_Sprite = (CSpriteComponent*)FindComponent("Rifle");
}

CItemRifle::~CItemRifle()
{
}

bool CItemRifle::Init()
{
	if (!CItem::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("Rifle");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Rifle", TEXT("Item/Rifle.png"));

	m_Body->SetRelativeScale(81.f, 21.f, 1.f);
	m_Body->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

CItemRifle* CItemRifle::Clone()
{
	return DBG_NEW CItemRifle(*this);
}

void CItemRifle::OnCollisionBegin(const CollisionResult& result)
{
	CItem::OnCollisionBegin(result);

	if (result.Dest->GetName() == "Player")
	{
		if (!m_Player->HasWeaponRifle())
			m_Player->AddWeaponRifle();

		m_Scene->GetResource()->SoundPlay("WeaponPickup");
	}
}
