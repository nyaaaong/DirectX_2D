#pragma once

#include "Item.h"

class CItemSniper :
    public CItem
{
	friend class CScene;

protected:
	CItemSniper();
	CItemSniper(const CItemSniper& obj);
	virtual ~CItemSniper();

public:
	virtual bool Init();
	virtual CItemSniper* Clone();

public:
	virtual void OnCollisionBegin(const CollisionResult& result);
};

