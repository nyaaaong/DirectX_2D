#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/MainWidget.h"
#include "../Widget/BossWidget.h"
#include "../Object/TileMap.h"

class CMainScene :
	public CSceneMode
{
public:
	CMainScene();
	virtual ~CMainScene();

private:
	CSharedPtr<CMainWidget> m_MainWidget;
	CSharedPtr<CBossWidget> m_BossWidget;
	CSharedPtr<CTileMap>	m_TileMap;
	class CGameObject*		m_BossMonster;
	std::function<void(bool, float)> m_LoadingFunction;
	bool					m_IsBossRoom;
	bool					m_BossClear;
	bool					m_NeedUpdateSound;
	bool					m_BossClearSoundPlayComplete;
	Vector3					m_BossRoomEndWorldPos;

public:
	CSharedPtr<CTileMap> GetTileMap()	const
	{
		return m_TileMap;
	}

public:
	void FadeOut()
	{
		m_MainWidget->FadeOut();
	}

	void SetBossClear()
	{
		m_BossClear = true;
	}

	/*void SetDebugText(const char* Text)
	{
		m_MainWidget->SetDebugText(Text);
	}*/

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void SetBossRoom();
	void SetPercent(float Percent);

private:
	void CreateSound();

private:
	void UpdateSound(float DeltaTime);
	void UpdateBoss(float DeltaTime);

private:
	void ToggleCollider(float DeltaTime);
	void CheatMoveBossRoom(float DeltaTime);
	void CheatBossHP(float DeltaTime);

public:
	template <typename T>
	void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
	{
		m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};

