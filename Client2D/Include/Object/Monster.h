#pragma once

#include "GameObject\GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/PaperBurnComponent.h"
#include "Component/ColliderBox2D.h"

class CMonster :
	public CGameObject
{
	friend class CScene;

protected:
	CMonster();
	CMonster(const CMonster& obj);
	virtual ~CMonster() = 0;

protected:
	CSharedPtr<CColliderBox2D>       m_Body;
	CSharedPtr<CPaperBurnComponent>   m_PaperBurn;
	float	m_HP;
	float	m_HitEffectTime;
	float	m_HitEffectTimeMax;
	bool	m_IsDied;
	bool	m_IsPaperBurn;
	bool	m_Hit;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CMonster* Clone() = 0;
	virtual void Destroy();

public:
	virtual void OnCollisionBegin(const CollisionResult& result);

protected:
	virtual void PaperBurnEnd();
	virtual void Dead();
	virtual void Hit(float DeltaTime);
};

