
#include "MainScene.h"
#include "LoadingScene.h"
#include "Public.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "../Object/Player2D.h"
#include "../Object/BulletKin.h"
#include "../Object/Bandana.h"
#include "../Object/ShotgunKin1.h"
#include "../Object/ShotgunKin2.h"
#include "../Object/BulletKing.h"
#include "../Object/Dummy.h"

CMainScene::CMainScene()	:
	m_BossMonster(nullptr),
	m_IsBossRoom(false),
	m_BossClear(false),
	m_NeedUpdateSound(false),
	m_BossClearSoundPlayComplete(false)
{
	SetTypeID<CMainScene>();
}

CMainScene::~CMainScene()
{
	m_Scene->GetResource()->SoundStop("Main");
	m_Scene->GetResource()->SoundStop("Boss");
	m_Scene->GetResource()->SoundStop("BossClear");
}

void CMainScene::Start()
{
	CSceneMode::Start();

	m_Scene->GetResource()->SoundPlay("Main");

	m_MainWidget->FadeIn();
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
				Obj = Player;
				break;
			case Object_Type::B_BulletKing:
				m_BossMonster = m_Scene->CreateGameObject<CBulletKing>("B_BulletKing");
				m_BossMonster->Disable();
				Obj = m_BossMonster;
				break;
			case Object_Type::TP_BossRoomStart:
				Obj = m_Scene->CreateGameObject<CDummy>("TP_BossRoomStart");
				{
					CDummy* BossRoomStart = (CDummy*)Obj;
					BossRoomStart->SetExtent(TileCenterSize.x, TileCenterSize.y);
					BossRoomStart->SetCollisionProfile("BossRoomStart");
					BossRoomStart->SetPivot(0.5f, 0.5f, 0.f);
				}
				break;
			case Object_Type::TP_BossRoomEnd:
				Obj = m_Scene->CreateGameObject<CDummy>("TP_BossRoomEnd");
				{
					CDummy* BossRoomEnd = (CDummy*)Obj;
					BossRoomEnd->SetExtent(TileCenterSize.x, TileCenterSize.y);
					BossRoomEnd->SetCollisionProfile("BossRoomEnd");
					BossRoomEnd->SetPivot(0.5f, 0.5f, 0.f);
				}
				break;
			}

			if (Obj)
			{
				Obj->SetWorldPos(vecObjectPos[j] + TileCenterSize); // 타일 중앙으로 위치하게 한다.

				if (i == (int)Object_Type::TP_BossRoomEnd)
					m_BossRoomEndWorldPos = Obj->GetWorldPos();
			}
		}
	}

	m_MainWidget = m_Scene->GetViewport()->CreateWidgetWindow<CMainWidget>("MainWidget");
	m_BossWidget = m_Scene->GetViewport()->CreateWidgetWindow<CBossWidget>("BossWidget");
	
	Vector2	BossHUDPos = m_BossWidget->GetWindowPos();

	m_BossWidget->SetPos(BossHUDPos.x + 400.f, BossHUDPos.y + 50.f);
	m_BossWidget->Enable(false);

	CreateSound();

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.7f);

	CInput::GetInst()->SetKeyCallback<CMainScene>("ToggleCollider", KeyState_Down, this, &CMainScene::ToggleCollider);
	CInput::GetInst()->SetKeyCallback<CMainScene>("CheatMoveBossRoom", KeyState_Down, this, &CMainScene::CheatMoveBossRoom);
	CInput::GetInst()->SetKeyCallback<CMainScene>("CheatBossHP", KeyState_Down, this, &CMainScene::CheatBossHP);

	return true;
}

void CMainScene::Update(float DeltaTime)
{
	UpdateSound(DeltaTime);
	UpdateBoss(DeltaTime);
}

void CMainScene::SetBossRoom()
{
	if (m_IsBossRoom)
		return;

	m_IsBossRoom = true;

	m_NeedUpdateSound = true;

	if (m_BossRoomEndWorldPos.x == 0.f && m_BossRoomEndWorldPos.y == 0.f)
		ASSERT("if (m_BossRoomEndWorldPos.x == 0.f && m_BossRoomEndWorldPos.y == 0.f)");

	m_Scene->GetPlayerObject()->SetWorldPos(m_BossRoomEndWorldPos);
}

void CMainScene::SetPercent(float Percent)
{
	if (m_BossWidget)
		m_BossWidget->SetPercent(Percent);
}

void CMainScene::CreateSound()
{
	m_Scene->GetResource()->LoadSound("BGM", true, "Main", "BGM/Main.mp3");
	m_Scene->GetResource()->LoadSound("BGM", true, "Boss", "BGM/Boss.mp3");
	m_Scene->GetResource()->LoadSound("BGM", true, "BossClear", "BGM/BossClear.mp3");

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

	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKing_Pattern1", "Monster/Boss/BulletKing/BulletKing_Pattern1.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKing_Pattern2", "Monster/Boss/BulletKing/BulletKing_Pattern2.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKing_Pattern3", "Monster/Boss/BulletKing/BulletKing_Pattern3.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "BulletKing_Pattern4", "Monster/Boss/BulletKing/BulletKing_Pattern4.wav");
}

void CMainScene::UpdateSound(float DeltaTime)
{
	if (!m_NeedUpdateSound)
		return;

	else
	{
		if (m_IsBossRoom)
		{
			m_Scene->GetResource()->SoundStop("Main");

			if (!m_BossClear)
				m_Scene->GetResource()->SoundPlay("Boss");

			else if (!m_BossClearSoundPlayComplete)
			{
				m_Scene->GetResource()->SoundStop("Boss");
				m_Scene->GetResource()->SoundPlay("BossClear");

				m_BossClearSoundPlayComplete = true;
			}

			m_NeedUpdateSound = false;
		}
	}
}

void CMainScene::UpdateBoss(float DeltaTime)
{
	if (m_IsBossRoom)
	{
		if (!m_BossClear)
		{
			if (!m_BossMonster->IsEnable())
			{
				m_BossMonster->Enable(true);
				m_BossWidget->Enable(true);
			}
		}

		else
		{
			m_BossWidget->Disable();

			m_NeedUpdateSound = true;
		}
	}
}

void CMainScene::ToggleCollider(float DeltaTime)
{
	CEngine::GetInst()->SetToggleCollider();
}

void CMainScene::CheatMoveBossRoom(float DeltaTime)
{
	SetBossRoom();
}

void CMainScene::CheatBossHP(float DeltaTime)
{
	if (m_BossMonster)
	{
		if (m_BossMonster->IsEnable())
		{
			CBulletKing* BulletKing = dynamic_cast<CBulletKing*>(m_BossMonster);
			
			if (BulletKing)
				BulletKing->SetHP(1.f);
		}
	}
}
