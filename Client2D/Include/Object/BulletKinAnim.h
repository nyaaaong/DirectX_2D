#pragma once

#include "Animation\AnimationSequence2DInstance.h"

class CBulletKinAnim :
    public CAnimationSequence2DInstance
{
public:
	CBulletKinAnim();
	CBulletKinAnim(const CBulletKinAnim& Anim);
	~CBulletKinAnim();

public:
	virtual void Start();
	virtual bool Init();
	virtual CBulletKinAnim* Clone();
};

