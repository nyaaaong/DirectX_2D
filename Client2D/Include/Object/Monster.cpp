
#include "Monster.h"
#include "Animation/AnimationSequence2DInstance.h"

CMonster::CMonster()	:
	m_HP(50.f),
	m_HitEffectTime(0.f),
	m_HitEffectTimeMax(0.3f),
	m_IsDied(false),
	m_IsPaperBurn(false),
	m_Hit(false)
{
	SetTypeID<CMonster>();
}

CMonster::CMonster(const CMonster& obj)	:
	CGameObject(obj)
{
	SetTypeID<CMonster>();

	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_PaperBurn = (CPaperBurnComponent*)FindComponent("PaperBurn");

	m_HP = obj.m_HP;
	m_IsDied = false;
	m_IsPaperBurn = false;
	m_Hit = false;
}

CMonster::~CMonster()
{
}

void CMonster::Start()
{
	CGameObject::Start();
}

bool CMonster::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_PaperBurn = CreateComponent<CPaperBurnComponent>("PaperBurn");

	m_Body->SetExtent(18.f, 33.f);
	m_Body->SetCollisionProfile("Monster");

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Hit(DeltaTime);
	Dead();
}

void CMonster::OnCollisionBegin(const CollisionResult& result)
{
	m_Hit = true;
}

void CMonster::PaperBurnEnd()
{
	Destroy();
}

void CMonster::Dead()
{
	if (m_HP <= 0.f && !m_IsDied)
	{
		m_IsDied = true;

		m_HP = 0.f;
		m_Body->Enable(false);
		m_Body->SetRender(false);
		// 죽는 애니메이션을 실행한다
	}

	else if (m_IsDied && !m_IsPaperBurn)
	{
		// 죽는 애니메이션이 실행중이며 만약 애니메이션이 끝났다면 페이퍼번을 실행한다.
		if (m_Sprite->GetAnimationInstance()->IsEnd())
		{
			m_IsPaperBurn = true;

			m_PaperBurn->StartPaperBurn();
		}
	}
}

void CMonster::Hit(float DeltaTime)
{
	if (m_Hit)
	{
		m_HitEffectTime += DeltaTime;

		m_Sprite->SetBaseColor(Vector4::Red);

		// 히트 사운드 출력

		if (m_HitEffectTime >= m_HitEffectTimeMax)
		{
			m_Sprite->SetBaseColor(Vector4::White);

			m_HitEffectTime = 0.f;
			m_Hit = false;
		}
	}
}

void CMonster::Destroy()
{
	CGameObject::Destroy();
}
