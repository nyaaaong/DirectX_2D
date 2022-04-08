#pragma once

#include "Monster.h"

class CBulletKing :
    public CMonster
{
	friend class CScene;

protected:
	CBulletKing();
	CBulletKing(const CBulletKing& obj);
	virtual ~CBulletKing();

private:
	float	m_BulletAngle;
	float	m_arrAngle[4];
	Vector3	m_arrDir[4];
	float	m_BurstTimer;	// 연사 공격이 지속될 시간
	float	m_BurstTimerMax;// 연사 공격이 지속될 시간
	float	m_BurstCoolDownTimer;	// 연사 공격 쿨타임
	float	m_BurstCoolDownTimerMax;// 연사 공격 쿨타임
	bool	m_BurstCooldown;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBulletKing* Clone();
	virtual void Calc(float DeltaTime);
	virtual void Destroy();

protected:
	virtual void DestroyBefore();
	virtual void PlaySoundDie();
	virtual void Attack(float DeltaTime);
};

