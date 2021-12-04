#pragma once

#include "../Excel.h"

class CExcel_Player :
    public CExcel
{
	friend class CExcelManager;

protected:
	CExcel_Player();
	virtual ~CExcel_Player();

public:
	virtual bool Init();
};

