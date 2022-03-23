#pragma once

#include "MonsterAnim.h"

class CBulletKinAnim :
	public CMonsterAnim
{
public:
	CBulletKinAnim();
	CBulletKinAnim(const CBulletKinAnim& Anim);
	virtual ~CBulletKinAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBulletKinAnim* Clone();

protected:
	virtual void ChangeAnimLeft();
	virtual void ChangeAnimRight();
};

