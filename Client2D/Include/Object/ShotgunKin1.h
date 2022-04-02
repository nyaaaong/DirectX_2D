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
	float	m_BulletAngle;
	float	m_arrAngle[4];
	Vector3	m_arrDir[4];

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CShotgunKin1* Clone();
	virtual void Calc(float DeltaTime);

protected:
	virtual void DestroyBefore();
	virtual void PlaySoundDie();
	virtual void Attack(float DeltaTime);
};

