#pragma once

#include "GameObject/GameObject.h"

class CBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CBullet();
    CBullet(const CBullet& obj);
    virtual ~CBullet();

private:
    CSharedPtr<class CSpriteComponent>    m_Sprite;
	float   m_Distance;
	CSharedPtr<class CColliderCircle>	m_Body;
	CGameObject* m_Owner;
	bool			m_NeedChangeOwner;

public:
	void SetOwner(CGameObject* Owner)
	{
		m_NeedChangeOwner = true;

		m_Owner = Owner;
	}

public:
	void SetDamage(const CollisionResult& result);

public:
	virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBullet* Clone();
};

