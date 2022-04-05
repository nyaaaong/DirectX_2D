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
};