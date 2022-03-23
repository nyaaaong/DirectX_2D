#pragma once

#include "Animation\AnimationSequence2DInstance.h"

class CMonsterAnim :
	public CAnimationSequence2DInstance
{
public:
	CMonsterAnim();
	CMonsterAnim(const CMonsterAnim& Anim);
	virtual ~CMonsterAnim();

protected:
	class CMonster*	m_OwnerObject;
	bool	m_PlayDie;	// �ѹ� �ִϸ��̼��� ���� �ƴ���

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CMonsterAnim* Clone() = 0;

protected:
	void ChangeAnimDir();

protected:
	virtual void ChangeAnimLeft();
	virtual void ChangeAnimRight();
};

