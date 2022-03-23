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
	Vector3	m_PlayerPos; // ���ͱ��� �÷��̾��� ��ġ
	Vector3	m_PlayerWorldPos; // ������� �÷��̾� ��ġ
	Vector3	m_PlayerDir; // ���ͱ��� �÷��̾��� ����
	Vector3	m_RandomDir; // ������ ����
	Monster_State	m_State;
	bool	m_Follow;	// �÷��̾ ���󰣴�
	bool	m_FollowFirst;	// Follow�� ó�� ����ƴ���
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

