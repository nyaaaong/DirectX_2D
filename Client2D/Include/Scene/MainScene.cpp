
#include "MainScene.h"
#include "Device.h"
#include "Public.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "Resource/Particle/Particle.h"
#include "../Object/Player2D.h"
#include "../Object/BulletKin.h"
#include "../Object/Bandana.h"
#include "../Object/ShotgunKin1.h"
#include "../Object/ShotgunKin2.h"
#include "../Object/BulletKing.h"
#include "../Object/Dummy.h"

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

	SetPlayerObject(Player);

	m_TileMap = m_Scene->LoadGameObject<CTileMap>();
	m_TileMap->Load("TileMap.dat", SCENE_PATH);

	CPublic::GetInst()->LoadObjPos(m_TileMap);
	CSceneComponent*	Root = m_TileMap->GetRootComponent();
	CTileMapComponent* TileMapComponent = dynamic_cast<CTileMapComponent*>(Root);

	TileMapComponent->SetTileColorWhite();

	Vector3	TileCenterSize = TileMapComponent->GetTileSize() * 0.5f;

	std::vector<Vector3>	vecObjectPos;

	for (int i = (int)Object_Type::M_BulletKin; i <= (int)Object_Type::S_NextScene; ++i)
	{
		vecObjectPos.clear();

		CPublic::GetInst()->GetObjectPos((Object_Type)i, vecObjectPos);

		size_t Size = vecObjectPos.size();

		for (int j = 0; j < Size; ++j)
		{
			CGameObject* Obj = nullptr;

			switch ((Object_Type)i)
			{
			case Object_Type::M_BulletKin:
				Obj = m_Scene->CreateGameObject<CBulletKin>("M_BulletKin");
				break;
			case Object_Type::M_Bandana:
				Obj = m_Scene->CreateGameObject<CBandana>("M_Bandana");
				break;
			case Object_Type::M_ShotgunKin1:
				Obj = m_Scene->CreateGameObject<CShotgunKin1>("M_ShotgunKin1");
				break;
			case Object_Type::M_ShotgunKin2:
				Obj = m_Scene->CreateGameObject<CShotgunKin2>("M_ShotgunKin2");
				break;
			case Object_Type::P_PlayerPos:
				Player->SetWorldPos(vecObjectPos[j] + TileCenterSize);
				break;
			case Object_Type::B_BulletKing:
				Obj = m_Scene->CreateGameObject<CBulletKing>("B_BulletKing");
				break;
			case Object_Type::S_NextScene:
				Obj = m_Scene->CreateGameObject<CDummy>("S_NextScene");
				{
					CDummy* NextScene = (CDummy*)Obj;
					NextScene->SetExtent(TileCenterSize.x, TileCenterSize.y);
					NextScene->SetCollisionProfile("NextScene");
					NextScene->SetPivot(0.5f, 0.5f, 0.f);
				}
				break;
			}

			if ((Object_Type)i != Object_Type::P_PlayerPos)
				Obj->SetWorldPos(vecObjectPos[j] + TileCenterSize); // 타일 중앙으로 위치하게 한다.
		}
	}

	m_MainWidget = m_Scene->GetViewport()->CreateWidgetWindow<CMainWidget>("MainWidget");

	CreateSound();

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.7f);

	CInput::GetInst()->SetKeyCallback<CMainScene>("ToggleCollider", KeyState_Down, this, &CMainScene::ToggleCollider);

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

	m_Scene->GetResource()->LoadSound("Effect", false, "Dodge", "Player/Dodge.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Hit", "Player/Hit.wav");

	m_Scene->GetResource()->LoadSound("Effect", false, "WeaponPickup", "Item/WeaponPickup.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "ItemPickup", "Item/ItemPickup.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Spawn", "Item/Spawn.wav");

	m_Scene->GetResource()->LoadSound("Effect", false, "Monster_Hit", "Monster/Effect/Hit.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Monster_Die", "Monster/Effect/Die.wav");

	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die1", "Monster/BulletKin/Die1.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die2", "Monster/BulletKin/Die2.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die3", "Monster/BulletKin/Die3.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKin_Die4", "Monster/BulletKin/Die4.wav");
}

void CMainScene::ToggleCollider(float DeltaTime)
{
	CEngine::GetInst()->SetToggleCollider();
}
