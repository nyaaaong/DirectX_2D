#pragma once

#include "Mash.h"

class CSpriteMesh :
    public CMash
{
	friend class CResourceManager;

protected:
	CSpriteMesh();
	virtual ~CSpriteMesh();

public:
	virtual bool Init();
};

