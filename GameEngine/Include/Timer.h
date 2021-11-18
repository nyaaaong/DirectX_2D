#pragma once

#include "GameInfo.h"

class CTimer
{
private:
	LARGE_INTEGER	m_Time;
	LARGE_INTEGER	m_Second;
	float	m_fDeltaTime;
	float	m_fFPS;
	float	m_fFPSTime;
	int		m_iTick;

public:
	float GetDeltaTime()	const
	{
		return m_fDeltaTime;
	}

	float GetFPS()	const
	{
		return m_fFPS;
	}

public:
	float Update();

public:
	CTimer();
	~CTimer();
};

