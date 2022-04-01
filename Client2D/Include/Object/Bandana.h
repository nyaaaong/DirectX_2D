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
	float	m_BurstTimer;	// 연사 공격이 지속될 시간
	float	m_BurstTimerMax;
	float	m_BurstCoolDownTimer;	// 연사 공격 쿨타임
	float	m_BurstCoolDownTimerMax;
	bool	m_BurstCooldown;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBandana* Clone();

protected:
	virtual void Calc(float DeltaTime);
	virtual void PlaySoundDie();
	virtual void Attack(float DeltaTime);
};

