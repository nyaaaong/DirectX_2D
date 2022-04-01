#pragma once

#include "Monster.h"

class CShotgunKin1 :
    public CMonster
{
	friend class CScene;

protected:
	CShotgunKin1();
	CShotgunKin1(const CShotgunKin1& obj);
	virtual ~CShotgunKin1();

private:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CShotgunKin1* Clone();

protected:
	virtual void PlaySoundDie();
	virtual void Attack(float DeltaTime);
};

