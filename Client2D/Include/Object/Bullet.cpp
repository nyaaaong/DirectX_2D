
#include "Bullet.h"
#include "Player2D.h"
#include "BulletAnim.h"
#include "BulletDummy.h"
#include "Character.h"
#include "../Scene/MainScene.h"
#include "Scene/SceneManager.h"
#include "Component/SpriteComponent.h"

CBullet::CBullet() :
	m_StartDistance(50.f),
	m_Distance(300.f),
	m_BulletSpeed(10000.f),
	m_CharacterType(Character_Type::Max),
	m_WeaponSlot(Weapon_Slot::None),
	m_Damage(3.f),
	m_Hit(false),
	m_Pierce(false),
	m_ImpactDestroyed(false),
	m_ImpactCreated(false),
	m_Check(false),
	m_SetBulletSpeed(false),
	m_NeedDestroyCollider(false),
	m_Impact(nullptr),
	m_BulletType(Bullet_Type::Pistol)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("BulletBody");

	m_StartDistance = obj.m_StartDistance;
	m_Distance = obj.m_Distance;
	m_BulletSpeed = obj.m_BulletSpeed;

	m_CharacterType = obj.m_CharacterType;
	m_WeaponSlot = obj.m_WeaponSlot;

	m_Hit = false;
	m_ImpactDestroyed = false;
	m_ImpactCreated = false;
	m_Check = false;
	m_NeedDestroyCollider = false;
	m_SetBulletSpeed = false;
	m_Pierce = obj.m_Pierce;

	m_Damage = obj.m_Damage;

	m_Owner = obj.m_Owner;

	m_BulletType = obj.m_BulletType;
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");

	m_Sprite->SetRelativeScale(24.f, 24.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body = CreateComponent<CColliderBox2D>("BulletBody");
	m_Body->SetCollisionProfile("AttackCheck");

	m_Body->SetExtent(12.f, 12.f);
	m_Body->SetRender(false);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBullet::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CBullet::OnCollisionEnd);

	m_Sprite->SetRender(false);
	m_Sprite->AddChild(m_Body);

	SetRootComponent(m_Sprite);

	return true;
}

void CBullet::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

void CBullet::Start()
{
	CGameObject::Start();

	if (GetName() == "")
		ASSERT("if (GetName() == "")");
}

void CBullet::First()
{
	if (m_Check)
	{
		CGameObject::First();

		if (!m_Owner)
			ASSERT("if (!m_Owner)");

		m_Damage = m_Owner->GetDamage();

		switch (m_CharacterType)
		{
		case Character_Type::Player:
			m_Body->SetCollisionProfile("PlayerAttack");

			m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Player_Bullet", TEXT("Bullet/Player/Bullet.png"));

			switch (m_WeaponSlot)
			{
			case Weapon_Slot::Pistol:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 800.f;
				m_StartDistance = 100.f;
				m_Scene->GetResource()->SoundPlay("Pistol");
				break;
			case Weapon_Slot::Rifle:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 800.f;
				m_StartDistance = 100.f;
				m_Scene->GetResource()->SoundPlay("Rifle");
				break;
			case Weapon_Slot::Sniper:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 5000.f;
				m_Distance = 2000.f;
				m_Scene->GetResource()->SoundPlay("Sniper");
				break;
			}
			break;
		case Character_Type::Monster:
			m_Body->SetCollisionProfile("MonsterAttack");

			m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Monster_Bullet", TEXT("Bullet/Enemy/Bullet.png"));

			switch (m_BulletType)
			{
			case Bullet_Type::Pistol:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 800.f;
				m_Scene->GetResource()->SoundPlay("Pistol");
				break;
			case Bullet_Type::Rifle:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 800.f;
				m_StartDistance = 100.f;
				m_Scene->GetResource()->SoundPlay("Rifle");
				break;
			case Bullet_Type::Shotgun:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 400.f;
				m_StartDistance = 200.f;
				m_Scene->GetResource()->SoundPlay("Shotgun");
				break;
			case Bullet_Type::ShotgunKin2Die:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 800.f;
				break;
			case Bullet_Type::BulletKing_Pattern1:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 3000.f;
				m_StartDistance = 400.f;
				break;
			case Bullet_Type::BulletKing_Pattern2:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 3000.f;
				m_StartDistance = 400.f;
				break;
			case Bullet_Type::BulletKing_Pattern3:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 400.f;
				m_Distance = 3000.f;
				m_StartDistance = 400.f;
				break;
			case Bullet_Type::BulletKing_Pattern4:
				if (!m_SetBulletSpeed)
					m_BulletSpeed = 1000.f;
				m_Distance = 3000.f;
				m_StartDistance = 400.f;
				break;
			}
			break;
		}
	}
}

