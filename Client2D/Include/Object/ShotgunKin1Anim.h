#pragma once

#include "MonsterAnim.h"

class CShotgunKin1Anim :
    public CMonsterAnim
{
public:
	CShotgunKin1Anim();
	CShotgunKin1Anim(const CShotgunKin1Anim& Anim);
	virtual ~CShotgunKin1Anim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CShotgunKin1Anim* Clone();

protected:
	virtual void ChangeAnimLeft();
	virtual void ChangeAnimRight();
};

