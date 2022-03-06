#pragma once

#include "ColliderComponent.h"

class CColliderBox2D :
    public CColliderComponent
{
    friend class CGameObject;

protected:
    CColliderBox2D();
    CColliderBox2D(const CColliderBox2D& com);
    virtual ~CColliderBox2D();

protected:
	Box2DInfo   m_Info;

public:
	Box2DInfo GetInfo() const
	{
		return m_Info;
	}

	void SetExtent(float Width, float Height)
	{
		m_Info.Length.x = Width;
		m_Info.Length.y = Height;

		SetWorldScale(m_Info.Length.x, m_Info.Length.y, 1.f);
	}

	void SetExtent(const Vector2& Size)
	{
		SetExtent(Size.x, Size.y);
	}

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void PrevRender();
    virtual void Render();
    virtual void PostRender();
    virtual CColliderBox2D* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
	virtual bool Collision(CColliderComponent* Dest);
	virtual bool CollisionMouse(const Vector2& MousePos);
};

