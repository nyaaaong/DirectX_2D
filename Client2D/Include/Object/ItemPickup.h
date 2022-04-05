#pragma once

#include "GameObject\GameObject.h"

class CItemPickup :
    public CGameObject
{
	friend class CScene;

protected:
	CItemPickup();
	CItemPickup(const CItemPickup& obj);
	virtual ~CItemPickup();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CItemPickup* Clone();
};