void CBullet::Update(float DeltaTime)
{
	if (m_NeedDestroyCollider)
		Destroy();

	CGameObject::Update(DeltaTime);

	float	Dist = m_BulletSpeed * DeltaTime;

	CheckFirstBullet(Dist);
	BulletUpdater(Dist);
}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone()
{
	return DBG_NEW CBullet(*this);
}

void CBullet::Destroy()
{
	CGameObject::Destroy();
}

void CBullet::OnCollisionBegin(const CollisionResult& result)
{
	if (!m_Check)
		return;

	Collision_Channel	DestChannel = result.Dest->GetCollisionProfile()->Channel;

	if (DestChannel == Collision_Channel::Player || 
		DestChannel == Collision_Channel::Monster)
	{
		CCharacter* Character = dynamic_cast<CCharacter*>(result.Dest->GetGameObject());

		if (!Character->AddDamage(m_Damage))
			return;

		m_Hit = true;
	}

	CreateHitEffect();
}

void CBullet::OnCollisionEnd(const CollisionResult& result)
{
	if (!m_Check)
		return;

	else
		m_ImpactCreated = false;
}

bool CBullet::IsWallTile(const Vector3& NextPos)
{
	CSceneMode* SceneMode = CSceneManager::GetInst()->GetSceneMode();
	CMainScene* Scene = dynamic_cast<CMainScene*>(SceneMode);

	if (!Scene)
		return true;

	CTileMap* TileMap = Scene->GetTileMap();

	if (!TileMap)
		return true;

	// 8방향 체크

	const Vector3	Center = GetWorldPos();
	const Vector2	Size = m_Body->GetInfo().Length;

	Vector3	MoveDir[(int)Move_Dir::End];

	for (int i = 0; i < (int)Move_Dir::End; ++i)
	{
		MoveDir[i] = Center;
	}

	MoveDir[(int)Move_Dir::LB].x -= Size.x;
	MoveDir[(int)Move_Dir::LB].y -= Size.y;

	MoveDir[(int)Move_Dir::B].y -= Size.y;

	MoveDir[(int)Move_Dir::RB].x += Size.x;
	MoveDir[(int)Move_Dir::RB].y -= Size.y;

	MoveDir[(int)Move_Dir::L].x -= Size.x;
	MoveDir[(int)Move_Dir::L].y -= Size.y;

	MoveDir[(int)Move_Dir::R].x += Size.x;
	MoveDir[(int)Move_Dir::R].y -= Size.y;

	MoveDir[(int)Move_Dir::LT].x -= Size.x;
	MoveDir[(int)Move_Dir::LT].y += Size.y;

	MoveDir[(int)Move_Dir::T].y += Size.y;

	MoveDir[(int)Move_Dir::RT].x += Size.x;
	MoveDir[(int)Move_Dir::RT].y += Size.y;

	for (int i = 0; i < (int)Move_Dir::End; ++i)
	{
		if (TileMap->GetTileType(MoveDir[i] + NextPos) == Tile_Type::T_Wall)
			return true;
	}

	return false;
}

void CBullet::CreateHitEffect()
{
	if (!m_ImpactCreated)
	{
		m_ImpactCreated = true;

		CScene* Scene = CSceneManager::GetInst()->GetScene();

		m_Impact = Scene->CreateGameObject<CBulletDummy>("BulletImpact");
		m_Impact->SetGrayColor(!m_Hit);
		m_Impact->SetWorldPos(GetWorldPos());

		if (!m_Pierce)
		{
			m_Body->Enable(false);
			m_NeedDestroyCollider = true;
		}

		else
			m_Hit = false;
	}
}

void CBullet::CheckFirstBullet(float Dist)
{
	if (IsWallTile(m_BulletDir * Dist))
	{
		Destroy();
		return;
	}

	else
	{
		m_Check = true;
	
		m_Sprite->SetRender(true);
		m_Body->SetRender(true);
	}

	m_StartDistance -= Dist;
}

void CBullet::BulletUpdater(float Dist)
{
	if (!m_Check)
		return;

	if (!m_Hit)
	{
		if (m_Distance <= 0.f || IsWallTile(m_BulletDir * Dist))
			CreateHitEffect();
	}

	m_Distance -= Dist;

	AddRelativePos(m_BulletDir * Dist);
}
