
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

	AddAnimation(TEXT("Player/Idle/Player_Idle_D.sqc"), "Player_Idle_D", ANIMATION_PATH);

	//SetEndFunction<CPlayerAnimation2D>("PlayerDodgeD", this, &CPlayerAnimation2D::DefaultAnimation);
	Play();

	return true;
}

CPlayerAnimation2D* CPlayerAnimation2D::Clone()
{
	return DBG_NEW CPlayerAnimation2D(*this);
}
