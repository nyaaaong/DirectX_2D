
#include "PlayerAnimation2D.h"

CPlayerAnimation2D::CPlayerAnimation2D()
{
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

	AddAnimation("PlayerIdleD", "PlayerIdleD", true, 0.3f);
	/*AddAnimation("PlayerIdleL", "PlayerIdleL", true, 0.3f);
	AddAnimation("PlayerIdleR", "PlayerIdleR", true, 0.3f);
	AddAnimation("PlayerIdleU", "PlayerIdleU", true, 0.3f);*/

	AddAnimation("PlayerDodgeD", "PlayerDodgeD", false, 0.4f);
	/*AddAnimation("PlayerDodgeL", "PlayerDodgeL", false, 0.4f);
	AddAnimation("PlayerDodgeR", "PlayerDodgeR", false, 0.4f);
	AddAnimation("PlayerDodgeU", "PlayerDodgeU", false, 0.4f);*/

	SetEndFunction<CPlayerAnimation2D>("PlayerDodgeD", this, &CPlayerAnimation2D::DefaultAnimation);

	return true;
}

CPlayerAnimation2D* CPlayerAnimation2D::Clone()
{
	return DBG_NEW CPlayerAnimation2D(*this);
}

void CPlayerAnimation2D::DefaultAnimation()
{
	ChangeAnimation("PlayerIdleD");
}
