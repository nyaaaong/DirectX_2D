#pragma once

#include "../Excel.h"

class CExcel_BulletKing :
    public CExcel
{
	friend class CExcelManager;

private:
	BossInfo	m_BulletKingInfo;

protected:
	CExcel_BulletKing();
	virtual ~CExcel_BulletKing();

public:
	const BossInfo& GetBulletKingInfo()	const
	{
		return m_BulletKingInfo;
	}

public:
	virtual bool Init();
};

