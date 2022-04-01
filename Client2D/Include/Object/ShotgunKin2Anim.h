#pragma once

#include "MonsterAnim.h"

class CShotgunKin2Anim :
    public CMonsterAnim
{
public:
	CShotgunKin2Anim();
	CShotgunKin2Anim(const CShotgunKin2Anim& Anim);
	virtual ~CShotgunKin2Anim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CShotgunKin2Anim* Clone();

protected:
	virtual void ChangeAnimLeft();
	virtual void ChangeAnimRight();
};

