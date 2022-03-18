
#include "BulletKinAnim.h"

CBulletKinAnim::CBulletKinAnim()
{
	SetTypeID<CBulletKinAnim>();
}

CBulletKinAnim::CBulletKinAnim(const CBulletKinAnim& Anim) :
	CAnimationSequence2DInstance(Anim)
{
	SetTypeID<CBulletKinAnim>();
}

CBulletKinAnim::~CBulletKinAnim()
{
}

void CBulletKinAnim::Start()
{
	CAnimationSequence2DInstance::Start();

	Play();
}

bool CBulletKinAnim::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation(TEXT("Monster/BulletKin/Idle/BulletKin_Idle_L.sqc"), "BulletKin_Idle_L", ANIMATION_PATH);

	SetCurrentAnimation("BulletKin_Idle_L");

	return true;
}

CBulletKinAnim* CBulletKinAnim::Clone()
{
	return DBG_NEW CBulletKinAnim(*this);
}