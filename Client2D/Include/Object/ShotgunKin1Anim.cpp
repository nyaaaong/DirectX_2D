
#include "ShotgunKin1Anim.h"
#include "Monster.h"

CShotgunKin1Anim::CShotgunKin1Anim()
{
	SetTypeID<CShotgunKin1Anim>();
}

CShotgunKin1Anim::CShotgunKin1Anim(const CShotgunKin1Anim& Anim) :
	CMonsterAnim(Anim)
{
	SetTypeID<CShotgunKin1Anim>();
}

CShotgunKin1Anim::~CShotgunKin1Anim()
{
}

void CShotgunKin1Anim::Start()
{
	CMonsterAnim::Start();

	Play();
}

bool CShotgunKin1Anim::Init()
{
	if (!CMonsterAnim::Init())
		return false;

	AddAnimation(TEXT("Monster/ShotgunKin1/Idle/ShotgunKin1_Idle_L.sqc"), "ShotgunKin1_Idle_L", ANIMATION_PATH);
	AddAnimation(TEXT("Monster/ShotgunKin1/Idle/ShotgunKin1_Idle_R.sqc"), "ShotgunKin1_Idle_R", ANIMATION_PATH);

	AddAnimation(TEXT("Monster/ShotgunKin1/Walk/ShotgunKin1_Walk_L.sqc"), "ShotgunKin1_Walk_L", ANIMATION_PATH, true, 1.f);
	AddAnimation(TEXT("Monster/ShotgunKin1/Walk/ShotgunKin1_Walk_R.sqc"), "ShotgunKin1_Walk_R", ANIMATION_PATH, true, 1.f);

	AddAnimation(TEXT("Monster/ShotgunKin1/Death/ShotgunKin1_Death.sqc"), "ShotgunKin1_Death", ANIMATION_PATH, false, 0.6f);

	SetCurrentAnimation("ShotgunKin1_Idle_L");

	return true;
}

void CShotgunKin1Anim::Update(float DeltaTime)
{
	CMonsterAnim::Update(DeltaTime);
}

CShotgunKin1Anim* CShotgunKin1Anim::Clone()
{
	return DBG_NEW CShotgunKin1Anim(*this);
}

void CShotgunKin1Anim::ChangeAnimLeft()
{
	CMonsterAnim::ChangeAnimLeft();

	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		ChangeAnimation("ShotgunKin1_Idle_L");
		break;
	case Monster_State::Walk:
		ChangeAnimation("ShotgunKin1_Walk_L");
		break;
	case Monster_State::Die:
		ChangeAnimation("ShotgunKin1_Death");
		break;
	}
}

void CShotgunKin1Anim::ChangeAnimRight()
{
	CMonsterAnim::ChangeAnimRight();

	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		ChangeAnimation("ShotgunKin1_Idle_R");
		break;
	case Monster_State::Walk:
		ChangeAnimation("ShotgunKin1_Walk_R");
		break;
	case Monster_State::Die:
		ChangeAnimation("ShotgunKin1_Death");
		break;
	}
}
