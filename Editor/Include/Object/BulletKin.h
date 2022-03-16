#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/PaperBurnComponent.h"
#include "Component/ColliderBox2D.h"

class CBulletKin :
	public CGameObject
{
	friend class CScene;

protected:
	CBulletKin();
	CBulletKin(const CBulletKin& obj);
	virtual ~CBulletKin();

private:
	CSharedPtr<CColliderBox2D>       m_Body;
	CSharedPtr<CPaperBurnComponent>   m_PaperBurn;
	float	m_HP;
	float	m_HitEffectTime;
	float	m_HitEffectTimeMax;
	bool	m_IsDied;
	bool	m_IsPaperBurn;
	bool	m_Hit;

public:
	class CSpriteComponent* GetSpriteComponent()    const
	{
		return m_Sprite;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBulletKin* Clone();
public:
	void OnCollisionBegin(const CollisionResult& result);

private:
	void PaperBurnEnd();
	void Dead();

private:
	void Hit(float DeltaTime);
};

