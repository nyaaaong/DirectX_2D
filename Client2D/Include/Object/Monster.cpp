
#include "Monster.h"
#include "Player2D.h"
#include "ItemRifle.h"
#include "ItemSniper.h"
#include "ItemLife.h"
#include "Scene/Scene.h"
#include "Component/NavAgent.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "../Scene/MainScene.h"

CMonster::CMonster() :
	m_BurnStartDelay(0.f),
	m_BurnStartDelayMax(0.4f),
	m_State(Monster_State::Idle),
	m_Player(nullptr),
	m_CurWeapon(nullptr),
	m_PlayerAngle(0.f),
	m_PlayerDist(0.f),
	m_UpdateSight(1280.f),
	m_AttackDelay(0.f),
	m_AttackDelayMax(1.f),
	m_MoveDelay(3.f),
	m_MoveDelayMax(3.f),
	m_PatternTimer(0.f),
	m_PatternTimerMax(1.f),
	m_StartDestroyBefore(false),
	m_ChangePattern(false),
	m_Move(false),
	m_CanUpdate(false),
	m_UseDropItem(true)
{
	SetTypeID<CMonster>();

	m_Type = Character_Type::Monster;

	m_vecDropItemType.resize((size_t)DropItem_Type::Max);
}

CMonster::CMonster(const CMonster& obj) :
	CCharacter(obj),
	m_BurnStartDelay(0.f),
	m_PatternTimer(0.f)
{
	SetTypeID<CMonster>();

	m_Sprite = (CSpriteComponent*)FindComponent("MonsterSprite");
	m_NavAgent = (CNavAgent*)FindComponent("NavAgnet");

	m_BurnStartDelay = 0.f;
	m_BurnStartDelayMax = obj.m_BurnStartDelayMax;

	m_Type = Character_Type::Monster;

	m_State = Monster_State::Idle;

	m_HP = obj.m_HP;

	m_Player = nullptr;

	m_AttackDelay = 0.f;
	m_AttackDelayMax = obj.m_AttackDelayMax;
	m_MoveDelay = obj.m_MoveDelay;
	m_MoveDelayMax = obj.m_MoveDelayMax;
	m_CurWeapon = nullptr;

	m_PlayerAngle = 0.f;
	m_PlayerDist = 0.f;
	m_PatternTimerMax = obj.m_PatternTimerMax;

	m_StartDestroyBefore = false;
	m_ChangePattern = false;
	m_Move = false;

	m_UseDropItem = obj.m_UseDropItem;

	m_vecDropItemType.resize((size_t)DropItem_Type::Max);

	m_UpdateSight = obj.m_UpdateSight;
}

CMonster::~CMonster()
{
}

void CMonster::Start()
{
	CCharacter::Start();

	CGameObject* Obj = m_Scene->GetPlayerObject();

	m_Player = dynamic_cast<CPlayer2D*>(Obj);

	if (!m_Player)
		ASSERT("if (!m_Player)");
}

bool CMonster::Init()
{
	if (!CCharacter::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("MonsterSprite");

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetTransparency(true);

	m_Body->SetWorldPos(m_Sprite->GetWorldPos());
	m_Body->SetCollisionProfile("Monster");
	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CMonster::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CMonster::OnCollisionEnd);

	m_Sprite->AddChild(m_Body);

	m_PaperBurn->SetMaterial(m_Sprite->GetMaterial());

	SetRootComponent(m_Sprite);

	m_NavAgent = CreateComponent<CNavAgent>("NavAgent");

	SetCurrentPattern(&CMonster::Attack);

	m_BottomOffsetY = 1.2f;

	m_PaperBurn->SetFinishCallback(this, &CMonster::Destroy);

	size_t Size = m_vecDropItemType.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecDropItemType[i] = true;
	}

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	if (!m_CanUpdate)
		return;

	if (!m_IsDied && !m_IsPaperBurn)
	{
		UpdateAttack(DeltaTime);
		UpdateMove(DeltaTime);
	}
}

void CMonster::Destroy()
{
	CCharacter::Destroy();
}

