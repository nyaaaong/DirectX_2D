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
	bool	m_PlayEnd;	// �ѹ� �ִϸ��̼��� ���� �ƴ���

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CItemAnim* Clone();
};

