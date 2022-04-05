#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CItemAnim :
    public CAnimationSequence2DInstance
{
public:
	CItemAnim();
	CItemAnim(const CItemAnim& Anim);
	virtual ~CItemAnim();

protected:
	bool	m_PlayEnd;	// 한번 애니메이션이 실행 됐는지

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CItemAnim* Clone();
};

