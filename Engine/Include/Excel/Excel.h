#pragma once

#include "../GameInfo.h"

class CExcel
{
	friend class CExcelManager;

protected:
	CExcel();
	virtual ~CExcel();

protected:
	libxl::Book* book;

public:
	virtual bool Init();

protected:
	bool Load(const wchar_t* FileName, const wchar_t* MiddlePath);
};

