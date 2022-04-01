#pragma once

#include "Animation\AnimationSequence2DInstance.h"

class CBulletAnim :
	public CAnimationSequence2DInstance
{
public:
	CBulletAnim();
	CBulletAnim(const CBulletAnim& Anim);
	virtual ~CBulletAnim();

private:
	bool	m_GrayEffect;

public:
	void SetGrayColor(bool IsGray)
	{
		m_GrayEffect = IsGray;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void First();
	virtual CBulletAnim* Clone();
};

