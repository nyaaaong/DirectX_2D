
#include "Monster.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "MonsterAnimation.h"

CMonster::CMonster()	:
	m_HP(50),
	m_HPMax(50)
{
	SetTypeID<CMonster>();
}

CMonster::CMonster(const CMonster& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("PlayerSprite");
	m_Body = (CColliderCircle*)FindComponent("Body");

	m_HP = obj.m_HP;
	m_HPMax = obj.m_HPMax;
}

CMonster::~CMonster()
{
}

void CMonster::Destroy()
{
	CGameObject::Destroy();

	m_Sprite->Destroy();
	m_Body->Destroy();
}

bool CMonster::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("PlayerSprite");
	m_Body = CreateComponent<CColliderCircle>("Body");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);

	m_Body->SetCollisionProfile("Monster");


	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CMonsterAnimation>();

	m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMonster* CMonster::Clone()
{
	return DBG_NEW CMonster(*this);
}
