#pragma once

#include "Monster.h"

class CBandana :
    public CMonster
{
	friend class CScene;

protected:
	CBandana();
	CBandana(const CBandana& obj);
	virtual ~CBandana();

private:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBandana* Clone();

protected:
	virtual void PlaySoundDie();
	virtual void Attack(float DeltaTime);
};

