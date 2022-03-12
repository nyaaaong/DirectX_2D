
#include "BulletImpactAnimation2D.h"

CBulletImpactAnimation2D::CBulletImpactAnimation2D()
{
	SetTypeID<CBulletImpactAnimation2D>();
}

CBulletImpactAnimation2D::CBulletImpactAnimation2D(const CBulletImpactAnimation2D& Anim) :
	CAnimationSequence2DInstance(Anim)
{
}

CBulletImpactAnimation2D::~CBulletImpactAnimation2D()
{
}

bool CBulletImpactAnimation2D::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation(TEXT("Bullet/Impact/Bullet_Impact.sqc"), "Bullet_Impact", ANIMATION_PATH, false, 0.1f);

	Play();

	SetCurrentAnimation("Bullet_Impact");

	return true;
}

CBulletImpactAnimation2D* CBulletImpactAnimation2D::Clone()
{
	return DBG_NEW CBulletImpactAnimation2D(*this);
}