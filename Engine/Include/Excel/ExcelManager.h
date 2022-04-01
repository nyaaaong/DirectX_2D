#pragma once

#include "../GameInfo.h"

class CExcelManager
{
private:
	class CExcel_Player* m_PlayerInfo;
	class CExcel_Monster* m_MonsterInfo;

public:
	bool Init();

public:
	const CharacterInfo& GetPlayerInfo()	const;
	const CharacterInfo& GetMonsterInfo(Object_Type MonsterType)	const;
	const CharacterInfo& GetMonsterInfo(int Index)	const;
	int GetMonsterSize()	const;

	DECLARE_SINGLE(CExcelManager)
};

