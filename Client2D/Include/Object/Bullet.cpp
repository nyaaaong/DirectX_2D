
#include "Bullet.h"
#include "Monster.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderCircle.h"

CBullet::CBullet() :
	m_Distance(600.f),
	m_Owner(nullptr),
	m_NeedChangeOwner(false)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Owner = obj.m_Owner;
	m_Distance = obj.m_Distance;
	m_NeedChangeOwner = false;

	m_Body = (CColliderCircle*)FindComponent("Body");
}

CBullet::~CBullet()
{
}

void CBullet::SetDamage(const CollisionResult& result)
{
	CColliderComponent* Src = result.Src;
	CColliderComponent* Dest = result.Dest;

	CGameObject* SrcObj = Src->GetGameObject();
	CGameObject* DestObj = Dest->GetGameObject();

	std::string SrcName = SrcObj->GetName();
	std::string DestName = DestObj->GetName();

	if (SrcName == "Bullet" &&
		DestName == "Monster")
	{
		CMonster* Monster = dynamic_cast<CMonster*>(DestObj);

		if (!Monster)
			ASSERT("if (!Monster)");

		Monster->SetDamage(1);
	}
}

void CBullet::Start()
{
	CGameObject::Start();
}

bool CBullet::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(50.f, 50.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body = (CColliderCircle*)CreateComponent<CColliderCircle>("Body");

	m_Body->SetRadius(25.f);

	m_Sprite->AddChild(m_Body);

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_NeedChangeOwner)
	{
		m_NeedChangeOwner = false;

		std::string	OwnerName = m_Owner->GetName();

		if (OwnerName == "Player")
		{
			m_Body->SetCollisionProfile("PlayerAttack");
			m_Body->AddCollisionCallback<CBullet>(Collision_State::Begin, this, &CBullet::SetDamage);
		}

		else if (OwnerName == "Monster")
			m_Body->SetCollisionProfile("MonsterAttack");
	}

	float	Dist = 500.f * DeltaTime;

	m_Distance -= Dist;

	if (m_Distance <= 0.f)
	{
		Destroy();
	}

	AddRelativePos(GetWorldAxis(AXIS_Y) * Dist);
}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone()
{
	return DBG_NEW CBullet(*this);
}
