#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/MainWidget.h"
#include "../Object/TileMap.h"

class CMainScene :
	public CSceneMode
{
public:
	CMainScene();
	virtual ~CMainScene();

private:
	CSharedPtr<CMainWidget> m_MainWidget;
	std::function<void(bool, float)> m_LoadingFunction;
	CSharedPtr<CTileMap> m_TileMap;

public:
	void SetWidgetText(const char* Text)
	{
		m_MainWidget->SetText(Text);
	}

public:
	CSharedPtr<CTileMap> GetTileMap()	const
	{
		return m_TileMap;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void CreateSound();

public:
	template <typename T>
	void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
	{
		m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};

