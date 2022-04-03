
#include "Monster.h"
#include "Player2D.h"
#include "Scene/Scene.h"
#include "Component/NavAgent.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "../Scene/MainScene.h"

CMonster::CMonster() :
	m_BurnStartDelay(0.f),
	m_BurnStartDelayMax(0.4f),
	m_State(Monster_State::Idle),
	m_Player(nullptr),
	m_AttackTimer(0.f),
	m_AttackTimerMax(1.f),
	m_AttackCoolDown(false),
	m_CurWeapon(nullptr),
	m_PlayerAngle(0.f),
	m_PlayerDist(0.f),
	m_UpdateSight(1580.f),
	m_PatternTimer(0.f),
	m_PatternTimerMax(2.f),
	m_StartDestroyBefore(false),
	m_ChangePattern(false),
	m_Move(false),
	m_CanUpdate(false)
{
	SetTypeID<CMonster>();

	m_Type = Character_Type::Monster;

	m_HP = 20.f;
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

	m_AttackTimer = 0.f;
	m_AttackTimerMax = obj.m_AttackTimerMax;
	m_AttackCoolDown = false;
	m_CurWeapon = nullptr;

	m_PlayerAngle = 0.f;
	m_PlayerDist = 0.f;
	m_PatternTimerMax = obj.m_PatternTimerMax;

	m_StartDestroyBefore = false;
	m_ChangePattern = false;
	m_Move = false;
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

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	if (!m_CanUpdate)
		return;
	
	ChangePattern(DeltaTime);

	m_CurPattern(DeltaTime);
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

	if (!m_ChangePattern)
	{
		m_PatternTimer += DeltaTime;

		if (m_PatternTimer >= m_PatternTimerMax)
		{
			m_PatternTimer = 0.f;

			m_ChangePattern = true;
		}
	}

	UpdateGun();
	UpdateAttackCoolDown(DeltaTime);
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
	if (m_IsDied || m_Move)
		return;

	m_Move = true;

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

void CMonster::UpdateAttackCoolDown(float DeltaTime)
{
	if (m_AttackCoolDown)
	{
		m_AttackTimer += DeltaTime;

		if (m_AttackTimer >= m_AttackTimerMax)
		{
			m_AttackTimer = 0.f;
			m_AttackCoolDown = false;
		}
	}
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

Vector3 CMonster::RandomPos() const
{
	Vector3	RandPos;

	float	Rand1 = rand() % 10000 / 100.f;
	float	Rand2 = rand() % 10000 / 300.f + 300.f;
	float	Rand4 = rand() % 10000 / 200.f;
	float	Rand3 = rand() % 10000 / 100.f;

	if (Rand1 <= 25.f)
		RandPos.x = Rand2;

	else if (Rand1 <= 50.f)
		RandPos.y = Rand2;

	else if (Rand1 <= 75.f)
	{
		RandPos.x = Rand2;
		RandPos.y = Rand4;
	}

	else
	{
		RandPos.x = Rand4;
		RandPos.y = Rand2;
	}

	if (Rand3 <= 12.5f)
		RandPos.x = RandPos.x > 0.f ? RandPos.x *= -1.f : RandPos.x;

	else if (Rand3 <= 25.f)
		RandPos.y = RandPos.y > 0.f ? RandPos.y *= -1.f : RandPos.y;

	else if (Rand3 <= 37.5f)
		RandPos.x = RandPos.x > 0.f ? RandPos.x : RandPos.x *= -1.f;

	else if (Rand3 <= 50.f)
		RandPos.y = RandPos.y > 0.f ? RandPos.y : RandPos.y *= -1.f;

	else if (Rand3 <= 62.5f)
	{
		RandPos.x = RandPos.x > 0.f ? RandPos.x *= -1.f : RandPos.x;
		RandPos.y = RandPos.y > 0.f ? RandPos.y *= -1.f : RandPos.y;
	}

	else if (Rand3 <= 75.f)
	{
		RandPos.x = RandPos.x > 0.f ? RandPos.x *= -1.f : RandPos.x;
		RandPos.y = RandPos.y > 0.f ? RandPos.y : RandPos.y *= -1.f;
	}

	else if (Rand3 <= 87.5f)
	{
		RandPos.x = RandPos.x > 0.f ? RandPos.x : RandPos.x *= -1.f;
		RandPos.y = RandPos.y > 0.f ? RandPos.y *= -1.f : RandPos.y;
	}

	else
	{
		RandPos.x = RandPos.x > 0.f ? RandPos.x : RandPos.x *= -1.f;
		RandPos.y = RandPos.y > 0.f ? RandPos.y : RandPos.y *= -1.f;
	}

	return RandPos;
}

void CMonster::ChangePattern(float DeltaTime)
{
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
