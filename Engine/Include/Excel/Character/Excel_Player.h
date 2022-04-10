#pragma once

#include "../Excel.h"

class CExcel_Player :
    public CExcel
{
	friend class CExcelManager;

private:
	PlayerInfo	m_PlayerInfo;

protected:
	CExcel_Player();
	virtual ~CExcel_Player();

public:
	const PlayerInfo&	GetPlayerInfo()	const
	{
		return m_PlayerInfo;
	}

public:
	virtual bool Init();
};

