#pragma once

#include "MonsterAnim.h"

class CBandanaAnim :
    public CMonsterAnim
{
public:
	CBandanaAnim();
	CBandanaAnim(const CBandanaAnim& Anim);
	virtual ~CBandanaAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBandanaAnim* Clone();

protected:
	virtual void ChangeAnimLeft();
	virtual void ChangeAnimRight();
};

