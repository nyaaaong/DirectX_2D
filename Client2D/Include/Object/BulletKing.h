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
	float	m_BurstTimer;	// ���� ������ ���ӵ� �ð�
	float	m_BurstTimerMax;// ���� ������ ���ӵ� �ð�
	float	m_BurstCoolDownTimer;	// ���� ���� ��Ÿ��
	float	m_BurstCoolDownTimerMax;// ���� ���� ��Ÿ��
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

