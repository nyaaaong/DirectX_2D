
#include "MainScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "../Object/Player2D.h"
#include "../Object/Monster.h"
#include "../Object/PixelTest.h"

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

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.3f);

	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	SetPlayerObject(Player);

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.6f);

	CMonster* Monster = m_Scene->CreateGameObject<CMonster>("Monster");

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.8f);

	CPixelTest* PixelTest = m_Scene->CreateGameObject<CPixelTest>("PixelTest");

	m_MainWidget = m_Scene->GetViewport()->CreateWidgetWindow<CMainWidget>("MainWidget");

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
