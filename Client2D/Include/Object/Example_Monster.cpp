
#include "Monster.h"
#include "Engine.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"
#include "MonsterAnimation.h"
#include "../Widget/SimpleHUD.h"

ExampleCMonster::ExampleCMonster()	:
	m_SimpleHUD(nullptr),
	m_HP(3)
{
	SetTypeID<ExampleCMonster>();
}

ExampleCMonster::ExampleCMonster(const ExampleCMonster& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("MonsterSprite");
	m_Body = (CColliderCircle*)FindComponent("Body");
	m_SimpleHUDWidget = (CWidgetComponent*)FindComponent("SimpleHUD");

	m_HP = obj.m_HP;
	m_PaperBurn = (CPaperBurnComponent*)FindComponent("PaperBurn");
}

ExampleCMonster::~ExampleCMonster()
{
}

void ExampleCMonster::Start()
{
	CGameObject::Start();

	m_PaperBurn->SetFinishCallback<ExampleCMonster>(this, &ExampleCMonster::PaperBurnEnd);
}

bool ExampleCMonster::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("MonsterSprite");
	m_Body = CreateComponent<CColliderCircle>("Body");
	m_PaperBurn = CreateComponent<CPaperBurnComponent>("PaperBurn");

	m_SimpleHUDWidget = CreateComponent<CWidgetComponent>("SimpleHUD");

	m_SimpleHUD = m_SimpleHUDWidget->CreateWidgetWindow<CSimpleHUD>("SimpleHUDWidget");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_SimpleHUDWidget);

	m_PaperBurn->SetMaterial(m_Sprite->GetMaterial());

	m_SimpleHUDWidget->SetRelativePos(-50.f, 50.f, 0.f);

	m_SimpleHUD->SetText(TEXT("띠모"));
	m_SimpleHUD->SetHPPercent(0.5f);
	m_SimpleHUD->SetHPDir(ProgressBar_Dir::BottomToTop);

	m_Body->SetCollisionProfile("Monster");


	m_Sprite->SetTransparency(true);
	//m_Sprite->SetOpacity(0.5f);

	m_Sprite->CreateAnimationInstance<ExampleCMonsterAnimation>();

	m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	m_Sprite->SetRelativePos(500.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body->AddCollisionMouseCallback(Collision_State::Begin, this, &ExampleCMonster::OnMouseBegin);
	m_Body->AddCollisionMouseCallback(Collision_State::End, this, &ExampleCMonster::OnMouseEnd);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &ExampleCMonster::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &ExampleCMonster::OnCollisionEnd);
	return true;
}

void ExampleCMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void ExampleCMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

ExampleCMonster* ExampleCMonster::Clone()
{
	return DBG_NEW ExampleCMonster(*this);
}

void ExampleCMonster::OnMouseBegin(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::State1);
}

void ExampleCMonster::OnMouseEnd(const CollisionResult& result)
{
	CEngine::GetInst()->SetMouseState(Mouse_State::Normal);
}

void ExampleCMonster::OnCollisionBegin(const CollisionResult& result)
{
	--m_HP;

	if (m_HP <= 0)
	{
		// 죽는 모션을 실행하고 죽는 모션이 끝났을때 끝 프레임에 고정시켜놓은 후에
		// PaperBurn을 진행한다.
		m_PaperBurn->StartPaperBurn();
		m_Body->Enable(false);
	}
}

void ExampleCMonster::OnCollisionEnd(const CollisionResult& result)
{
}

void ExampleCMonster::PaperBurnEnd()
{
	Destroy();
}
