
#include "Viewport.h"
#include "../Input.h"

CViewport::CViewport()	:
	m_Scene(nullptr)
{
}

CViewport::~CViewport()
{
}

void CViewport::Start()
{
	auto	iter = m_WindowList.begin();
	auto	iterEnd = m_WindowList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

bool CViewport::Init()
{
	return true;
}

void CViewport::Update(float DeltaTime)
{
	auto	iter = m_WindowList.begin();
	auto	iterEnd = m_WindowList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WindowList.erase(iter);
			iterEnd = m_WindowList.end();
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

void CViewport::PostUpdate(float DeltaTime)
{
	auto	iter = m_WindowList.begin();
	auto	iterEnd = m_WindowList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WindowList.erase(iter);
			iterEnd = m_WindowList.end();
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

bool CViewport::CollisionMouse()
{
	Vector2 MousePos = CInput::GetInst()->GetMousePos();

	// ��� �켱������ ���� �������� �浹ó���� �����Ѵ�.

	return false;
}

void CViewport::Collision()
{
}

void CViewport::Render()
{
	auto	iter = m_WindowList.begin();
	auto	iterEnd = m_WindowList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_WindowList.erase(iter);
			iterEnd = m_WindowList.end();
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
