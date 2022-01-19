#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderCircle.h"
#include "Component/WidgetComponent.h"

class CMonster :
    public CGameObject
{
    friend class CScene;

protected:
    CMonster();
    CMonster(const CMonster& obj);
    virtual ~CMonster();

private:
    CSharedPtr<CSpriteComponent>    m_Sprite;
    CSharedPtr<CColliderCircle>       m_Body;
	int		m_HP;
	int		m_HPMax;

	CSharedPtr<CWidgetComponent>     m_SimpleHUDWidget;
	class CSimpleHUD* m_SimpleHUD;

public:
	void SetDamage(int Value)
	{
		m_HP -= Value;

		if (m_HP <= 0)
			Destroy();
	}

public:
	virtual void Destroy();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CMonster* Clone();

public:
	void OnMouseBegin(const CollisionResult& result);
	void OnMouseEnd(const CollisionResult& result);
};

