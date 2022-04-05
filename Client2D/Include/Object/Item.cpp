
#include "Item.h"
#include "ItemPickup.h"
#include "Player2D.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneMode.h"

CItem::CItem()	:
	m_Type(Item_Type::None)
{
	SetTypeID<CItem>();
}

CItem::CItem(const CItem& obj)	:
	CGameObject(obj)
{
	SetTypeID<CItem>();

	m_Body = (CColliderBox2D*)FindComponent("Body");

	m_Type = obj.m_Type;
}

CItem::~CItem()
{
}

void CItem::Start()
{
	CGameObject::Start();

	CGameObject* Obj = CSceneManager::GetInst()->GetSceneMode()->GetPlayerObject();

	if (!Obj)
		ASSERT("if (!Obj)");

	m_Player = dynamic_cast<CPlayer2D*>(Obj);

	if (!m_Player)
		ASSERT("if (!m_Player)");
}

bool CItem::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->UseMouseCollision(false);
	m_Body->SetCollisionProfile("Item");

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CItem::OnCollisionBegin);

	return true;
}

CItem* CItem::Clone()
{
	return DBG_NEW CItem(*this);
}

void CItem::Destroy()
{
	CGameObject::Destroy();

	CItemPickup* Effect = m_Scene->CreateGameObject<CItemPickup>("PickupEffect");

	Effect->SetWorldPos(GetWorldPos());
}

void CItem::OnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{
		switch (m_Type)
		{
		case Item_Type::None:
			return;
		case Item_Type::Rifle:
			m_Player->AddWeaponRifle();
			m_Scene->GetResource()->SoundPlay("WeaponPickup");
			break;
		case Item_Type::Sniper:
			m_Player->AddWeaponSniper();
			m_Scene->GetResource()->SoundPlay("WeaponPickup");
			break;
		case Item_Type::Life:
			m_Player->AddHP(10.f);
			m_Scene->GetResource()->SoundPlay("ItemPickup");
			break;
		}

		CGameObject::Destroy();
	}
}
