#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CWeaponAnimation :
    public CAnimationSequence2DInstance
{
public:
	CWeaponAnimation();
	CWeaponAnimation(const CWeaponAnimation& Anim);
	~CWeaponAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CWeaponAnimation* Clone();

private:
	void Revolver();
	void Rifle();
	void Sniper();
};

