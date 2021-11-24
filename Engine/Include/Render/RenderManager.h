#pragma once

#include "../GameInfo.h"

class CRenderManager
{
private:
	const std::list<CSharedPtr<class CGameObject>>* m_ObjectList;
	std::vector<class CSceneComponent*>	m_RenderList;
	unsigned long long		m_RenderCount;

public:
	void SetObjectList(const std::list<CSharedPtr<class CGameObject>>* List)
	{
		m_ObjectList = List;
	}

	void AddRenderList(class CSceneComponent* Component);

public:
	bool Init();
	void Render();

	DECLARE_SINGLE(CRenderManager)
};

