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
	float	m_AttackDelay;
	float	m_AttackDelayMax;
	float	m_MoveDelay;
	float	m_MoveDelayMax;
	float	m_PlayerAngle;
	float	m_PlayerDist;	// 플레이어와 자신의 사이 거리
	float	m_UpdateSight;
	float	m_PatternTimer;
	float	m_PatternTimerMax;
	bool	m_StartDestroyBefore;
	bool	m_ChangePattern;
	bool	m_Move;
	bool	m_CanUpdate;
	bool	m_UseGun;
	bool	m_UseDropItem;
	bool	m_UsePattern;
	bool	m_arrDropItem[(int)DropItem_Type::Max];
	std::function<void(float)>	m_CurPattern;

public:
	bool IsDropItemType(DropItem_Type Type)
	{
		return m_arrDropItem[(int)Type];
	}

	bool IsDropItemType(int Type)
	{
		return m_arrDropItem[Type];
	}

	Monster_State GetState()	const
	{
		return m_State;
	}

	const Vector3& GetPlayerDir()	const
	{
		return m_PlayerDir;
	}

public:
	void SetDropItemType(DropItem_Type Type)
	{
		switch (Type)
		{
		case DropItem_Type::Rifle:
		case DropItem_Type::Sniper:
		case DropItem_Type::Life:
			m_arrDropItem[(int)Type] = true;
			break;
		}
	}

	void DeleteDropItemType(DropItem_Type Type)
	{
		switch (Type)
		{
		case DropItem_Type::Rifle:
		case DropItem_Type::Sniper:
		case DropItem_Type::Life:
			m_arrDropItem[(int)Type] = false;
			break;
			break;
		}
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CMonster* Clone() = 0;
	virtual void Destroy();

protected:
	virtual void OnCollisionBegin(const CollisionResult& result);
	virtual void OnCollisionEnd(const CollisionResult& result);

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
	virtual void DestroyBefore();

protected:
	virtual void HideAllWeapon();
	virtual void UpdateGun();
	virtual void UpdateGunDir(CSpriteComponent* Weapon);
	virtual void UpdateDropItemType();
	virtual void DropItem();
	virtual void CreateItem(DropItem_Type Type);
	// 패턴이 바뀔 때 실행되는 함수
	virtual void ChangePatternStartFunc(float DeltaTime);

private:
	Vector3 RandomPos()	const;
	void ChangePattern(float DeltaTime);
	void SetCurrentPattern(void(CMonster::*Func)(float));
	void UpdateAttack(float DeltaTime);
	void UpdateMove(float DeltaTime);
};

