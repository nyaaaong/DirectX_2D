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
	bool			m_HitObject;

public:
	void HitObject(bool IsHit)
	{
		m_HitObject = IsHit;
	}

public:
	virtual bool Init();
	virtual void First();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBulletDummy* Clone();
};