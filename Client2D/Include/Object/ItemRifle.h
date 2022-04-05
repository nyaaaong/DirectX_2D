#pragma once

#include "Item.h"

class CItemRifle :
    public CItem
{
	friend class CScene;

protected:
	CItemRifle();
	CItemRifle(const CItemRifle& obj);
	virtual ~CItemRifle();

public:
	virtual bool Init();
	virtual CItemRifle* Clone();

public:
	virtual void OnCollisionBegin(const CollisionResult& result);
};

