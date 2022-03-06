#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CPlayerAnimation2D :
    public CAnimationSequence2DInstance
{
public:
	CPlayerAnimation2D();
	CPlayerAnimation2D(const CPlayerAnimation2D& Anim);
	~CPlayerAnimation2D();

public:
	virtual bool Init();
	virtual CPlayerAnimation2D* Clone();

private:
	void Idle();
	void Walk();
	void Dodge();
	void Death();
	void Fall();
	void GetItem();
	void Respawn();
};

