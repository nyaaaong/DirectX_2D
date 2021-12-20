
#include "ExcelManager.h"
#include "include_cpp/libxl.h"
#include "Excel.h"
#include "Character/Excel_Player.h"

DEFINITION_SINGLE(CExcelManager)

CExcelManager::CExcelManager()	:
	m_PlayerInfo(nullptr)
{
}

CExcelManager::~CExcelManager()
{
	SAFE_DELETE(m_PlayerInfo);
}

bool CExcelManager::Init()
{
	m_PlayerInfo = new CExcel_Player;

	if (!m_PlayerInfo->Init())
		return false;

	return true;
}
