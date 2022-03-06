#pragma once

#include "GameObject/GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"

class CPlayer2D :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& obj);
	virtual ~CPlayer2D();

private:
	CSharedPtr<CColliderBox2D>       m_Body;
	CSharedPtr<CCameraComponent>     m_Camera;
	CSharedPtr<CWidgetComponent>     m_SimpleHUDWidget;
	bool        m_SolW;
	bool	m_EnableInput;
	bool	m_Dodge;
	bool	m_Move;
	bool	m_AttackCoolDown;
	float       m_WDistance;
	float       m_Opacity;
	float	m_AttackTimer;
	float	m_AttackTimerMax;
	float	m_MoveSpeed;	
	Vector3	m_PrevPos;
	int		m_Dir;
	bool	m_SetCameraInfo;

public:
	CSharedPtr<CCameraComponent> GetCameraComponent()	const
	{
		return m_Camera;
	}

	bool IsDir(Character_Direction Dir)
	{
		return m_Dir & (int)Dir;
	}

	bool IsMove()	const
	{
		return m_Move;
	}

public:
	void SetEnableInput(bool Enable)
	{
		m_EnableInput = Enable;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPlayer2D* Clone();

private:
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);
	void RotationZInv(float DeltaTime);
	void RotationZ(float DeltaTime);
	void Dodge(float DeltaTime);
	void DodgeEnd(float DeltaTime);
	void Attack(float DeltaTime);
	void Attack1(float DeltaTime);
	void test(float DeltatTime);

public:
	void SetDir(Character_Direction Dir);
	void ClearDir(Character_Direction Dir);

private:
	void UpdateAnimDir();

private:
	void Action(float DeltaTime);
	void MovePointDown(float DeltaTime);
	void PathResult(const std::list<Vector3>& PathList);

private:
	void ChangeAnimIdle();
	void ChangeAnimWalk();
};

