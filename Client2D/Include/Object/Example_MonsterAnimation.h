#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class ExampleCMonsterAnimation :
    public CAnimationSequence2DInstance
{
public:
	ExampleCMonsterAnimation();
	ExampleCMonsterAnimation(const ExampleCMonsterAnimation& Anim);
	~ExampleCMonsterAnimation();

public:
	virtual bool Init();
	virtual ExampleCMonsterAnimation* Clone();
};

