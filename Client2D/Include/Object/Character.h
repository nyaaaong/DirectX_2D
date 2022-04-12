#pragma once

#include "GameObject\GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/PaperBurnComponent.h"
#include "Component/ColliderBox2D.h"

class CCharacter :
	public CGameObject
{
	friend class CScene;

protected:
	CCharacter();
	CCharacter(const CCharacter& obj);
	virtual ~CCharacter();

protected:
	CSharedPtr<CColliderBox2D>       m_Body;
	CSharedPtr<CPaperBurnComponent>   m_PaperBurn;
	float	m_PrevHP;
	float	m_HP;
	float	m_HPMax;
	float	m_HitEffectTime;
	float	m_HitEffectTimeMax;
	float	m_MoveSpeed;
	float	m_TopOffsetY; // 타일체크용
	float	m_BottomOffsetY; // 타일체크용
	float	m_Damage;
	bool	m_IsDied;
	bool	m_IsPaperBurn;
	bool	m_Hit;
	bool	m_IsPlayedHitSound;
	bool	m_UsePaperburn;
	bool	m_Invincibility;
	Character_Type	m_Type;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CCharacter* Clone() = 0;
	virtual void Destroy();

public:
	virtual void OnCollisionBegin(const CollisionResult& result);
	virtual void OnCollisionEnd(const CollisionResult& result);

public:
	bool IsInvincibility()	const
	{
		return m_Invincibility;
	}

	bool IsHit()	const
	{
		return m_Hit;
	}

	Character_Type GetType()	const
	{
		return m_Type;
	}

	float GetDamage()	const
	{
		return m_Damage;
	}

public:
	void SetHP(float HP)
	{
		m_HP = HP;

		if (m_HP < 0.f)
			m_HP = 0.f;

		else if (m_HP >= m_HPMax)
			m_HP = m_HPMax;
	}

	virtual bool AddDamage(float Damage)
	{
		m_PrevHP = m_HP;
		m_HP -= Damage;

		if (m_Type == Character_Type::Player)
		{
			if (m_HP < 1.f)
				m_HP = 1.f;
		}

		else
		{
			if (m_HP <= 0.f)
				m_HP = 0.f;
		}

		return true;
	}

	void AddHP(float HP)
	{
		m_PrevHP = m_HP;
		m_HP += HP;

		if (m_HP > m_HPMax)
			m_HP = m_HPMax;
	}

protected:
	virtual void Calc(float DeltaTime);
	virtual void PaperBurnEnd();
	virtual void Dead(float DeltaTime);
	virtual void Hit(float DeltaTime);

protected:
	bool IsWallTile(const Vector3& NextWorldPos)	const;
};

