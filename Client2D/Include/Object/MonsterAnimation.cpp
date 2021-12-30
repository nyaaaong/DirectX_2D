
#include "MonsterAnimation.h"

CMonsterAnimation::CMonsterAnimation()
{
	SetTypeID<CMonsterAnimation>();
}

CMonsterAnimation::CMonsterAnimation(const CMonsterAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CMonsterAnimation::~CMonsterAnimation()
{
}

bool CMonsterAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("PlayerIdle", "Idle");

	return true;
}

CMonsterAnimation* CMonsterAnimation::Clone()
{
	return DBG_NEW CMonsterAnimation(*this);
}
