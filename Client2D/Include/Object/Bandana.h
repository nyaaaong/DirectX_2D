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
	float	m_BurstTimer;	// ���� ������ ���ӵ� �ð�
	float	m_BurstTimerMax;
	float	m_BurstCoolDownTimer;	// ���� ���� ��Ÿ��
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

