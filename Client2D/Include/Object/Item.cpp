
#include "Item.h"
#include "ItemPickup.h"
#include "Player2D.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneMode.h"

CItem::CItem()	:
	m_Type(Item_Type::None),
	m_CompleteAnim(false),
	m_MinCheck(false),
	m_MaxCheck(false),
	m_DirY(-1.f),
	m_AnimSpeed(300.f),
	m_Bottom(0.f),
	m_BottomMin(0.f),
	m_BottomMax(0.f)
{
	SetTypeID<CItem>();
}

CItem::CItem(const CItem& obj)	:
	CGameObject(obj)
{
	SetTypeID<CItem>();

	m_Body = (CColliderBox2D*)FindComponent("Body");

	m_Type = obj.m_Type;
	m_CompleteAnim = false;
	m_MinCheck = false;
	m_MaxCheck = false;
	m_DirY = obj.m_DirY;
	m_AnimSpeed = obj.m_AnimSpeed;
	m_Bottom = 0.f;
	m_BottomMin = obj.m_BottomMin;
	m_BottomMax = obj.m_BottomMax;
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

void CItem::First()
{
	CGameObject::First();

	m_BottomMin = GetWorldPos().y - 20.f;
	m_BottomMax = GetWorldPos().y - 30.f;
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

void CItem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_CompleteAnim)
	{
		Vector3	Pos = GetWorldPos();

		m_Bottom = m_DirY * m_AnimSpeed * DeltaTime;

		AddWorldPos(0.f, m_Bottom, 0.f);

		if (!m_MaxCheck)
		{
			if (Pos.y <= m_BottomMax)
			{
				m_MaxCheck = true;

				SetWorldPos(Pos.x, m_BottomMax, 0.f);

				m_DirY = 1.f;
			}
		}

		else
		{
			if (!m_MinCheck)
			{
				if (Pos.y >= m_BottomMin)
				{
					m_MinCheck = true;

					SetWorldPos(Pos.x, m_BottomMin, 0.f);

					m_DirY = -1.f;
				}
			}

			else
			{
				if (Pos.y <= m_BottomMax)
				{
					m_MaxCheck = true;

					SetWorldPos(Pos.x, m_BottomMax, 0.f);

					m_CompleteAnim = true;
				}
			}
		}
	}
}

CItem* CItem::Clone()
{
	return DBG_NEW CItem(*this);
}

void CItem::Destroy()
{
	CGameObject::Destroy();

	m_Body->Enable(false);

	CItemPickup* Effect = m_Scene->CreateGameObject<CItemPickup>("PickupEffect");
	
	Effect->SetWorldPos(GetWorldPos());
}

void CItem::OnCollisionBegin(const CollisionResult& result)
{
	if (!m_CompleteAnim)
		return;

	if (result.Dest->GetCollisionProfile()->Channel == Collision_Channel::Player)
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

		Destroy();
	}
}
