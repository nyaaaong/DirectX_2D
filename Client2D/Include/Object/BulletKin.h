#pragma once

#include "Character.h"

class CBulletKin :
	public CCharacter
{
	friend class CScene;

protected:
	CBulletKin();
	CBulletKin(const CBulletKin& obj);
	virtual ~CBulletKin();

private:
	float	m_BurnStartDelay;
	float	m_BurnStartDelayMax;

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
	virtual void Dead(float DeltaTime);
	virtual void Hit(float DeltaTime);
};

