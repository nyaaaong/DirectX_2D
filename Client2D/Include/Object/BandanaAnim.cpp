
#include "BandanaAnim.h"
#include "Monster.h"

CBandanaAnim::CBandanaAnim()
{
	SetTypeID<CBandanaAnim>();
}

CBandanaAnim::CBandanaAnim(const CBandanaAnim& Anim) :
	CMonsterAnim(Anim)
{
	SetTypeID<CBandanaAnim>();
}

CBandanaAnim::~CBandanaAnim()
{
}

void CBandanaAnim::Start()
{
	CMonsterAnim::Start();

	Play();
}

bool CBandanaAnim::Init()
{
	if (!CMonsterAnim::Init())
		return false;

	AddAnimation(TEXT("Monster/Bandana/Idle/Bandana_Idle_L.sqc"), "Bandana_Idle_L", ANIMATION_PATH);
	AddAnimation(TEXT("Monster/Bandana/Idle/Bandana_Idle_R.sqc"), "Bandana_Idle_R", ANIMATION_PATH);

	AddAnimation(TEXT("Monster/Bandana/Walk/Bandana_Walk_L.sqc"), "Bandana_Walk_L", ANIMATION_PATH, true, 1.f);
	AddAnimation(TEXT("Monster/Bandana/Walk/Bandana_Walk_R.sqc"), "Bandana_Walk_R", ANIMATION_PATH, true, 1.f);

	AddAnimation(TEXT("Monster/Bandana/Death/Bandana_Death_L.sqc"), "Bandana_Death_L", ANIMATION_PATH, false, 0.4f);
	AddAnimation(TEXT("Monster/Bandana/Death/Bandana_Death_R.sqc"), "Bandana_Death_R", ANIMATION_PATH, false, 0.4f);

	SetCurrentAnimation("Bandana_Idle_L");

	return true;
}

void CBandanaAnim::Update(float DeltaTime)
{
	CMonsterAnim::Update(DeltaTime);
}

CBandanaAnim* CBandanaAnim::Clone()
{
	return DBG_NEW CBandanaAnim(*this);
}

void CBandanaAnim::ChangeAnimLeft()
{
	CMonsterAnim::ChangeAnimLeft();

	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		ChangeAnimation("Bandana_Idle_L");
		break;
	case Monster_State::Walk:
		ChangeAnimation("Bandana_Walk_L");
		break;
	case Monster_State::Die:
		ChangeAnimation("Bandana_Death_R");
		break;
	}
}

void CBandanaAnim::ChangeAnimRight()
{
	CMonsterAnim::ChangeAnimRight();

	switch (m_OwnerObject->GetState())
	{
	case Monster_State::Idle:
		ChangeAnimation("Bandana_Idle_R");
		break;
	case Monster_State::Walk:
		ChangeAnimation("Bandana_Walk_R");
		break;
	case Monster_State::Die:
		ChangeAnimation("Bandana_Death_L");
		break;
	}
}
