
#include "BulletKin.h"
#include "BulletKinAnim.h"
#include "Scene/Scene.h"

CBulletKin::CBulletKin()	:
	m_HP(50.f),
	m_HitEffectTime(0.f),
	m_HitEffectTimeMax(0.3f),
	m_IsDied(false),
	m_IsPaperBurn(false),
	m_Hit(false)
{
	SetTypeID<CBulletKin>();
}

CBulletKin::CBulletKin(const CBulletKin& obj)	:
	CGameObject(obj)
{
	SetTypeID<CBulletKin>();

	m_Sprite = (CSpriteComponent*)FindComponent("MonsterSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_PaperBurn = (CPaperBurnComponent*)FindComponent("PaperBurn");

	m_Sprite->CreateAnimationInstance<CBulletKinAnim>();

	m_HP = obj.m_HP;
	m_IsDied = false;
	m_IsPaperBurn = false;
	m_Hit = false;
}

CBulletKin::~CBulletKin()
{
}

void CBulletKin::Start()
{
	CGameObject::Start();
}

bool CBulletKin::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("MonsterSprite");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_PaperBurn = CreateComponent<CPaperBurnComponent>("PaperBurn");

	float	Offset = 400.f;
	Vector2	CamLB = m_Scene->GetCameraManager()->GetCurrentCamera()->GetLeftBottom();
	Vector3 MonsterPos = Vector3(CamLB.x + Offset, CamLB.y + Offset, 0.f);

	m_Sprite->CreateAnimationInstance<CBulletKinAnim>();
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetRelativePos(MonsterPos);
	m_Sprite->SetTransparency(true);
	m_Sprite->AddChild(m_Body);

	m_Body->SetExtent(18.f, 33.f);
	m_Body->SetWorldPos(m_Sprite->GetWorldPos());
	m_Body->SetCollisionProfile("Monster");
	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBulletKin::OnCollisionBegin);

	m_PaperBurn->SetMaterial(m_Sprite->GetMaterial());
	m_PaperBurn->SetFinishCallback<CBulletKin>(this, &CBulletKin::PaperBurnEnd);

	SetRootComponent(m_Sprite);

	return true;
}

void CBulletKin::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Hit(DeltaTime);
	Dead();
}

void CBulletKin::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBulletKin* CBulletKin::Clone()
{
	return DBG_NEW CBulletKin(*this);
}

void CBulletKin::OnCollisionBegin(const CollisionResult& result)
{
	m_Hit = true;
}

void CBulletKin::PaperBurnEnd()
{
	Destroy();
}

void CBulletKin::Dead()
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

void CBulletKin::Hit(float DeltaTime)
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
