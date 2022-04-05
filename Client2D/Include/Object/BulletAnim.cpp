
#include "BulletAnim.h"

CBulletAnim::CBulletAnim()	:
	m_GrayEffect(false)
{
	SetTypeID<CBulletAnim>();
}

CBulletAnim::CBulletAnim(const CBulletAnim& Anim)	:
	CAnimationSequence2DInstance(Anim)
{
	SetTypeID<CBulletAnim>();

	m_GrayEffect = Anim.m_GrayEffect;
}

CBulletAnim::~CBulletAnim()
{
}

void CBulletAnim::Start()
{
	CAnimationSequence2DInstance::Start();

	Play();
}

bool CBulletAnim::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	AddAnimation(TEXT("Bullet/Impact/Bullet_Impact.sqc"), "Bullet_Impact", ANIMATION_PATH, false, 0.2f);
	AddAnimation(TEXT("Bullet/Impact/Bullet_Impact_2.sqc"), "Bullet_Impact_2", ANIMATION_PATH, false, 0.2f);

	SetCurrentAnimation("Bullet_Impact");

	return true;
}

void CBulletAnim::First()
{
	CAnimationSequence2DInstance::First();

	if (m_GrayEffect)
		SetCurrentAnimation("Bullet_Impact_2");
}

CBulletAnim* CBulletAnim::Clone()
{
	return DBG_NEW CBulletAnim(*this);
}
