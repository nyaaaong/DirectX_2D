
#include "MainScene.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "../Object/Costume/Costume.h"

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");
	CCostume* Costume = m_Scene->CreateGameObject<CCostume>("Costume");
	
	Costume->SetPlayer(Player);

	SetPlayerObject(Player);

	return true;
}
