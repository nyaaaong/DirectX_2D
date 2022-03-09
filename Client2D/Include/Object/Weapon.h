#pragma once

#include "GameObject\GameObject.h"

class CWeapon :
    public CGameObject
{
	friend class CScene;

protected:
	CWeapon();
	CWeapon(const CWeapon& obj);
	virtual ~CWeapon();

private:
	Vector3	m_MousePos;
	Weapon_Slot	m_WeaponSlot;
	Character_Type m_CharacterType;
	Vector3	m_MouseDir;

public:
	Weapon_Slot GetWeaponSlot()	const
	{
		return m_WeaponSlot;
	}

	Character_Type GetCharacterType()	const
	{
		return m_CharacterType;
	}

public:
	void SetMouseDir(const Vector3& Dir)
	{
		m_MouseDir = Dir;
	}

	void SetCharacterType(Character_Type Type)
	{
		m_CharacterType = Type;
	}

	void SetMousePos(const Vector3& MousePos)
	{
		m_MousePos = MousePos;
	}

	void SetWeaponSlot(Weapon_Slot Slot)
	{
		m_WeaponSlot = Slot;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CWeapon* Clone();
};

