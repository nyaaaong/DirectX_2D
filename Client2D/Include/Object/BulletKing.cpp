
#include "BulletKing.h"

CBulletKing::CBulletKing()
{
}

CBulletKing::CBulletKing(const CBulletKing& obj)	:
	CMonster(obj)
{
}

CBulletKing::~CBulletKing()
{
}

void CBulletKing::Start()
{
	CMonster::Start();
}

bool CBulletKing::Init()
{
	if (!CMonster::Init())
		return false;

	return true;
}

void CBulletKing::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);
}

CBulletKing* CBulletKing::Clone()
{
	return DBG_NEW CBulletKing(*this);
}

void CBulletKing::Calc(float DeltaTime)
{
	CMonster::Calc(DeltaTime);
}

void CBulletKing::Destroy()
{
	CMonster::Destroy();
}

void CBulletKing::DestroyBefore()
{
	CMonster::DestroyBefore();
}

void CBulletKing::PlaySoundDie()
{
	CMonster::PlaySoundDie();
}

void CBulletKing::Attack(float DeltaTime)
{
	CMonster::Attack(DeltaTime);
}
