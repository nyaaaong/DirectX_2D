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
	float	m_BulletAngle;
	float	m_arrAngle[4];
	Vector3	m_arrDir[4];

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CShotgunKin2* Clone();
	virtual void Calc(float DeltaTime);
	virtual void Destroy();

protected:
	virtual void DestroyBefore();
	virtual void PlaySoundDie();
	virtual void Attack(float DeltaTime);
};

