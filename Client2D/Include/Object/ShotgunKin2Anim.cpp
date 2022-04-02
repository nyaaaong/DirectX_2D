
#include "ShotgunKin2Anim.h"
#include "Monster.h"

CShotgunKin2Anim::CShotgunKin2Anim()
{
	SetTypeID<CShotgunKin2Anim>();
}

CShotgunKin2Anim::CShotgunKin2Anim(const CShotgunKin2Anim& Anim) :
	CMonsterAnim(Anim)
{
	SetTypeID<CShotgunKin2Anim>();
}

CShotgunKin2Anim::~CShotgunKin2Anim()
{
}

void CShotgunKin2Anim::Start()
{
	CMonsterAnim::Start();

	Play();
}

bool CShotgunKin2Anim::Init()
{
	if (!CMonsterAnim::Init())
		return false;

	AddAnimation(TEXT("Monster/ShotgunKin2/Idle/ShotgunKin2_Idle_L.sqc"), "ShotgunKin2_Idle_L", ANIMATION_PATH);
	AddAnimation(TEXT("Monster/ShotgunKin2/Idle/ShotgunKin2_Idle_R.sqc"), "ShotgunKin2_Idle_R", ANIMATION_PATH);

	AddAnimation(TEXT("Monster/ShotgunKin2/Walk/ShotgunKin2_Walk_L.sqc"), "ShotgunKin2_Walk_L", ANIMATION_PATH, true, 1.f);
	AddAnimation(TEXT("Monster/ShotgunKin2/Walk/ShotgunKin2_Walk_R.sqc"), "ShotgunKin2_Walk_R", ANIMATION_PATH, true, 1.f);

	AddAnimation(TEXT("Monster/ShotgunKin2/Death/ShotgunKin2_Death.sqc"), "ShotgunKin2_Death", ANIMATION_PATH, false, 0.6f);

	SetCurrentAnimation("ShotgunKin2_Idle_L");

	return true;
}

void CShotgunKin2Anim::Update(float DeltaTime)
{
	CMonsterAnim::Update(DeltaTime);
}

CShotgunKin2Anim* CShotgunKin2Anim::Clone()
{
	return DBG_NEW CShotgunKin2Anim(*this);
}

void CShotgunKin2Anim::ChangeAnimLeft()
{
	CMonsterAnim::ChangeAnimLeft();

	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		ChangeAnimation("ShotgunKin2_Idle_L");
		break;
	case Monster_State::Walk:
		ChangeAnimation("ShotgunKin2_Walk_L");
		break;
	case Monster_State::Die:
		ChangeAnimation("ShotgunKin2_Death");
		break;
	}
}

void CShotgunKin2Anim::ChangeAnimRight()
{
	CMonsterAnim::ChangeAnimRight();

	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		ChangeAnimation("ShotgunKin2_Idle_R");
		break;
	case Monster_State::Walk:
		ChangeAnimation("ShotgunKin2_Walk_R");
		break;
	case Monster_State::Die:
		ChangeAnimation("ShotgunKin2_Death");
		break;
	}
}
