#pragma once

#include "Monster.h"

class CShotgunKin2 :
    public CMonster
{
	friend class CScene;

protected:
	CShotgunKin2();
	CShotgunKin2(const CShotgunKin2& obj);
	virtual ~CShotgunKin2();

private:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CShotgunKin2* Clone();

protected:
	virtual void PlaySoundDie();
	virtual void Attack(float DeltaTime);
};

