
#include "BulletKingAnim.h"

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

	return true;
}

void CBulletKingAnim::Update(float DeltaTime)
{
	CMonsterAnim::Update(DeltaTime);
}

CBulletKingAnim* CBulletKingAnim::Clone()
{
	return DBG_NEW CBulletKingAnim(*this);
}

void CBulletKingAnim::ChangeAnimLeft()
{
	CMonsterAnim::ChangeAnimLeft();
}

void CBulletKingAnim::ChangeAnimRight()
{
	CMonsterAnim::ChangeAnimRight();
}
