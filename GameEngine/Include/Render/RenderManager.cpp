
#include "RenderManager.h"
#include "../GameObject/GameObject.h"
#include "../Component/SceneComponent.h"

DEFINITION_SINGLE(CRenderManager)

CRenderManager::CRenderManager()	:
	m_ObjectList(nullptr),
	m_RenderCount(0)
{
}

CRenderManager::~CRenderManager()
{
}

void CRenderManager::AddRenderList(CSceneComponent* Component)
{
	if (m_RenderCount == (unsigned long long)m_RenderList.size())
		m_RenderList.resize(m_RenderCount * 2);

	m_RenderList[m_RenderCount] = Component;
	++m_RenderCount;
}

bool CRenderManager::Init()
{
	m_RenderList.resize(500);
	m_RenderCount = 0;


	return true;
}

void CRenderManager::Render()
{
	m_RenderCount = 0;

	{
		auto	iter = m_ObjectList->begin();
		auto	iterEnd = m_ObjectList->end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->PrevRender();
		}
	}

	{
		for (unsigned long long i = 0; i < m_RenderCount; ++i)
		{
			m_RenderList[i]->Render();
		}
	}

	{
		for (unsigned long long i = 0; i < m_RenderCount; ++i)
		{
			m_RenderList[i]->PostRender();
		}
	}
}
