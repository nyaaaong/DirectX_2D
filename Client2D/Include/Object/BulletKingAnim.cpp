
#include "BulletKingAnim.h"
#include "BulletKing.h"

CBulletKingAnim::CBulletKingAnim()
{
	SetTypeID<CBulletKingAnim>();
}

CBulletKingAnim::CBulletKingAnim(const CBulletKingAnim& Anim) :
	CMonsterAnim(Anim)
{
	SetTypeID<CBulletKingAnim>();
}

CBulletKingAnim::~CBulletKingAnim()
{
}

void CBulletKingAnim::Start()
{
	CMonsterAnim::Start();

	Play();
}

bool CBulletKingAnim::Init()
{
	if (!CMonsterAnim::Init())
		return false;

	AddAnimation(TEXT("Monster/Boss/BulletKing/BulletKing_Idle.sqc"), "BulletKing_Idle", ANIMATION_PATH);

	AddAnimation(TEXT("Monster/Boss/BulletKing/BulletKing_Pattern1.sqc"), "BulletKing_Pattern1", ANIMATION_PATH, false, 0.4f);
	AddAnimation(TEXT("Monster/Boss/BulletKing/BulletKing_Pattern2.sqc"), "BulletKing_Pattern2", ANIMATION_PATH, false, 0.4f);

	AddAnimation(TEXT("Monster/Boss/BulletKing/BulletKing_Pattern3_Start.sqc"), "BulletKing_Pattern3_Start", ANIMATION_PATH, false, 0.4f);
	AddAnimation(TEXT("Monster/Boss/BulletKing/BulletKing_Pattern3_End.sqc"), "BulletKing_Pattern3_End", ANIMATION_PATH, false, 1.5f);

	AddAnimation(TEXT("Monster/Boss/BulletKing/BulletKing_Die.sqc"), "BulletKing_Die", ANIMATION_PATH, true, 0.2f);
	AddAnimation(TEXT("Monster/Boss/BulletKing/BulletKing_Die_End.sqc"), "BulletKing_Die_End", ANIMATION_PATH, false);

	SetCurrentAnimation("BulletKing_Idle");

	return true;
}

void CBulletKingAnim::Update(float DeltaTime)
{
	CMonsterAnim::Update(DeltaTime);
	
	CBulletKing* BulletKing = dynamic_cast<CBulletKing*>(m_OwnerObject);

	if (BulletKing->GetBulletKingState() == BulletKing->GetBulletKingPrevState())
		return;

	switch (BulletKing->GetBulletKingState())
	{
	case BulletKing_State::Idle:
		ChangeAnimation("BulletKing_Idle");
		break;
	case BulletKing_State::Die:
		// 패턴3 도중에 죽을 수도 있기 때문에 렌더를 활성화
		m_Owner->SetRender(true);
		ChangeAnimation("BulletKing_Die");
		break;
	case BulletKing_State::Die_End:
		ChangeAnimation("BulletKing_Die_End");
		break;
	case BulletKing_State::Pattern1:
		ChangeAnimation("BulletKing_Pattern1");
		break;
	case BulletKing_State::Pattern2:
		ChangeAnimation("BulletKing_Pattern2");
		break;
	case BulletKing_State::Pattern3_Start:
		ChangeAnimation("BulletKing_Pattern3_Start");
		break;
	case BulletKing_State::Pattern3_Progress:
		m_Owner->SetRender(false);
		break;
	case BulletKing_State::Pattern3_End:
		m_Owner->SetRender(true);
		ChangeAnimation("BulletKing_Pattern3_End");
		break;
	case BulletKing_State::Pattern4:
		ChangeAnimation("BulletKing_Pattern1");
		break;
	}
}

CBulletKingAnim* CBulletKingAnim::Clone()
{
	return DBG_NEW CBulletKingAnim(*this);
}
