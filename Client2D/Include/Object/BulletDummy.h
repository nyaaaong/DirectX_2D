#pragma once

#include "GameObject\GameObject.h"

class CBulletDummy :
	public CGameObject
{
	friend class CScene;

protected:
	CBulletDummy();
	CBulletDummy(const CBulletDummy& obj);
	virtual ~CBulletDummy();

private:
	bool			m_GrayEffect;

public:
	void SetGrayColor(bool IsGray)
	{
		m_GrayEffect = IsGray;
	}

public:
	bool IsAnimEnd()	const;

public:
	virtual bool Init();
	virtual void First();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBulletDummy* Clone();
};