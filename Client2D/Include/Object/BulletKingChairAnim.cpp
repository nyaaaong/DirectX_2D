
#include "BulletKingChairAnim.h"
#include "BulletKing.h"

CBulletKingChairAnim::CBulletKingChairAnim()
{
	SetTypeID<CBulletKingChairAnim>();
}

CBulletKingChairAnim::CBulletKingChairAnim(const CBulletKingChairAnim& Anim) :
	CMonsterAnim(Anim)
{
	SetTypeID<CBulletKingChairAnim>();
}

CBulletKingChairAnim::~CBulletKingChairAnim()
{
}

void CBulletKingChairAnim::Start()
{
	CMonsterAnim::Start();

	Play();
}

bool CBulletKingChairAnim::Init()
{
	if (!CMonsterAnim::Init())
		return false;

	AddAnimation(TEXT("Monster/Boss/BulletKing/Chair/BulletKing_Chair_Idle.sqc"), "BulletKing_Chair_Idle", ANIMATION_PATH, false);

	AddAnimation(TEXT("Monster/Boss/BulletKing/Chair/BulletKing_Chair_Pattern1.sqc"), "BulletKing_Chair_Pattern1", ANIMATION_PATH, false, 0.4f);
	AddAnimation(TEXT("Monster/Boss/BulletKing/Chair/BulletKing_Chair_Pattern2.sqc"), "BulletKing_Chair_Pattern2", ANIMATION_PATH, false, 0.4f);

	AddAnimation(TEXT("Monster/Boss/BulletKing/Chair/BulletKing_Chair_Pattern3_Start.sqc"), "BulletKing_Chair_Pattern3_Start", ANIMATION_PATH, false);
	AddAnimation(TEXT("Monster/Boss/BulletKing/Chair/BulletKing_Chair_Pattern3_Progress.sqc"), "BulletKing_Chair_Pattern3_Progress", ANIMATION_PATH, true, 0.5f);
	AddAnimation(TEXT("Monster/Boss/BulletKing/Chair/BulletKing_Chair_Pattern3_End.sqc"), "BulletKing_Chair_Pattern3_End", ANIMATION_PATH, false);

	AddAnimation(TEXT("Monster/Boss/BulletKing/Chair/BulletKing_Chair_Pattern4.sqc"), "BulletKing_Chair_Pattern4", ANIMATION_PATH);

	SetCurrentAnimation("BulletKing_Chair_Idle");

	return true;
}

void CBulletKingChairAnim::Update(float DeltaTime)
{
	CMonsterAnim::Update(DeltaTime);

	CBulletKing* BulletKing = dynamic_cast<CBulletKing*>(m_OwnerObject);

	if (BulletKing->GetBulletKingState() == BulletKing->GetBulletKingPrevState())
		return;

	switch (BulletKing->GetBulletKingState())
	{
	case BulletKing_State::Idle:
		ChangeAnimation("BulletKing_Chair_Idle");
		break;
	case BulletKing_State::Die:
	case BulletKing_State::Die_End:
		ChangeAnimation("BulletKing_Chair_Idle");
		break;
	case BulletKing_State::Pattern1:
		ChangeAnimation("BulletKing_Chair_Pattern1");
		break;
	case BulletKing_State::Pattern2:
		ChangeAnimation("BulletKing_Chair_Pattern2");
		break;
	case BulletKing_State::Pattern3_Start:
		ChangeAnimation("BulletKing_Chair_Pattern3_Start");
		break;
	case BulletKing_State::Pattern3_Progress:
		ChangeAnimation("BulletKing_Chair_Pattern3_Progress");
		break;
	case BulletKing_State::Pattern3_End:
		ChangeAnimation("BulletKing_Chair_Pattern3_End");
		break;
	case BulletKing_State::Pattern4:
		ChangeAnimation("BulletKing_Chair_Pattern4");
		break;
	}
}

CBulletKingChairAnim* CBulletKingChairAnim::Clone()
{
	return DBG_NEW CBulletKingChairAnim(*this);
}
