
#include "BulletKinAnim.h"
#include "Monster.h"

CBulletKinAnim::CBulletKinAnim()
{
	SetTypeID<CBulletKinAnim>();
}

CBulletKinAnim::CBulletKinAnim(const CBulletKinAnim& Anim) :
	CMonsterAnim(Anim)
{
	SetTypeID<CBulletKinAnim>();
}

CBulletKinAnim::~CBulletKinAnim()
{
}

void CBulletKinAnim::Start()
{
	CMonsterAnim::Start();

	Play();
}

bool CBulletKinAnim::Init()
{
	if (!CMonsterAnim::Init())
		return false;

	AddAnimation(TEXT("Monster/BulletKin/Idle/BulletKin_Idle_L.sqc"), "BulletKin_Idle_L", ANIMATION_PATH);
	AddAnimation(TEXT("Monster/BulletKin/Idle/BulletKin_Idle_R.sqc"), "BulletKin_Idle_R", ANIMATION_PATH);

	AddAnimation(TEXT("Monster/BulletKin/Walk/BulletKin_Walk_L.sqc"), "BulletKin_Walk_L", ANIMATION_PATH, true, 1.f);
	AddAnimation(TEXT("Monster/BulletKin/Walk/BulletKin_Walk_R.sqc"), "BulletKin_Walk_R", ANIMATION_PATH, true, 1.f);

	AddAnimation(TEXT("Monster/BulletKin/Death/BulletKin_Death_L.sqc"), "BulletKin_Death_L", ANIMATION_PATH, false, 0.4f);
	AddAnimation(TEXT("Monster/BulletKin/Death/BulletKin_Death_R.sqc"), "BulletKin_Death_R", ANIMATION_PATH, false, 0.4f);

	SetCurrentAnimation("BulletKin_Idle_L");

	return true;
}

void CBulletKinAnim::Update(float DeltaTime)
{
	CMonsterAnim::Update(DeltaTime);
}

CBulletKinAnim* CBulletKinAnim::Clone()
{
	return DBG_NEW CBulletKinAnim(*this);
}

void CBulletKinAnim::ChangeAnimLeft()
{
	CMonsterAnim::ChangeAnimLeft();

	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		ChangeAnimation("BulletKin_Idle_L");
		break;
	case Monster_State::Walk:
		ChangeAnimation("BulletKin_Walk_L");
		break;
	case Monster_State::Die:
		ChangeAnimation("BulletKin_Death_R");
		break;
	}
}

void CBulletKinAnim::ChangeAnimRight()
{
	CMonsterAnim::ChangeAnimRight();

	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		ChangeAnimation("BulletKin_Idle_R");
		break;
	case Monster_State::Walk:
		ChangeAnimation("BulletKin_Walk_R");
		break;
	case Monster_State::Die:
		ChangeAnimation("BulletKin_Death_L");
		break;
	}
}
