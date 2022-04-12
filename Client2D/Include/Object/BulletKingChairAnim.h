#pragma once

#include "MonsterAnim.h"

class CBulletKingChairAnim :
	public CMonsterAnim
{
public:
	CBulletKingChairAnim();
	CBulletKingChairAnim(const CBulletKingChairAnim& Anim);
	virtual ~CBulletKingChairAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBulletKingChairAnim* Clone();
};

