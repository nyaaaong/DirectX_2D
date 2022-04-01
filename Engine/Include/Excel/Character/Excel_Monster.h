#pragma once

#include "../Excel.h"

class CExcel_Monster :
    public CExcel
{
	friend class CExcelManager;

private:
	std::vector<CharacterInfo>	m_vecMonsterInfo;
	int	m_MonsterSize;

protected:
	CExcel_Monster();
	virtual ~CExcel_Monster();

public:
	int GetMonsterSize()	const
	{
		return m_MonsterSize;
	}

	const CharacterInfo& GetMonsterInfo(Object_Type MonsterType)	const
	{
		return m_vecMonsterInfo[(int)MonsterType];
	}

	const CharacterInfo& GetMonsterInfo(int Index)	const
	{
		return m_vecMonsterInfo[Index];
	}

public:
	virtual bool Init();
};

