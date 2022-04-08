#pragma once

#include "GameObject/GameObject.h"
#include "Component/ColliderBox2D.h"

class CDummy :
	public CGameObject
{
	friend class CScene;

protected:
	CDummy();
	CDummy(const CDummy& obj);
	virtual ~CDummy();

private:
	CSharedPtr<CColliderBox2D>       m_Body;

public:
	void SetPivot(float x, float y, float z)
	{
		m_Body->SetPivot(x, y, z);
	}

	void SetPivot(const Vector3& v)
	{
		m_Body->SetPivot(v);
	}

	void SetExtent(float x, float y)
	{
		m_Body->SetExtent(x, y);
	}

	void SetExtent(const Vector2& Size)
	{
		m_Body->SetExtent(Size);
	}

	void SetCollisionProfile(const std::string& Name)
	{
		m_Body->SetCollisionProfile(Name);
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CDummy* Clone();
};
