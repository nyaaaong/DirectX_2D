#pragma once

#include "Scene.h"

class CSceneManager
{
private:
	CScene* m_pScene;
	CScene* m_pNextScene;

public:
	CScene* GetScene()	const
	{
		return m_pScene;
	}

public:
	bool Init();
	bool Update(float fTime);
	bool PostUpdate(float fTime);

public:
	template <typename T>
	bool CreateSceneMode(bool bCurrent = true)
	{
		if (bCurrent)
			return m_pScene->CreateSceneMode<T>();

		return m_pNextScene->CreateSceneMode<T>();
	}

	DECLARE_SINGLE(CSceneManager)
};

