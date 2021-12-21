
#include "MainScene.h"
#include "Scene/Scene.h"
#include "../Object/Player2D.h"
#include "Scene/SceneResource.h"

CMainScene::CMainScene()
{
	SetTypeID<CMainScene>();
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	SetPlayerObject(Player);

	return true;
}

void CMainScene::CreateMaterial()
{
}

void CMainScene::CreateAnimationSequence()
{
	m_Scene->GetResource()->CreateAnimationSequence2D("PlayerIdleD", "Player", TEXT("Player.png"), Vector2(66.f, 117.f), Vector2(42.f, 66.f), 4, 6);

	m_Scene->GetResource()->CreateAnimationSequence2D("PlayerDodgeD", "Player", TEXT("Player.png"), Vector2(66.f, 876.f), Vector2(48.f, 87.f), 9, 6);
}
