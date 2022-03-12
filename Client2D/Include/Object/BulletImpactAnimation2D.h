#pragma once

#include "Animation\AnimationSequence2DInstance.h"

class CBulletImpactAnimation2D :
    public CAnimationSequence2DInstance
{
public:
	CBulletImpactAnimation2D();
	CBulletImpactAnimation2D(const CBulletImpactAnimation2D& Anim);
	~CBulletImpactAnimation2D();

public:
	virtual bool Init();
	virtual CBulletImpactAnimation2D* Clone();

private:
};

