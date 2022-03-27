#pragma once

#include "Character.h"

class CMonster :
	public CCharacter
{
	friend class CScene;

public:
	CMonster();
	CMonster(const CMonster& obj);
	virtual ~CMonster();

protected:
	CSharedPtr<class CNavAgent>	m_NavAgent;
	CSharedPtr<CSpriteComponent>	m_Weapon;
	CSharedPtr<CSpriteComponent>	m_WeaponL;
	CSpriteComponent* m_CurWeapon;
	class CPlayer2D* m_Player;
	Vector3	m_PlayerWorldPos; // 월드상의 플레이어 위치
	Vector3	m_PlayerDir; // 몬스터기준 플레이어의 방향
	Vector3	m_RandomDir; // 랜덤한 방향
	Monster_State	m_State;
	float	m_BurnStartDelay;
	float	m_BurnStartDelayMax;
	float	m_MoveTimer;
	float	m_MoveTimerMax;
	float	m_AttackTimer;
	float	m_AttackTimerMax;
	float	m_PlayerAngle;
	float	m_PlayerDist;	// 플레이어와 자신의 사이 거리
	float	m_PlayerDistMin;	// 플레이어와 자신의 사이가 이거보다 작거나 같으면 몬스터를 멈춘다
	float	m_PlayerDistMax;	// 플레이어와 자신의 사이가 이거보다 작거나 같을때만 몬스터를 움직이게 한다
	bool	m_AttackCoolDown;
	bool	m_Follow;	// 플레이어를 따라간다
	bool	m_FollowFirst;	// Follow가 처음 진행됐는지
	bool	m_InsideLimit;
	bool	m_OutsideLimit;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CMonster* Clone() = 0;
	virtual void Destroy();

protected:
	virtual void OnCollisionBegin(const CollisionResult& result);
	virtual void OnCollisionEnd(const CollisionResult& result);

public:
	Monster_State GetState()	const
	{
		return m_State;
	}

	const Vector3& GetPlayerDir()	const
	{
		return m_PlayerDir;
	}

protected:
	virtual void Calc(float DeltaTime);

protected:
	virtual void PaperBurnEnd();
	virtual void Dead(float DeltaTime);
	virtual void Hit(float DeltaTime);
	virtual void Move(float DeltaTime);
	virtual void Attack(float DeltaTime);

protected:
	virtual void PlaySoundDie();

protected:
	virtual void HideAllWeapon();
	virtual void UpdateAttackCoolDown(float DeltaTime);
	virtual void UpdateGun();
	virtual void UpdateGunDir(CSpriteComponent* Weapon);

private:
	Vector3 RandomPos()	const;
};

