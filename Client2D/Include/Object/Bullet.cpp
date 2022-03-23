
#include "Bullet.h"
#include "BulletAnim.h"
#include "BulletDummy.h"
#include "../Scene/MainScene.h"
#include "Scene/SceneManager.h"
#include "Component/SpriteComponent.h"
#include "Character.h"

CBullet::CBullet() :
	m_StartDistance(50.f),
	m_Distance(300.f),
	m_BulletSpeed(10000.f),
	m_CharacterType(Character_Type::Max),
	m_WeaponSlot(Weapon_Slot::None),
	m_Damage(3.f),
	m_HitObject(false),
	m_Pierce(false)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Body = (CColliderBox2D*)FindComponent("Body");

	m_StartDistance = obj.m_StartDistance;
	m_Distance = obj.m_Distance;
	m_BulletSpeed = obj.m_BulletSpeed;

	m_CharacterType = obj.m_CharacterType;
	m_WeaponSlot = obj.m_WeaponSlot;

	m_HitObject = false;
	m_Pierce = obj.m_Pierce;

	m_Damage = obj.m_Damage;

	m_Owner = obj.m_Owner;
}

CBullet::~CBullet()
{
}

void CBullet::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

void CBullet::Start()
{
	CGameObject::Start();
}

void CBullet::First()
{
	if (m_Sprite->IsRender())
	{
		CGameObject::First();

		if (!m_Owner)
			ASSERT("if (!m_Owner)");

		m_Damage = m_Owner->GetDamage();

		switch (m_CharacterType)
		{
		case Character_Type::Player:
			m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Player_Bullet", TEXT("Bullet/Player/Bullet.png"));
			break;
		case Character_Type::Monster:
			m_Sprite->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Monster_Bullet", TEXT("Bullet/Monster/Bullet.png"));
			break;
		}

		switch (m_WeaponSlot)
		{
		case Weapon_Slot::Weap1:
			m_BulletSpeed = 1000.f;
			m_Distance = 500.f;
			m_SoundName = "Player_Weap1";
			break;
		case Weapon_Slot::Weap2:
			m_BulletSpeed = 1000.f;
			m_Distance = 800.f;
			m_SoundName = "Player_Weap2";
			break;
		case Weapon_Slot::Weap3:
			m_BulletSpeed = 5000.f;
			m_Distance = 2000.f;
			m_SoundName = "Player_Weap3";
			break;
		}

		if (m_SoundName == "")
			ASSERT("if (m_SoundName == "")");

		m_Scene->GetResource()->SoundPlay(m_SoundName);
	}
}

bool CBullet::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(24.f, 24.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body = CreateComponent<CColliderBox2D>("Body");

	m_Body->SetExtent(12.f, 12.f);
	m_Body->SetRender(false);

	m_Sprite->AddChild(m_Body);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBullet::OnCollisionBegin);

	m_Sprite->SetRender(false);

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	float	Dist = m_BulletSpeed * DeltaTime;

	if (m_Distance <= 0.f || IsWallTile(m_BulletDir * Dist))
		CreateHitEffect(true);

	m_Distance -= Dist;

	if (m_StartDistance >= 0.f)
		m_StartDistance -= Dist;

	else
	{
		m_StartDistance = -1.f;
		m_Sprite->SetRender(true);
		m_Body->SetRender(true);
	}	

	AddRelativePos(m_BulletDir * Dist);
}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone()
{
	return DBG_NEW CBullet(*this);
}

void CBullet::OnCollisionBegin(const CollisionResult& result)
{
	CGameObject* DestObj = result.Dest->GetGameObject();

	CCharacter* CharacterObj = dynamic_cast<CCharacter*>(DestObj);
	//CStructureObject* StrObj = dynamic_cast<CStructureObject*>(DestObj);

	if (CharacterObj)
	{
		m_HitObject = true;

		CharacterObj->AddHP(-m_Damage);
	}

	CreateHitEffect(false);
}

bool CBullet::IsWallTile(const Vector3& NextWorldPos)
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
	MoveDir[(int)Move_Dir::LB].y -= (Size.y * 1.4f);

	MoveDir[(int)Move_Dir::B].y -= (Size.y * 1.4f);

	MoveDir[(int)Move_Dir::RB].x += Size.x;
	MoveDir[(int)Move_Dir::RB].y -= (Size.y * 1.4f);

	MoveDir[(int)Move_Dir::L].x -= Size.x;
	MoveDir[(int)Move_Dir::L].y -= (Size.y * 1.4f);

	MoveDir[(int)Move_Dir::R].x += Size.x;
	MoveDir[(int)Move_Dir::R].y -= (Size.y * 1.4f);

	MoveDir[(int)Move_Dir::LT].x -= Size.x;
	MoveDir[(int)Move_Dir::LT].y += (Size.y * 0.2f);

	MoveDir[(int)Move_Dir::T].y += (Size.y * 0.2f);

	MoveDir[(int)Move_Dir::RT].x += Size.x;
	MoveDir[(int)Move_Dir::RT].y += (Size.y * 0.2f);

	for (int i = 0; i < (int)Move_Dir::End; ++i)
	{
		if (TileMap->GetTileType(MoveDir[i] + NextWorldPos) == Tile_Type::Wall)
			return true;
	}

	return false;
}

void CBullet::CreateHitEffect(bool IsDie)
{
	if (!m_Sprite->IsRender() || !m_Body->IsRender())
	{
		CGameObject::Destroy();
		return;
	}

	CBulletDummy* Impact = m_Scene->CreateGameObject<CBulletDummy>("BulletImpact");

	Impact->HitObject(m_HitObject);
	Impact->SetWorldPos(m_Sprite->GetWorldPos());

	if (!m_HitObject || !m_Pierce)
		CGameObject::Destroy();

	else if (IsDie)
	{
		Impact->HitObject(false);
		CGameObject::Destroy();
	}
}