#pragma once

#include "GameObject/GameObject.h"
#include "Component/ColliderBox2D.h"

class CItem :
	public CGameObject
{
	friend class CScene;

protected:
	CItem();
	CItem(const CItem& obj);
	virtual ~CItem();

protected:
	CSharedPtr<class CPlayer2D>		m_Player;
	CSharedPtr<CColliderBox2D>		m_Body;

public:
	virtual void Start();
	virtual bool Init();
	virtual CItem* Clone();
	virtual void Destroy();

public:
	virtual void OnCollisionBegin(const CollisionResult& result);
};