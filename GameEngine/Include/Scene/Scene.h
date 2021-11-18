#pragma once

#include "SceneMode.h"
#include "SceneResource.h"
#include "../GameObject/GameObject.h"

class CScene
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	CSharedPtr<CSceneMode>	m_pMode;
	CSceneResource* m_pResource;
	std::list<CSharedPtr<CGameObject>>	m_ObjList;

public:
	CSceneResource* GetResource()	const
	{
		return m_pResource;
	}

public:
	void Update(float fTime);
	void PostUpdate(float fTime);

public:
	template <typename T>
	bool CreateSceneMode()
	{
		m_pMode = new T;

		if (!m_pMode->Init())
		{
			m_pMode = nullptr;
			return false;
		}

		return true;
	}

	template <typename T>
	T* CreateGameObject(const std::string& strName)
	{
		T* pObj = new T;

		pObj->SetName(strName);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		m_ObjList.push_back(pObj);

		return pObj;
	}
};

