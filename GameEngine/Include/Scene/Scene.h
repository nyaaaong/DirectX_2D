#pragma once

#include "SceneMode.h"
#include "SceneResource.h"
#include "SceneCollision.h"
#include "CameraManager.h"
#include "Viewport.h"
#include "../GameObject/GameObject.h"

class CScene
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	CSharedPtr<CSceneMode> m_Mode;
	CSceneResource* m_Resource;
	CSceneCollision* m_Collision;
	CCameraManager* m_CameraManager;
	CViewport* m_Viewport;
	std::list<CSharedPtr<CGameObject>>	m_ObjList;
	bool		m_Start;
	bool		m_Change;

public:
	void SetAutoChange(bool Change)
	{
		m_Change = Change;
	}

public:
	CSceneResource* GetResource()	const
	{
		return m_Resource;
	}

	CCameraManager* GetCameraManager()	const
	{
		return m_CameraManager;
	}

	CViewport* GetViewport()	const
	{
		return m_Viewport;
	}

	CSceneCollision* GetCollision()	const
	{
		return m_Collision;
	}

	CGameObject* GetPlayerObject()	const
	{
		return m_Mode->GetPlayerObject();
	}

	CGameObject* FindObject(const std::string& Name)
	{
		auto	iter = m_ObjList.begin();
		auto	iterEnd = m_ObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
				return *iter;
		}

		return nullptr;
	}

public:
	void Start();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Save(const char* FileName, const std::string& PathName = SCENE_PATH);
	void SaveFullPath(const char* FullPath);
	void Load(const char* FileName, const std::string& PathName = SCENE_PATH);
	void LoadFullPath(const char* FullPath);

public:
	template <typename T>
	bool CreateSceneMode()
	{
		m_Mode = DBG_NEW T;

		m_Mode->m_Scene = this;

		if (!m_Mode->Init())
		{
			m_Mode = nullptr;
			return false;
		}

		return true;
	}

public:
	template <typename T>
	T* CreateSceneModeEmpty()
	{
		m_Mode = DBG_NEW T;

		m_Mode->m_Scene = this;

		return (T*)*m_Mode;
	}

public:
	template <typename T>
	bool LoadSceneMode()
	{
		m_Mode = DBG_NEW T;

		m_Mode->m_Scene = this;

		return true;
	}

public:
	template <typename T>
	T* CreateGameObject(const std::string& Name)
	{
		T* Obj = DBG_NEW T;

		Obj->SetName(Name);
		Obj->SetScene(this);

		if (!Obj->Init())
		{
			SAFE_RELEASE(Obj);
			return nullptr;
		}

		m_ObjList.push_back(Obj);

		if (m_Start)
			Obj->Start();

		return Obj;
	}

public:
	template <typename T>
	T* LoadGameObject()
	{
		T* Obj = DBG_NEW T;

		Obj->SetScene(this);

		m_ObjList.push_back(Obj);

		if (m_Start)
			Obj->Start();

		return Obj;
	}
};

