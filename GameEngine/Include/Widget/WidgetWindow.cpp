
#include "WidgetWindow.h"

CWidgetWindow::CWidgetWindow()	:
	m_Viewport(nullptr),
	m_ZOrder(0),
	m_Start(false)
{
}

CWidgetWindow::~CWidgetWindow()
{
}

void CWidgetWindow::Start()
{
	m_Start = true;

	auto	iter = m_WidgetList.begin();
	auto	iterEnd = m_WidgetList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

bool CWidgetWindow::Init()
{
	return true;
}

void CWidgetWindow::Update(float DeltaTime)
{
	if (!m_Start)
		Start();

	auto	iter = m_WidgetList.begin();
	auto	iterEnd = m_WidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WidgetList.erase(iter);
			iterEnd = m_WidgetList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CWidgetWindow::PostUpdate(float DeltaTime)
{
	if (!m_Start)
		Start();

	auto	iter = m_WidgetList.begin();
	auto	iterEnd = m_WidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WidgetList.erase(iter);
			iterEnd = m_WidgetList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}
}

void CWidgetWindow::Render()
{
	if (!m_Start)
		Start();

	auto	iter = m_WidgetList.begin();
	auto	iterEnd = m_WidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WidgetList.erase(iter);
			iterEnd = m_WidgetList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render();
		++iter;
	}
}
