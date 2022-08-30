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
	Monster_State		m_State;
	BulletKing_State	m_BulletKingPrevState;
	BulletKing_State	m_BulletKingState;
	float	m_BurnStartDelay;
	float	m_BurnStartDelayMax;
	float	m_AttackDelay;
	float	m_AttackDelayMax;
	float	m_MoveDelay;
	float	m_MoveDelayMax;
	float	m_PlayerAngle;
	float	m_PlayerDist;	// 플레이어와 자신의 사이 거리
	float	m_PlayerDistMin;	// 플레이어와 거리가 얼마나 될때까지 접근할지 (보스용)
	float	m_UpdateSight;
	float	m_PatternTimer;
	float	m_PatternTimerMax;
	float	m_PatternTime[(int)BulletKing_State::Max];
	float	m_PatternTimeMax[(int)BulletKing_State::Max];
	bool	m_StartDestroyBefore;
	bool	m_ChangePattern;
	bool	m_Move;
	bool	m_CanUpdate;
	bool	m_UseGun;
	bool	m_UseDropItem;
	bool	m_UsePattern;
	bool	m_arrDropItem[(int)DropItem_Type::Max];
	bool	m_IsBulletKing;
	bool	m_NeedPatternChange;
	bool	m_NeedPatternChangeIdle;
	bool	m_NeedConnectPatternChange;
	bool	m_DieProgress;
	bool	m_DieEndProgress;
	bool	m_DieFinish;
	bool	m_DieEndFinish;
	bool	m_CurBossAnimComplete;
	bool	m_CurBossChairAnimComplete;
	bool	m_AttackOncePattern1;
	bool	m_AttackOncePattern2;
	bool	m_AttackOncePattern3;
	bool	m_AttackOncePattern4;
	// 패턴이 끝났다면 교체를 위해 true를 리턴한다.
	std::function<void(float)>	m_CurPattern;
	std::vector<std::function<void(float)>>	m_vecPattern;
	std::unordered_map<BulletKing_State, std::function<void(float)>>	m_mapConnectPattern;

public:
	bool IsDropItemType(DropItem_Type Type)
	{
		return m_arrDropItem[(int)Type];
	}

	bool IsDropItemType(int Type)
	{
		return m_arrDropItem[Type];
	}

	BulletKing_State GetBulletKingPrevState()	const
	{
		return m_BulletKingPrevState;
	}

	BulletKing_State GetBulletKingState()	const
	{
		return m_BulletKingState;
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
		m_arrDropItem[(int)Type] = true;
	}

	void DeleteDropItemType(DropItem_Type Type)
	{
		m_arrDropItem[(int)Type] = false;
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
	virtual void DieAnim(float DeltaTime);
	virtual void DieAnim_End(float DeltaTime);
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

private:
	Vector3 RandomPos()	const;
	void UpdateAttack(float DeltaTime);
	void UpdateMove(float DeltaTime);

protected:
	int CreateRandomIndex();
	void UpdatePattern(float DeltaTime);

protected:
	virtual void Idle(float DeltaTime);

protected:
	template <typename T>
	void AddPattern(T* Obj, void(T::* Func)(float))
	{
		m_vecPattern.push_back(std::bind(Func, Obj, std::placeholders::_1));
	}

	template <typename T>
	void AddConnectPattern(BulletKing_State State, T* Obj, void(T::* Func)(float))
	{
		m_mapConnectPattern.insert(std::make_pair(State, std::bind(Func, Obj, std::placeholders::_1)));
	}
};

