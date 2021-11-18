
#include "Scene.h"

CScene::CScene()	:
	m_pResource(nullptr)
{
	m_pMode = new CSceneMode;
	m_pResource = new CSceneResource;

	m_pMode->m_pScene = this;
	m_pResource->m_pScene = this;
}

CScene::~CScene()
{
	SAFE_DELETE(m_pResource);
}

void CScene::Update(float fTime)
{
	m_pMode->Update(fTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if ((*iter)->IsDisable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(fTime);
		++iter;
	}
}

void CScene::PostUpdate(float fTime)
{
	m_pMode->PostUpdate(fTime);

	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if ((*iter)->IsDisable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(fTime);
		++iter;
	}
}
