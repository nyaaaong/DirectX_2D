#pragma once

#include "Monster.h"

class CBulletKin :
	public CMonster
{
	friend class CScene;

protected:
	CBulletKin();
	CBulletKin(const CBulletKin& obj);
	virtual ~CBulletKin();

public:
	class CSpriteComponent* GetSpriteComponent()    const
	{
		return m_Sprite;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBulletKin* Clone();
	virtual void Destroy();

protected:
	virtual void OnCollisionBegin(const CollisionResult& result);

protected:
	virtual void PaperBurnEnd();
	virtual void Dead();
	virtual void Hit(float DeltaTime);
};