void CMonster::OnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "Player")
	{
		((CPlayer2D*)result.Dest->GetGameObject())->AddDamage(m_Damage);
		return;	
	}

	CCharacter::OnCollisionBegin(result);
}

void CMonster::OnCollisionEnd(const CollisionResult& result)
{
	CCharacter::OnCollisionEnd(result);
}

void CMonster::Calc(float DeltaTime)
{
	CCharacter::Calc(DeltaTime);

	CSceneMode* SceneMode = m_Scene->GetSceneMode();
	CMainScene* MainScene = dynamic_cast<CMainScene*>(SceneMode);

	if (!MainScene)
		ASSERT("if (!MainScene)");

	char	Text[256] = {};
	sprintf_s(Text, "m_PlayerDir : %.1f, %.1f", m_PlayerDir.x, m_PlayerDir.y);

	MainScene->SetWidgetText(Text);

	m_PlayerWorldPos = m_Player->GetWorldPos();

	m_PlayerDist = GetWorldPos().Distance(m_PlayerWorldPos);

	if (m_PlayerDist <= m_UpdateSight)
		m_CanUpdate = true;

	else
	{
		m_CanUpdate = false;
		return;
	}

	Vector3	WorldPos = GetWorldPos();

	m_PlayerAngle = atan2(m_PlayerWorldPos.y - WorldPos.y, m_PlayerWorldPos.x - WorldPos.x) * (180.f / PI);

	m_PlayerDir = Vector3::ConvertDir(m_PlayerAngle);

	if (!m_IsDied)
		m_State = Monster_State::Idle;

	UpdateDropItemType();
	UpdateGun();
}

void CMonster::PaperBurnEnd()
{
	CCharacter::PaperBurnEnd();
}

void CMonster::Dead(float DeltaTime)
{
	if (m_HP <= 0.f && !m_IsDied)
	{
		CCharacter::Dead(DeltaTime);

		PlaySoundDie();

		m_IsDied = true;

		m_HP = 0.f;
		m_Body->Enable(false);
		m_Body->SetRender(false);
		
		m_State = Monster_State::Die;
	}

	if (m_UsePaperburn)
	{
		if (m_BurnStartDelay < m_BurnStartDelayMax)
			m_BurnStartDelay += DeltaTime;

		else if (m_IsDied && !m_IsPaperBurn && m_BurnStartDelay >= m_BurnStartDelayMax)
		{
			// 죽는 애니메이션이 실행중이며 만약 애니메이션이 끝났다면 페이퍼번을 실행시킨다.
			if (m_Sprite->GetAnimationInstance()->IsEnd())
			{
				m_Sprite->GetAnimationInstance()->Stop();

				m_IsPaperBurn = true;

				m_PaperBurn->StartPaperBurn();

				m_Sprite->SetOpacity(0.5f);

				DropItem();
			}
		}
	}

	// 페이퍼번을 사용하지 않을때
	else
	{
		if (m_IsDied)
		{
			// 죽는 애니메이션이 실행중이며 만약 애니메이션이 끝났다면
			if (m_Sprite->GetAnimationInstance()->IsEnd())
			{
				m_Sprite->GetAnimationInstance()->Stop();

				DropItem();

				Destroy();
			}

			else if (!m_StartDestroyBefore)
				DestroyBefore();
		}
	}
}

void CMonster::Hit(float DeltaTime)
{
	CCharacter::Hit(DeltaTime);
}

void CMonster::Move(float DeltaTime)
{
	m_State = Monster_State::Walk;

	Vector3	WorldPos = GetWorldPos();
	WorldPos.z = 0.f;

	CCharacter::Move(WorldPos + RandomPos());
}

void CMonster::Attack(float DeltaTime)
{
}

void CMonster::PlaySoundDie()
{
}

void CMonster::DestroyBefore()
{
	m_StartDestroyBefore = true;
}

void CMonster::HideAllWeapon()
{
	m_Weapon->SetRender(false);
	m_WeaponL->SetRender(false);

	m_CurWeapon = nullptr;
}

