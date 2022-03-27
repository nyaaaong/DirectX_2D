#pragma once

#include "Monster.h"

class CBulletKin :
	public CMonster
{
	friend class CScene;

protected:
	CBulletKin();
	CBulletKin(const CBulletKin& obj);
	virtual ~CBulletKin();

private:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBulletKin* Clone();

protected:
	virtual void PlaySoundDie();
	virtual void Attack(float DeltaTime);
};

