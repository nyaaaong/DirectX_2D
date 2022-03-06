
#include "PlayerAnimation2D.h"

CPlayerAnimation2D::CPlayerAnimation2D()
{
	SetTypeID<CPlayerAnimation2D>();
}

CPlayerAnimation2D::CPlayerAnimation2D(const CPlayerAnimation2D& Anim)	:
	CAnimationSequence2DInstance(Anim)
{
}

CPlayerAnimation2D::~CPlayerAnimation2D()
{
}

bool CPlayerAnimation2D::Init()
{
	if (!CAnimationSequence2DInstance::Init())
		return false;

	Idle();
	Walk();
	Dodge();
	Death();
	Fall();
	GetItem();
	Respawn();


	//SetEndFunction<CPlayerAnimation2D>("PlayerDodgeD", this, &CPlayerAnimation2D::DefaultAnimation);
	Play();

	SetCurrentAnimation("Player_Idle_D");

	return true;
}

CPlayerAnimation2D* CPlayerAnimation2D::Clone()
{
	return DBG_NEW CPlayerAnimation2D(*this);
}

void CPlayerAnimation2D::Idle()
{
	AddAnimation(TEXT("Player/Idle/Player_Idle_D.sqc"), "Player_Idle_D", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Idle/Player_Idle_DL.sqc"), "Player_Idle_DL", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Idle/Player_Idle_DR.sqc"), "Player_Idle_DR", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Idle/Player_Idle_U.sqc"), "Player_Idle_U", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Idle/Player_Idle_UL.sqc"), "Player_Idle_UL", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Idle/Player_Idle_UR.sqc"), "Player_Idle_UR", ANIMATION_PATH);
}

void CPlayerAnimation2D::Walk()
{
	AddAnimation(TEXT("Player/Walk/Player_Walk_D.sqc"), "Player_Walk_D", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Walk/Player_Walk_DL.sqc"), "Player_Walk_DL", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Walk/Player_Walk_DR.sqc"), "Player_Walk_DR", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Walk/Player_Walk_U.sqc"), "Player_Walk_U", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Walk/Player_Walk_UL.sqc"), "Player_Walk_UL", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Walk/Player_Walk_UR.sqc"), "Player_Walk_UR", ANIMATION_PATH);
}

void CPlayerAnimation2D::Dodge()
{
	AddAnimation(TEXT("Player/Dodge/Player_Dodge_D.sqc"), "Player_Dodge_D", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Dodge/Player_Dodge_DL.sqc"), "Player_Dodge_DL", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Dodge/Player_Dodge_DR.sqc"), "Player_Dodge_DR", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Dodge/Player_Dodge_U.sqc"), "Player_Dodge_U", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Dodge/Player_Dodge_UL.sqc"), "Player_Dodge_UL", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Dodge/Player_Dodge_UR.sqc"), "Player_Dodge_UR", ANIMATION_PATH);
}

void CPlayerAnimation2D::Death()
{
	AddAnimation(TEXT("Player/Death/Player_Death.sqc"), "Player_Death", ANIMATION_PATH);
	AddAnimation(TEXT("Player/Death/Player_Death_1.sqc"), "Player_Death_1", ANIMATION_PATH);
}

void CPlayerAnimation2D::Fall()
{
	AddAnimation(TEXT("Player/Fall/Player_Fall.sqc"), "Player_Fall", ANIMATION_PATH);
}

void CPlayerAnimation2D::GetItem()
{
	AddAnimation(TEXT("Player/GetItem/Player_GetItem.sqc"), "Player_GetItem", ANIMATION_PATH);
}

void CPlayerAnimation2D::Respawn()
{
	AddAnimation(TEXT("Player/Respawn/Player_Respawn.sqc"), "Player_Respawn", ANIMATION_PATH);
}