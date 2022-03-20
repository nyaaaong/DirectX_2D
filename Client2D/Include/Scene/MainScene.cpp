
#include "MainScene.h"
#include "Device.h"
#include "Public.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "Resource/Particle/Particle.h"
#include "../Object/Player2D.h"
#include "../Object/BulletKin.h"

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

	CPublic::GetInst()->LoadObjPos(m_TileMap);
	CSceneComponent*	Root = m_TileMap->GetRootComponent();
	CTileMapComponent* TileMapComponent = dynamic_cast<CTileMapComponent*>(Root);

	if (!Root)
		ASSERT("if (!Root)");

	TileMapComponent->SetTileColorWhite();

	CGameObject* Obj = nullptr;
	Vector3	TileCenterSize = TileMapComponent->GetTileSize() * 0.5f;

	std::vector<Vector3>	vecObjectPos;

	for (int i = 0; i < (int)Object_Type::Max; ++i)
	{
		vecObjectPos.clear();

		CPublic::GetInst()->GetObjectPos((Object_Type)i, vecObjectPos);

		size_t Size = vecObjectPos.size();

		for (int j = 0; j < Size; ++j)
		{
			switch ((Object_Type)i)
			{
			case Object_Type::BulletKin:
				Obj = m_Scene->CreateGameObject<CBulletKin>("BulletKin");
				Obj->SetWorldPos(vecObjectPos[j] + TileCenterSize); // 타일 중앙으로 위치하게 한다.
				break;
			}
		}
	}

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

	m_Scene->GetResource()->LoadSound("Effect", false, "Monster_Hit", "Monster/Effect/Hit.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Monster_Die", "Monster/Effect/Die.wav");

	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die1", "Monster/BulletKin/Die1.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die2", "Monster/BulletKin/Die2.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die3", "Monster/BulletKin/Die3.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die4", "Monster/BulletKin/Die4.wav");
}
