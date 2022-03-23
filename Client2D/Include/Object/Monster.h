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
	float	m_BurnStartDelay;
	float	m_BurnStartDelayMax;
	float	m_MoveTimer;
	float	m_MoveTimerMax;
	class CPlayer2D* m_Player;
	Vector3	m_PlayerPos; // 몬스터기준 플레이어의 위치
	Vector3	m_PlayerWorldPos; // 월드상의 플레이어 위치
	Vector3	m_PlayerDir; // 몬스터기준 플레이어의 방향
	Vector3	m_RandomDir; // 랜덤한 방향
	Monster_State	m_State;
	bool	m_Follow;	// 플레이어를 따라간다
	bool	m_FollowFirst;	// Follow가 처음 진행됐는지
	bool	m_InsideLimit;
	CSharedPtr<class CNavAgent>	m_NavAgent;

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

	const Vector3& GetPlayerPos()	const
	{
		return m_PlayerPos;
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
};

