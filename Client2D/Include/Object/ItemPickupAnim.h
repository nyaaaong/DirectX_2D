#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CItemPickupAnim :
    public CAnimationSequence2DInstance
{
public:
	CItemPickupAnim();
	CItemPickupAnim(const CItemPickupAnim& Anim);
	virtual ~CItemPickupAnim();

public:
	virtual bool Init();
	virtual CItemPickupAnim* Clone();
};

