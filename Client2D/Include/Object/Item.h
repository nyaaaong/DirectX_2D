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
	Item_Type		m_Type;
	bool			m_CompleteAnim;
	float			m_AnimSpeed;
	float			m_Bottom;
	float			m_BottomMin;
	float			m_BottomMax;
	float			m_DirY;
	bool			m_MinCheck;
	bool			m_MaxCheck;

public:
	virtual void Start();
	virtual void First();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CItem* Clone();
	virtual void Destroy();

public:
	virtual void OnCollisionBegin(const CollisionResult& result);
};