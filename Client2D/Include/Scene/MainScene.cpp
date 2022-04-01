
#include "MainScene.h"
#include "Device.h"
#include "Public.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "Resource/Particle/Particle.h"
#include "../Object/Player2D.h"
#include "../Object/BulletKin.h"
#include "../Object/Bandana.h"
#include "../Object/ShotgunKin1.h"
#include "../Object/ShotgunKin2.h"

CMainScene::CMainScene()	:
	m_TileMap(nullptr)
{
	SetTypeID<CMainScene>();
}

CMainScene::~CMainScene()
{
	m_Scene->GetResource()->SoundStop("Main");
}

void CMainScene::Start()
{
	CSceneMode::Start();

	m_Scene->GetResource()->SoundPlay("Main");
}

bool CMainScene::Init()
{
	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.1f);

	if (!CSceneMode::Init())
		return false;

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.3f);

	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	Player->SetWorldPos(400.f, 300.f, 0.f);

	SetPlayerObject(Player);

	m_TileMap = m_Scene->LoadGameObject<CTileMap>();
	m_TileMap->Load("TileMap.dat", SCENE_PATH);

	CPublic::GetInst()->LoadObjPos(m_TileMap);
	CSceneComponent*	Root = m_TileMap->GetRootComponent();
	CTileMapComponent* TileMapComponent = dynamic_cast<CTileMapComponent*>(Root);

	TileMapComponent->SetTileColorWhite();

	Vector3	TileCenterSize = TileMapComponent->GetTileSize() * 0.5f;

	std::vector<Vector3>	vecObjectPos;

	for (int i = 0; i < (int)Object_Type::Max; ++i)
	{
		vecObjectPos.clear();

		CPublic::GetInst()->GetObjectPos((Object_Type)i, vecObjectPos);

		size_t Size = vecObjectPos.size();

		for (int j = 0; j < Size; ++j)
		{
			CGameObject* Obj = nullptr;

			switch ((Object_Type)i)
			{
			case Object_Type::BulletKin:
				Obj = m_Scene->CreateGameObject<CBulletKin>("BulletKin");
				break;
			case Object_Type::Bandana:
				Obj = m_Scene->CreateGameObject<CBandana>("Bandana");
				break;
			case Object_Type::ShotgunKin1:
				Obj = m_Scene->CreateGameObject<CShotgunKin1>("ShotgunKin1");
				break;
			case Object_Type::ShotgunKin2:
				Obj = m_Scene->CreateGameObject<CShotgunKin2>("ShotgunKin2");
				break;
			}

			Obj->SetWorldPos(vecObjectPos[j] + TileCenterSize); // 타일 중앙으로 위치하게 한다.
		}
	}

	m_MainWidget = m_Scene->GetViewport()->CreateWidgetWindow<CMainWidget>("MainWidget");

	CreateSound();

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.7f);

	return true;
}

void CMainScene::Update(float DeltaTime)
{
	CSceneMode::Update(DeltaTime);
}

void CMainScene::CreateSound()
{
	m_Scene->GetResource()->LoadSound("BGM", true, "Main", "BGM/Main.mp3");

	m_Scene->GetResource()->LoadSound("Effect", false, "Pistol", "Weapon/Shot/Pistol.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Rifle", "Weapon/Shot/Rifle.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Sniper", "Weapon/Shot/Sniper.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Shotgun", "Weapon/Shot/Shotgun.wav");

	m_Scene->GetResource()->LoadSound("Effect", false, "Monster_Hit", "Monster/Effect/Hit.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Monster_Die", "Monster/Effect/Die.wav");

	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die1", "Monster/BulletKin/Die1.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die2", "Monster/BulletKin/Die2.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die3", "Monster/BulletKin/Die3.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die4", "Monster/BulletKin/Die4.wav");
}
