#pragma once

#include "Animation\AnimationSequence2DInstance.h"

class CBulletAnim :
	public CAnimationSequence2DInstance
{
public:
	CBulletAnim();
	CBulletAnim(const CBulletAnim& Anim);
	~CBulletAnim();

private:
	bool	m_HitObject;

public:
	void HitObject(bool IsHit)
	{
		m_HitObject = IsHit;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void First();
	virtual CBulletAnim* Clone();
};

