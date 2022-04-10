
#include "ExcelManager.h"
#include "Excel.h"
#include "../Scene/SceneManager.h"
#include "include_cpp/libxl.h"
#include "Character/Excel_Player.h"
#include "Character/Excel_Monster.h"
#include "Character/Excel_BulletKing.h"

DEFINITION_SINGLE(CExcelManager)

CExcelManager::CExcelManager()	:
	m_PlayerInfo(nullptr),
	m_MonsterInfo(nullptr),
	m_BulletKingInfo(nullptr)
{
}

CExcelManager::~CExcelManager()
{
	SAFE_DELETE(m_BulletKingInfo);
	SAFE_DELETE(m_MonsterInfo);
	SAFE_DELETE(m_PlayerInfo);
}

bool CExcelManager::Init()
{
	m_PlayerInfo = DBG_NEW CExcel_Player;
	m_MonsterInfo = DBG_NEW CExcel_Monster;
	m_BulletKingInfo = DBG_NEW CExcel_BulletKing;

	if (!m_PlayerInfo->Init())
		return false;

	if (!m_MonsterInfo->Init())
		return false;

	if (!m_BulletKingInfo->Init())
		return false;

	m_PlayerInfo->Load(L"Player.xlsx", L"Character");
	m_MonsterInfo->Load(L"Monster.xlsx", L"Character");
	m_BulletKingInfo->Load(L"Boss.xlsx", L"Character");

	return true;
}

const PlayerInfo& CExcelManager::GetPlayerInfo() const
{
	return m_PlayerInfo->GetPlayerInfo();
}

const MonsterInfo& CExcelManager::GetMonsterInfo(Object_Type MonsterType) const
{
	return m_MonsterInfo->GetMonsterInfo(MonsterType);
}

const MonsterInfo& CExcelManager::GetMonsterInfo(int Index) const
{
	return m_MonsterInfo->GetMonsterInfo(Index);
}

const BossInfo& CExcelManager::GetBulletKingInfo() const
{
	return m_BulletKingInfo->GetBulletKingInfo();
}

int CExcelManager::GetMonsterSize() const
{
	return m_MonsterInfo->GetMonsterSize();
}
