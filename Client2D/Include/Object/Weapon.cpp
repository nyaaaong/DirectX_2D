
#include "Weapon.h"
#include "../Object/WeaponAnimation.h"
#include "Component/SpriteComponent.h"

CWeapon::CWeapon()	:
	m_WeaponSlot(Weapon_Slot::None),
	m_CharacterType(Character_Type::Player)
{
	SetTypeID<CWeapon>();
}

CWeapon::CWeapon(const CWeapon& obj)	:
	CGameObject(obj)
{
	SetTypeID<CWeapon>();

	m_Sprite = (CSpriteComponent*)FindComponent("WeaponSprite");

	m_WeaponSlot = obj.m_WeaponSlot;
	m_CharacterType = obj.m_CharacterType;
}

CWeapon::~CWeapon()
{
}

bool CWeapon::Init()
{
	if (!CGameObject::Init())
		return false;
	
	m_Sprite = CreateComponent<CSpriteComponent>("WeaponSprite");
	m_Sprite->CreateAnimationInstance<CWeaponAnimation>();

	SetRootComponent(m_Sprite);

	return true;
}

void CWeapon::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_WeaponSlot == Weapon_Slot::None)
		m_Sprite->SetRender(false);

	else
		m_Sprite->SetRender(true);
}

void CWeapon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CWeapon* CWeapon::Clone()
{
	return DBG_NEW CWeapon(*this);
}
