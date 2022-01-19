
#include "Monster.h"
#include "Engine.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "MonsterAnimation.h"
#include "../Widget/SimpleHUD.h"

CMonster::CMonster()	:
	m_SimpleHUD(nullptr),
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
	m_SimpleHUDWidget = (CWidgetComponent*)FindComponent("SimpleHUD");

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

	m_SimpleHUDWidget = CreateComponent<CWidgetComponent>("SimpleHUD");

	m_SimpleHUD = m_SimpleHUDWidget->CreateWidgetWindow<CSimpleHUD>("SimpleHUDWidget");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_SimpleHUDWidget);

	m_SimpleHUDWidget->SetRelativePos(-50.f, 50.f, 0.f);

	m_SimpleHUD->SetText(TEXT("¶ì¸ð"));
	m_SimpleHUD->SetHPPercent(0.5f);
	m_SimpleHUD->SetHPDir(ProgressBar_Dir::BottomToTop);

	m_Body->SetCollisionProfile("Monster");


	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<CMonsterAnimation>();

	m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->AddCollisionMouseCallback(Collision_State::Begin, this, &CMonster::OnMouseBegin);
	m_Body->AddCollisionMouseCallback(Collision_State::End, this, &CMonster::OnMouseEnd);

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

void CMonster::OnMouseBegin(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::State1);
}

void CMonster::OnMouseEnd(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::Normal);
}
