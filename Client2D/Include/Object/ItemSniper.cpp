
#include "ItemSniper.h"
#include "Player2D.h"

CItemSniper::CItemSniper()
{
	SetTypeID<CItemSniper>();
}

CItemSniper::CItemSniper(const CItemSniper& obj) :
	CItem(obj)
{
	SetTypeID<CItemSniper>();

	m_Sprite = (CSpriteComponent*)FindComponent("Sniper");
}

CItemSniper::~CItemSniper()
{
}

bool CItemSniper::Init()
{
	if (!CItem::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("Sniper");
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Sniper", TEXT("Item/Sniper.png"));

	m_Body->SetRelativeScale(90.f, 27.f, 1.f);
	m_Body->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

CItemSniper* CItemSniper::Clone()
{
	return DBG_NEW CItemSniper(*this);
}

void CItemSniper::OnCollisionBegin(const CollisionResult& result)
{
	CItem::OnCollisionBegin(result);

	if (result.Dest->GetName() == "Player")
	{
		if (!m_Player->HasWeaponSniper())
			m_Player->AddWeaponSniper();

		m_Scene->GetResource()->SoundPlay("WeaponPickup");
	}
}