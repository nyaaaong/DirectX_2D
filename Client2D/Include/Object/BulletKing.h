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
	CSharedPtr<CSpriteComponent>	m_Chair;
	Vector2							m_ChairAnimSize;
	class CAnimationSequence2DInstance* m_ChairAnimInst;
	class CMainScene* m_MainScene;
	bool	m_ChairInvisible;
	float	m_ChairAlpha;
	float	m_BulletAngle;
	float	m_BulletCount;
	float	m_arrAngle[72];
	Vector3	m_arrDir[72];
	bool	m_BulletType1;
	bool	m_BulletType2;
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
	virtual void Enable(bool Enable);
	virtual void Hit(float DeltaTime);

protected:
	virtual void DestroyBefore();
	virtual void PlaySoundDie();

protected:
	void Pattern1(float DeltaTime);
	void Pattern2(float DeltaTime);
	void Pattern3_Start(float DeltaTime);
	void Pattern3_Progress(float DeltaTime);
	void Pattern3_End(float DeltaTime);
	void Pattern4(float DeltaTime);

protected:
	void Pattern1Attack();
	void Pattern2Attack();
	void Pattern3Attack();
	void Pattern4Attack();

private:
	void UpdateStatus();
};

