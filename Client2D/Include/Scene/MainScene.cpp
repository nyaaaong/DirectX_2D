
#include "MainScene.h"
#include "Device.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "Resource/Particle/Particle.h"
#include "../Object/Player2D.h"

CMainScene::CMainScene()	:
	m_TileMap(nullptr)
{
	SetTypeID<CMainScene>();
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	if (!CSceneMode::Init())
		return false;

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.5f);

	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	SetPlayerObject(Player);

	m_TileMap = m_Scene->LoadGameObject<CTileMap>();
	m_TileMap->Load("TileMap.dat", SCENE_PATH);

	m_MainWidget = m_Scene->GetViewport()->CreateWidgetWindow<CMainWidget>("MainWidget");

	CreateSound();

	return true;
}

void CMainScene::Update(float DeltaTime)
{
	CSceneMode::Update(DeltaTime);
}

void CMainScene::CreateSound()
{
	m_Scene->GetResource()->LoadSound("Effect", false, "Player_Weap1", "Weapon/Shot/Weap1.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Player_Weap2", "Weapon/Shot/Weap2.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Player_Weap3", "Weapon/Shot/Weap3.wav");
}
