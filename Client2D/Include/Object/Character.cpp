
#include "Character.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneResource.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "../Scene/MainScene.h"

CCharacter::CCharacter() :
	m_HP(50.f),
	m_HPMax(50.f),
	m_HitEffectTime(0.f),
	m_HitEffectTimeMax(0.1f),
	m_IsDied(false),
	m_IsPaperBurn(false),
	m_UsePaperburn(true),
	m_Hit(false),
	m_IsPlayedHitSound(false),
	m_Damage(3.f),
	m_MoveSpeed(300.f),
	m_Type(Character_Type::Max),
	m_TopOffsetY(1.f),
	m_BottomOffsetY(1.f)
{
}

CCharacter::CCharacter(const CCharacter& obj) :
	CGameObject(obj)
{
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_PaperBurn = (CPaperBurnComponent*)FindComponent("PaperBurn");

	m_HP = obj.m_HP;
	m_HPMax = obj.m_HPMax;
	m_IsDied = false;
	m_IsPaperBurn = false;
	m_UsePaperburn = obj.m_UsePaperburn;
	m_Hit = false;
	m_IsPlayedHitSound = false;
	m_Type = obj.m_Type;

	m_Damage = obj.m_Damage;
	m_MoveSpeed = obj.m_MoveSpeed;

	m_TopOffsetY = obj.m_TopOffsetY;
	m_BottomOffsetY = obj.m_BottomOffsetY;
}

CCharacter::~CCharacter()
{
}

void CCharacter::Start()
{
	CGameObject::Start();
}

bool CCharacter::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_PaperBurn = CreateComponent<CPaperBurnComponent>("PaperBurn");

	m_Body->UseMouseCollision(false);

	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Calc(DeltaTime);
	Hit(DeltaTime);

	if (!m_Hit)
		Dead(DeltaTime);
}

void CCharacter::OnCollisionBegin(const CollisionResult& result)
{
	m_Hit = true;
}

void CCharacter::OnCollisionEnd(const CollisionResult& result)
{
	
}

void CCharacter::Calc(float DeltaTime)
{
}

void CCharacter::PaperBurnEnd()
{
	Destroy();
}

void CCharacter::Dead(float DeltaTime)
{
	switch (m_Type)
	{
	case Character_Type::Player:
		break;
	case Character_Type::Monster:
		m_Scene->GetResource()->SoundPlay("Monster_Die");
		break;
	}
}

void CCharacter::Hit(float DeltaTime)
{
	if (m_Hit)
	{
		m_HitEffectTime += DeltaTime;

		m_Sprite->SetBaseColor(Vector4::Red);

		// 히트 사운드 출력
		if (!m_IsPlayedHitSound)
		{
			switch (m_Type)
			{
			case Character_Type::Player:
				break;
			case Character_Type::Monster:
				m_Scene->GetResource()->SoundPlay("Monster_Hit");
				break;
			}

			m_IsPlayedHitSound = true;
		}

		if (m_HitEffectTime >= m_HitEffectTimeMax)
		{
			m_Sprite->SetBaseColor(Vector4::White);

			m_HitEffectTime = 0.f;
			m_Hit = false;
			m_IsPlayedHitSound = false;
		}
	}
}

bool CCharacter::IsWallTile(const Vector3& NextWorldPos)
{
	CSceneMode* SceneMode = CSceneManager::GetInst()->GetSceneMode();
	CMainScene* Scene = dynamic_cast<CMainScene*>(SceneMode);

	if (!Scene)
		return true;

	CTileMap* TileMap = Scene->GetTileMap();

	if (!TileMap)
		return true;

	// 8방향 체크
	
	const Vector2	Center = m_Body->GetInfo().Center;
	const Vector2	Size = m_Body->GetInfo().Length;

	Vector3	MoveDir[(int)Move_Dir::End];

	for (int i = 0; i < (int)Move_Dir::End; ++i)
	{
		MoveDir[i].x = Center.x;
		MoveDir[i].y = Center.y;
	}

	float	CtrSizeTop = Size.y * m_TopOffsetY;
	float	CtrSizeBottom = Size.y * m_BottomOffsetY;

	MoveDir[(int)Move_Dir::LB].x -= Size.x;
	MoveDir[(int)Move_Dir::LB].y -= CtrSizeTop;

	MoveDir[(int)Move_Dir::B].y -= CtrSizeTop;

	MoveDir[(int)Move_Dir::RB].x += Size.x;
	MoveDir[(int)Move_Dir::RB].y -= CtrSizeTop;

	MoveDir[(int)Move_Dir::L].x -= Size.x;
	MoveDir[(int)Move_Dir::L].y -= CtrSizeTop;

	MoveDir[(int)Move_Dir::R].x += Size.x;
	MoveDir[(int)Move_Dir::R].y -= CtrSizeTop;

	MoveDir[(int)Move_Dir::LT].x -= Size.x;
	MoveDir[(int)Move_Dir::LT].y += CtrSizeBottom;

	MoveDir[(int)Move_Dir::T].y += CtrSizeBottom;

	MoveDir[(int)Move_Dir::RT].x += Size.x;
	MoveDir[(int)Move_Dir::RT].y += CtrSizeBottom;

	for (int i = 0; i < (int)Move_Dir::End; ++i)
	{
		if (TileMap->GetTileType(MoveDir[i] + NextWorldPos) == Tile_Type::T_Wall)
			return true;
	}

	return false;
}

void CCharacter::Destroy()
{
	CGameObject::Destroy();
}