void CMonster::UpdateGun()
{
	HideAllWeapon();

	if (m_IsDied)
		return;

	if ((180.999f >= m_PlayerAngle && m_PlayerAngle > 90.999f) ||
		(-180.999f <= m_PlayerAngle && m_PlayerAngle < -90.999f))
	{
		m_WeaponL->SetRender(true);
		m_CurWeapon = m_WeaponL;
	}

	else
	{
		m_Weapon->SetRender(true);
		m_CurWeapon = m_Weapon;
	}

	UpdateGunDir(m_CurWeapon);	
}

void CMonster::UpdateGunDir(CSpriteComponent* Weapon)
{
	Weapon->SetRelativeRotationZ(m_PlayerAngle);
}

void CMonster::UpdateDropItemType()
{
	if (!m_Player->HasWeaponRifle())
		SetDropItemType(DropItem_Type::Rifle);

	else
		DeleteDropItemType(DropItem_Type::Rifle);

	if (!m_Player->HasWeaponSniper())
		SetDropItemType(DropItem_Type::Sniper);

	else
		DeleteDropItemType(DropItem_Type::Sniper);
}

void CMonster::UpdateAttack(float DeltaTime)
{
	m_AttackDelay += DeltaTime;

	if (m_AttackDelay >= m_AttackDelayMax)
	{
		m_AttackDelay = 0.f;

		Attack(DeltaTime);
	}
}

void CMonster::UpdateMove(float DeltaTime)
{
	// 플레이어의 공격에 맞고 죽을때 움직이는 것을 방지하기 위함
	if (m_Player->GetDamage() * 3.f >= m_HP)
		return;

	m_MoveDelay += DeltaTime;

	if (m_MoveDelay >= m_MoveDelayMax)
	{
		m_MoveDelay = 0.f;

		Move(DeltaTime);
	}
}

void CMonster::DropItem()
{
	if (!m_UseDropItem)
		return;

	std::vector<DropItem_Type>	vecRandItem;

	for (int i = (int)DropItem_Type::Rifle; i < (int)DropItem_Type::Max; ++i)
	{
		if (IsDropItemType(i))
			vecRandItem.push_back((DropItem_Type)i);
	}

	size_t Size = vecRandItem.size();

	if (!Size)
		return;

	float	Percent = rand() % 10000 / 100.f;
	int		Index = rand() % Size;

	if (Percent <= 20.f)
		CreateItem(vecRandItem[Index]);
}

void CMonster::CreateItem(DropItem_Type Type)
{
	switch (Type)
	{
	case DropItem_Type::Rifle:
	{
		CItemRifle* NewItem = m_Scene->CreateGameObject<CItemRifle>("Rifle");
		NewItem->SetWorldPos(GetWorldPos());
	}
		break;
	case DropItem_Type::Sniper:
	{
		CItemSniper* NewItem = m_Scene->CreateGameObject<CItemSniper>("Sniper");
		NewItem->SetWorldPos(GetWorldPos());
	}		
		break;
	case DropItem_Type::Life:
	{
		CItemLife* NewItem = m_Scene->CreateGameObject<CItemLife>("Life");
		NewItem->SetWorldPos(GetWorldPos());
	}
		break;
	}
}

void CMonster::ChangePatternStartFunc(float DeltaTime)
{
}

Vector3 CMonster::RandomPos() const
{
	Vector3	RandPos;

	float	Rand1 = rand() % 10000 / 100.f;

	RandPos = m_PlayerDir * Rand1;

	return RandPos;
}

void CMonster::ChangePattern(float DeltaTime)
{
	if (m_IsDied)
		return;

	if (m_ChangePattern)
	{
		m_ChangePattern = false;

		float RandF = rand() % 10000 / 100.f;

		if (RandF < 50.f)
		{
			SetCurrentPattern(&CMonster::Move);

			m_Move = false;
		}

		else
			SetCurrentPattern(&CMonster::Attack);
	}
}

void CMonster::SetCurrentPattern(void(CMonster::*Func)(float))
{
	m_CurPattern = std::bind(Func, this, std::placeholders::_1);
}
