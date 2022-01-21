
#include "Bullet.h"
#include "Monster.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderCircle.h"

CBullet::CBullet() :
	m_Distance(600.f)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Distance = obj.m_Distance;

	m_Body = (CColliderCircle*)FindComponent("Body");
}

CBullet::~CBullet()
{
}

void CBullet::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
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

	m_Body = CreateComponent<CColliderCircle>("Body");

	m_Body->SetRadius(25.f);

	m_Sprite->AddChild(m_Body);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBullet::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CBullet::OnCollisionEnd);

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

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

void CBullet::OnCollisionBegin(const CollisionResult& result)
{
	Destroy();
}

void CBullet::OnCollisionEnd(const CollisionResult& result)
{
}
