
#include "MonsterAnimation.h"

ExampleCMonsterAnimation::ExampleCMonsterAnimation()
{
	SetTypeID<ExampleCMonsterAnimation>();
}

ExampleCMonsterAnimation::ExampleCMonsterAnimation(const ExampleCMonsterAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

ExampleCMonsterAnimation::~ExampleCMonsterAnimation()
{
}

bool ExampleCMonsterAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation("PlayerIdle", "Idle");

	return true;
}

ExampleCMonsterAnimation* ExampleCMonsterAnimation::Clone()
{
	return DBG_NEW ExampleCMonsterAnimation(*this);
}
