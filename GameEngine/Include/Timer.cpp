#include "Timer.h"

float CTimer::Update()
{
	LARGE_INTEGER	Time;
	QueryPerformanceCounter(&Time);

	m_fDeltaTime = (Time.QuadPart - m_Time.QuadPart) / static_cast<float>(m_Second.QuadPart);

	m_Time = Time;

	m_fFPSTime += m_fDeltaTime;
	++m_iTick;

	if (m_iTick == 60)
	{
		m_fFPS = 60 / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iTick = 0;
	}

	return m_fDeltaTime;
}

CTimer::CTimer()	:
	m_Time(),
	m_Second(),
	m_fDeltaTime(0.f),
	m_fFPS(0.f),
	m_fFPSTime(0.f),
	m_iTick(0)
{
	QueryPerformanceFrequency(&m_Second);
	QueryPerformanceCounter(&m_Time);
}

CTimer::~CTimer()
{
}
