#pragma once

#include "../GameInfo.h"

class CExcelManager
{
private:
	class CExcel_Player* m_PlayerInfo;
	class CExcel_Monster* m_MonsterInfo;
	class CExcel_BulletKing* m_BulletKingInfo;

public:
	bool Init();

public:
	const PlayerInfo& GetPlayerInfo()	const;
	const MonsterInfo& GetMonsterInfo(Object_Type MonsterType)	const;
	const MonsterInfo& GetMonsterInfo(int Index)	const;
	const BossInfo& GetBulletKingInfo()	const;
	int GetMonsterSize()	const;

	DECLARE_SINGLE(CExcelManager)
};

