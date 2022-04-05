#pragma once

#include "Character.h"
#include "Component/CameraComponent.h"
#include "Component/WidgetComponent.h"

class CPlayer2D :
	public CCharacter
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& obj);
	virtual ~CPlayer2D();

private:
	CSharedPtr<CCameraComponent>	m_Camera;
	CSharedPtr<CWidgetComponent>	m_SimpleHUDWidget;
	CSharedPtr<CSpriteComponent>	m_Weapon1;
	CSharedPtr<CSpriteComponent>	m_Weapon1L;
	CSharedPtr<CSpriteComponent>	m_Weapon2;
	CSharedPtr<CSpriteComponent>	m_Weapon2L;
	CSharedPtr<CSpriteComponent>	m_Weapon3;
	CSharedPtr<CSpriteComponent>	m_Weapon3L;
	CSpriteComponent*	m_CurWeapon;
	Vector3	m_PrevPos;
	Vector3	m_MouseDir;
	Weapon_Slot	m_WeaponSlot;
	bool	m_EnableInput;
	bool	m_Move;
	bool	m_AttackCoolDown;
	bool	m_SetCameraInfo;
	bool	m_DodgeCoolDown;
	bool	m_PierceBullet;
	bool	m_HasRifle;
	bool	m_HasSniper;
	float   m_Opacity;
	float	m_AttackDelay;
	float	m_AttackDelayMax;
	float	m_DodgeSpeed;
	float	m_DodgeTimer;
	float	m_DodgeTimerMax;
	float	m_MouseAngle;
	int		m_Dir;
	int		m_MoveDir;

public:
	bool HasWeaponRifle()	const
	{
		return m_HasRifle;
	}

	bool HasWeaponSniper()	const
	{
		return m_HasSniper;
	}

	float GetMouseAngle()	const
	{
		return m_MouseAngle;
	}

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

	bool IsMoveDir(Character_Direction Dir)
	{
		return m_MoveDir & (int)Dir;
	}

	bool IsMove()	const
	{
		return m_Move;
	}

public:
	void AddWeaponRifle();
	void AddWeaponSniper();

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

private:
	void HideAllWeapon();

public:
	void SetDir(Character_Direction Dir);
	void SetMoveDir(Character_Direction Dir);
	void DeleteDir(Character_Direction Dir);
	void DeleteMoveDir(Character_Direction Dir);

private:
	void UpdateAttackCoolDown(float DeltaTime);
	void UpdateDodgeCoolDown(float DeltaTime);
	void UpdateMousePos();
	void UpdateGun();
	void UpdateGunDir(CSpriteComponent* Weapon);
	void UpdateAnimDir();

private:
	void ChangeAnimIdle();
	void ChangeAnimWalk();
	void ChangeAnimDodge();
};

