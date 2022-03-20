
#include "BulletKin.h"
#include "BulletKinAnim.h"
#include "Scene/Scene.h"

CBulletKin::CBulletKin()	:
	m_BurnStartDelay(0.f),
	m_BurnStartDelayMax(0.5f)
{
	SetTypeID<CBulletKin>();

	m_Type = Character_Type::Monster;
}

CBulletKin::CBulletKin(const CBulletKin& obj)	:
	CCharacter(obj),
	m_BurnStartDelay(0.f)
{
	SetTypeID<CBulletKin>();

	m_Sprite = (CSpriteComponent*)FindComponent("BulletKinSprite");
	m_Sprite->CreateAnimationInstance<CBulletKinAnim>();

	m_BurnStartDelayMax = obj.m_BurnStartDelayMax;

	m_Type = Character_Type::Monster;
}

CBulletKin::~CBulletKin()
{
}

void CBulletKin::Start()
{
	CCharacter::Start();
}

bool CBulletKin::Init()
{
	if (!CCharacter::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("BulletKinSprite");

	m_Sprite->CreateAnimationInstance<CBulletKinAnim>();
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetTransparency(true);
	m_Sprite->AddChild(m_Body);

	m_Body->SetWorldPos(m_Sprite->GetWorldPos());
	m_Body->SetExtent(18.f, 33.f);
	m_Body->SetCollisionProfile("Monster");
	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBulletKin::OnCollisionBegin);

	m_PaperBurn->SetMaterial(m_Sprite->GetMaterial());
	m_PaperBurn->SetFinishCallback<CBulletKin>(this, &CBulletKin::PaperBurnEnd);

	SetRootComponent(m_Sprite);

	return true;
}

void CBulletKin::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

CBulletKin* CBulletKin::Clone()
{
	return DBG_NEW CBulletKin(*this);
}

void CBulletKin::Destroy()
{
	CCharacter::Destroy();
}

void CBulletKin::OnCollisionBegin(const CollisionResult& result)
{
	CCharacter::OnCollisionBegin(result);
}

void CBulletKin::PaperBurnEnd()
{
	CCharacter::PaperBurnEnd();
}

void CBulletKin::Dead(float DeltaTime)
{
	if (m_BurnStartDelay < m_BurnStartDelayMax)
		m_BurnStartDelay += DeltaTime;

	if (m_HP <= 0.f && !m_IsDied)
	{
		CCharacter::Dead(DeltaTime);

		int i = rand() % 4 + 1;
		char Name[256] = {};

		sprintf_s(Name, "BulletKin_Die%d", i);

		m_Scene->GetResource()->SoundPlay(Name);		

		m_IsDied = true;

		m_HP = 0.f;
		m_Body->Enable(false);
		m_Body->SetRender(false);
		// 죽는 애니메이션을 실행한다
		m_Sprite->GetAnimationInstance()->ChangeAnimation("BulletKin_Death_R");
	}

	else if (m_IsDied && !m_IsPaperBurn && m_BurnStartDelay >= m_BurnStartDelayMax)
	{
		// 죽는 애니메이션이 실행중이며 만약 애니메이션이 끝났다면 페이퍼번을 실행한다.
		if (m_Sprite->GetAnimationInstance()->IsEnd())
		{
			m_Sprite->GetAnimationInstance()->Stop();

			m_IsPaperBurn = true;

			m_PaperBurn->StartPaperBurn();
		}
	}
}

void CBulletKin::Hit(float DeltaTime)
{
	CCharacter::Hit(DeltaTime);
}
