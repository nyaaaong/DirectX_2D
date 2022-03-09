
#include "WeaponAnimation.h"
#include "Weapon.h"
#include "Component/SpriteComponent.h"

CWeaponAnimation::CWeaponAnimation()
{
	SetTypeID<CWeaponAnimation>();
}

CWeaponAnimation::CWeaponAnimation(const CWeaponAnimation& Anim) :
	CAnimationSequence2DInstance(Anim)
{
	SetTypeID<CWeaponAnimation>();
}

CWeaponAnimation::~CWeaponAnimation()
{
}

bool CWeaponAnimation::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	Revolver();
	Rifle();
	Sniper();

	SetCurrentAnimation("Revolver_R");

	return true;
}

void CWeaponAnimation::Update(float DeltaTime)
{
	CAnimationSequence2DInstance::Update(DeltaTime);

	CGameObject*	Obj = m_Owner->GetGameObject();
	CWeapon* Weapon = dynamic_cast<CWeapon*>(Obj);

	if (!Weapon)
		return;

	Character_Type	Type = Weapon->GetCharacterType();
	Weapon_Slot	Slot = Weapon->GetWeaponSlot();

	switch (Type)
	{
	case Character_Type::Player:
		switch (Slot)
		{
		case Weapon_Slot::None:
			break;
		case Weapon_Slot::Weap1:
			ChangeAnimation("Revolver_R");
			break;
		case Weapon_Slot::Weap2:
			ChangeAnimation("Rifle_R");
			break;
		case Weapon_Slot::Weap3:
			ChangeAnimation("Sniper_R");
			break;
		}
		break;
	case Character_Type::Monster:
		switch (Slot)
		{
		case Weapon_Slot::None:
			break;
		case Weapon_Slot::Weap1:
			break;
		case Weapon_Slot::Weap2:
			break;
		case Weapon_Slot::Weap3:
			break;
		}
		break;
	}
}

CWeaponAnimation* CWeaponAnimation::Clone()
{
	return DBG_NEW CWeaponAnimation(*this);
}

void CWeaponAnimation::Revolver()
{
	AddAnimation(TEXT("Weapon/Right/Revolver_R.sqc"), "Revolver_R", ANIMATION_PATH);
	AddAnimation(TEXT("Weapon/Left/Revolver_L.sqc"), "Revolver_L", ANIMATION_PATH);
}

void CWeaponAnimation::Rifle()
{
	AddAnimation(TEXT("Weapon/Right/Rifle_R.sqc"), "Rifle_R", ANIMATION_PATH);
	AddAnimation(TEXT("Weapon/Left/Rifle_L.sqc"), "Rifle_L", ANIMATION_PATH);
}

void CWeaponAnimation::Sniper()
{
	AddAnimation(TEXT("Weapon/Right/Sniper_R.sqc"), "Sniper_R", ANIMATION_PATH);
	AddAnimation(TEXT("Weapon/Left/Sniper_L.sqc"), "Sniper_L", ANIMATION_PATH);
}
