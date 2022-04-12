#pragma once
#include "MonsterAnim.h"

class CBulletKingAnim :
	public CMonsterAnim
{
public:
	CBulletKingAnim();
	CBulletKingAnim(const CBulletKingAnim& Anim);
	virtual ~CBulletKingAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBulletKingAnim* Clone();
};

