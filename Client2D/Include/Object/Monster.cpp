
#include "Monster.h"
#include "Player2D.h"
#include "Scene/Scene.h"
#include "Component/NavAgent.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "../Scene/MainScene.h"

CMonster::CMonster() :
	m_BurnStartDelay(0.f),
	m_BurnStartDelayMax(0.5f),
	m_State(Monster_State::Idle),
	m_MoveTimer(0.f),
	m_MoveTimerMax(2.f),
	m_Follow(false),
	m_Player(nullptr),
	m_FollowFirst(true),
	m_InsideLimit(false)
{
	SetTypeID<CMonster>();

	m_Type = Character_Type::Monster;

	m_HP = 20.f;
}

CMonster::CMonster(const CMonster& obj) :
	CCharacter(obj),
	m_BurnStartDelay(0.f),
	m_MoveTimer(0.f)
{
	SetTypeID<CMonster>();

	m_Sprite = (CSpriteComponent*)FindComponent("MonsterSprite");

	m_BurnStartDelay = 0.f;
	m_BurnStartDelayMax = obj.m_BurnStartDelayMax;

	m_MoveTimerMax = obj.m_MoveTimerMax;

	m_Type = Character_Type::Monster;

	m_State = Monster_State::Idle;

	m_Follow = obj.m_Follow;

	m_HP = obj.m_HP;

	m_Player = nullptr;
	m_FollowFirst = true;
	m_InsideLimit = false;
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
	m_Sprite->AddChild(m_Body);

	m_PaperBurn->SetMaterial(m_Sprite->GetMaterial());

	SetRootComponent(m_Sprite);

	m_NavAgent = CreateComponent<CNavAgent>("NavAgent");

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
	CSceneMode* SceneMode = m_Scene->GetSceneMode();
	CMainScene* MainScene = dynamic_cast<CMainScene*>(SceneMode);

	if (!MainScene)
		ASSERT("if (!MainScene)");

	char	Text[256] = {};
	sprintf_s(Text, "MonsterWorldPos : (%.1f, %1.f)", GetWorldPos().x, GetWorldPos().y);

	MainScene->SetWidgetText(Text);

	Calc(DeltaTime);
	Move(DeltaTime);
	//Attack(DeltaTime);
}

void CMonster::Destroy()
{
	CCharacter::Destroy();
}

void CMonster::OnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "Player")
		return;

	else if (result.Dest->GetCollisionProfile()->Name == "SightLimit")
	{
		m_InsideLimit = true;
		return;
	}

	CCharacter::OnCollisionBegin(result);
}

void CMonster::OnCollisionEnd(const CollisionResult& result)
{
	CCharacter::OnCollisionEnd(result);

	if (result.Dest->GetCollisionProfile()->Name == "SightLimit")
		m_InsideLimit = false;
}

void CMonster::Calc(float DeltaTime)
{
	m_PlayerWorldPos = m_Player->GetWorldPos();
	m_PlayerPos = m_PlayerWorldPos - GetWorldPos();

	m_PlayerDir = m_PlayerPos;
	m_PlayerDir.Normalize();

	m_State = Monster_State::Idle;
}

void CMonster::PaperBurnEnd()
{
	CCharacter::PaperBurnEnd();
}

void CMonster::Dead(float DeltaTime)
{
	if (m_BurnStartDelay < m_BurnStartDelayMax)
		m_BurnStartDelay += DeltaTime;

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

	else if (m_IsDied && !m_IsPaperBurn && m_BurnStartDelay >= m_BurnStartDelayMax)
	{
		// 죽는 애니메이션이 실행중이며 만약 애니메이션이 끝났다면 페이퍼번을 실행한다.
		if (m_Sprite->GetAnimationInstance()->IsEnd())
		{
			m_Sprite->GetAnimationInstance()->Stop();

			m_IsPaperBurn = true;

			m_PaperBurn->StartPaperBurn();
		}
	}
}

void CMonster::Hit(float DeltaTime)
{
	CCharacter::Hit(DeltaTime);
}

void CMonster::Move(float DeltaTime)
{
	if (m_IsDied)
		return;

	//if (!m_Follow)
	//	return;

	else if (m_MoveTimer < m_MoveTimerMax)
		return;

	else if (m_InsideLimit)
	{
		m_MoveTimer = m_MoveTimerMax;
		return;
	}

	m_MoveTimer += DeltaTime;

	CCharacter::Move(m_PlayerWorldPos);
	//m_NavAgent

	/*m_State = Monster_State::Idle;

	
	Vector3	NextMovePos = GetWorldPos() + m_PlayerDir * m_MoveSpeed * DeltaTime; 

	if (!IsWallTile(NextMovePos))
	{
		SetWorldPos(NextMovePos);
		m_State = Monster_State::Walk;
	}*/
}

void CMonster::Attack(float DeltaTime)
{
}

void CMonster::PlaySoundDie()
{
}
