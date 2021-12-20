#pragma once

#include "../GameInfo.h"

class CExcelManager
{
private:
	class CExcel* m_PlayerInfo;

public:
	bool Init();

	DECLARE_SINGLE(CExcelManager)
};

