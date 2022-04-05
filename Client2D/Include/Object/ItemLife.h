#pragma once

#include "Item.h"

class CItemLife :
	public CItem
{
	friend class CScene;

protected:
	CItemLife();
	CItemLife(const CItemLife& obj);
	virtual ~CItemLife();

public:
	virtual bool Init();
	virtual CItemLife* Clone();
};