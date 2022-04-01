
#include "ExcelManager.h"
#include "Excel.h"
#include "../Scene/SceneManager.h"
#include "include_cpp/libxl.h"
#include "Character/Excel_Player.h"
#include "Character/Excel_Monster.h"

DEFINITION_SINGLE(CExcelManager)

CExcelManager::CExcelManager()	:
	m_PlayerInfo(nullptr),
	m_MonsterInfo(nullptr)
{
}

CExcelManager::~CExcelManager()
{
	SAFE_DELETE(m_MonsterInfo);
	SAFE_DELETE(m_PlayerInfo);
}

bool CExcelManager::Init()
{
	if (CSceneManager::GetInst()->IsEditor())
		return true;

	m_PlayerInfo = DBG_NEW CExcel_Player;
	m_MonsterInfo = DBG_NEW CExcel_Monster;

	if (!m_PlayerInfo->Init())
		return false;

	if (!m_MonsterInfo->Init())
		return false;

	m_PlayerInfo->Load(L"Player.xlsx", L"Character");
	m_MonsterInfo->Load(L"Monster.xlsx", L"Character");

	return true;
}

const CharacterInfo& CExcelManager::GetPlayerInfo() const
{
	return m_PlayerInfo->GetPlayerInfo();
}

const CharacterInfo& CExcelManager::GetMonsterInfo(Object_Type MonsterType) const
{
	return m_MonsterInfo->GetMonsterInfo(MonsterType);
}

const CharacterInfo& CExcelManager::GetMonsterInfo(int Index) const
{
	return m_MonsterInfo->GetMonsterInfo(Index);
}

int CExcelManager::GetMonsterSize() const
{
	return m_MonsterInfo->GetMonsterSize();
}
