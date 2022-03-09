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
	CSharedPtr<class CWeapon>     m_WeaponObject;
	bool	m_EnableInput;
	bool	m_Move;
	bool	m_AttackCoolDown;
	float       m_Opacity;
	float	m_AttackTimer;
	float	m_AttackTimerMax;
	float	m_MoveSpeed;	
	float	m_DodgeSpeed;	
	Vector3	m_PrevPos;
	int		m_Dir;
	bool	m_SetCameraInfo;
	float	m_DodgeTimer;
	float	m_DodgeTimerMax;
	bool	m_DodgeCoolDown;
	Vector3	m_MouseDir;

public:
	const Vector3& GetMouseDir()	const
	{
		return m_MouseDir;
	}

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
	void Attack(float DeltaTime);
	void DodgeStart(float DeltaTime);
	void Dodge(float DeltaTime);
	void NoWeapon(float DeltaTime);
	void Weapon1(float DeltaTime);
	void Weapon2(float DeltaTime);
	void Weapon3(float DeltaTime);

public:
	void SetDir(Character_Direction Dir);
	void ClearDir(Character_Direction Dir);

private:
	void UpdateMousePos();
	void UpdateAnimDir();

private:
	void ChangeAnimIdle();
	void ChangeAnimWalk();
	void ChangeAnimDodge();

private:
	bool IsNormalTile(const Vector3& NextWorldPos);
};

