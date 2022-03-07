
#include "Player2D.h"
#include "Bullet.h"
#include "BubbleParticle.h"
#include "Input.h"
#include "PlayerAnimation2D.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/NavigationManager.h"
#include "Resource/Material/Material.h"
#include "../Widget/SimpleHUD.h"
#include "../Scene/MainScene.h"

CPlayer2D::CPlayer2D() :
	m_EnableInput(true),
	m_Dodge(false),
	m_AttackTimer(0.f),
	m_AttackCoolDown(false),
	m_Move(false),
	m_SetCameraInfo(false),
	m_MoveSpeed(400.f),
	m_Dir(0)
{
	SetTypeID<CPlayer2D>();
	m_SolW = false;
	m_WDistance = 0.f;
	m_Opacity = 1.f;

	m_AttackTimerMax = 0.3f;
}

CPlayer2D::CPlayer2D(const CPlayer2D& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("PlayerSprite");

	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_SimpleHUDWidget = (CWidgetComponent*)FindComponent("SimpleHUD");

	m_Opacity = obj.m_Opacity;
	m_Dodge = false;
	m_Move = false;

	m_AttackTimer = 0.f;
	m_AttackTimerMax = obj.m_AttackTimerMax;
	m_AttackCoolDown = false;

	m_MoveSpeed = obj.m_MoveSpeed;

	m_Dir = 0;

	m_SetCameraInfo = false;
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::SetDir(Character_Direction Dir)
{
	switch (Dir)
	{
	case Character_Direction::Down:
		m_Dir &= ~(int)Character_Direction::Up;
		break;
	case Character_Direction::Left:
		m_Dir &= ~(int)Character_Direction::Right;
		break;
	case Character_Direction::Right:
		m_Dir &= ~(int)Character_Direction::Left;
		break;
	case Character_Direction::Up:
		m_Dir &= ~(int)Character_Direction::Down;
		break;
	}

	m_Dir |= (int)Dir;
}

void CPlayer2D::ClearDir(Character_Direction Dir)
{
	m_Dir &= ~(int)Dir;
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	//Vector2	Size = GetAnimationSize2D();
	//m_Body->SetExtent(Size);
}

bool CPlayer2D::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("PlayerSprite");

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_Body->SetExtent(30.f, 30.f);

	m_Camera = CreateComponent<CCameraComponent>("Camera");

	m_SimpleHUDWidget = CreateComponent<CWidgetComponent>("SimpleHUD");

	m_SimpleHUDWidget->CreateWidgetWindow<CSimpleHUD>("SimpleHUDWidget");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Player");

	m_Camera->OnViewportCenter();
	//m_Camera->SetViewportRatio(0.7f, 0.7f);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Camera);
	m_Sprite->AddChild(m_SimpleHUDWidget);

	m_SimpleHUDWidget->SetRelativePos(-50.f, 50.f, 0.f);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CPlayerAnimation2D>();

	m_Sprite->SetRelativePos(650.f, 600.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveUp", KeyState_Push, this, &CPlayer2D::MoveUp);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveDown", KeyState_Push, this, &CPlayer2D::MoveDown);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveLeft", KeyState_Push, this, &CPlayer2D::MoveLeft);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveRight", KeyState_Push, this, &CPlayer2D::MoveRight);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("RotationZInv", KeyState_Push, this, &CPlayer2D::RotationZInv);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("RotationZ", KeyState_Push, this, &CPlayer2D::RotationZ);
	//CInput::GetInst()->SetKeyCallback<CPlayer2D>("Attack", KeyState_Down, this, &CPlayer2D::Attack);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Dodge", KeyState_Down, this, &CPlayer2D::Dodge);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Attack1", KeyState_Push, this, &CPlayer2D::Attack1);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("test", KeyState_Push, this, &CPlayer2D::test);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MovePoint", KeyState_Down, this, &CPlayer2D::MovePointDown);

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_SetCameraInfo)
	{
		CSceneMode* SceneMode = m_Scene->GetSceneMode();
		CMainScene* Scene = dynamic_cast<CMainScene*>(SceneMode);

		if (!Scene)
			return;

		CTileMap* TileMap = Scene->GetTileMap();

		if (TileMap)
		{
			m_SetCameraInfo = true;

			Vector3	StartPos, EndPos;

			float	Count = static_cast<float>(TileMap->GetTileCountX() * TileMap->GetTileCountY());

			EndPos.x = Count;
			EndPos.y = Count;

			m_Camera->SetCameraLimit(StartPos, EndPos);
		}
	}

	if (m_Sprite && m_Move)
	{
		if (!CInput::GetInst()->IsKeyDown("MoveUp") && !CInput::GetInst()->IsKeyDown("MoveDown") &&
			!CInput::GetInst()->IsKeyDown("MoveLeft") && !CInput::GetInst()->IsKeyDown("MoveRight"))
			m_Move = false;
	}

	if (m_AttackCoolDown)
	{
		m_AttackTimer += DeltaTime;

		if (m_AttackTimer >= m_AttackTimerMax)
		{
			m_AttackTimer = 0.f;
			m_AttackCoolDown = false;
		}
	}

	static bool	Hide = false;

	if (Hide)
	{
		m_Opacity -= DeltaTime / 5.f;

		if (m_Opacity < 0.f)
			m_Opacity = 0.f;

		m_Sprite->SetOpacity(m_Opacity);
	}

	Action(DeltaTime);
	UpdateAnimDir();
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer2D* CPlayer2D::Clone()
{
	return DBG_NEW CPlayer2D(*this);
}

void CPlayer2D::MoveUp(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Move = true;

	SetDir(Character_Direction::Up);

	Vector3	Result = m_Sprite->GetWorldAxis(AXIS_Y) * m_MoveSpeed * DeltaTime;

	if (!IsNormalTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::MoveDown(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Move = true;

	SetDir(Character_Direction::Down);

	Vector3	Result = m_Sprite->GetWorldAxis(AXIS_Y) * -m_MoveSpeed * DeltaTime;

	if (!IsNormalTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::MoveLeft(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Move = true;

	SetDir(Character_Direction::Left);

	Vector3	Result = m_Sprite->GetWorldAxis(AXIS_X) * -m_MoveSpeed * DeltaTime;

	if (!IsNormalTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::MoveRight(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Move = true;

	SetDir(Character_Direction::Right);

	Vector3	Result = m_Sprite->GetWorldAxis(AXIS_X) * m_MoveSpeed * DeltaTime;

	if (!IsNormalTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::RotationZInv(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Sprite->AddRelativeRotationZ(180.f * DeltaTime);
}

void CPlayer2D::RotationZ(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Sprite->AddRelativeRotationZ(-180.f * DeltaTime);
}

void CPlayer2D::Dodge(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Move = true;

	m_EnableInput = false;
	m_Dodge = true;

	m_Sprite->GetAnimationInstance()->ChangeAnimation("PlayerDodgeD");
}

void CPlayer2D::DodgeEnd(float DeltaTime)
{
	m_EnableInput = true;

	m_Move = false;

	m_Sprite->GetAnimationInstance()->ChangeAnimation("PlayerIdleD");
}

void CPlayer2D::Attack(float DeltaTime)
{
	if (!m_EnableInput || m_AttackCoolDown)
		return;

	m_AttackCoolDown = true;

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldRotation(GetWorldRot());
	Bullet->SetCollisionProfile("PlayerAttack");

	Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldRotation(GetWorldRot());
	Bullet->SetCollisionProfile("PlayerAttack");

	Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldRotation(GetWorldRot());
	Bullet->SetCollisionProfile("PlayerAttack");
}

void CPlayer2D::Attack1(float DeltaTime)
{
	if (!m_EnableInput || m_AttackCoolDown)
		return;

	m_AttackCoolDown = true;

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldRotation(GetWorldRot());
	Bullet->SetCollisionProfile("PlayerAttack");

	Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldRotation(GetWorldRot() + Vector3(0.f, 0.f, 45.f));
	Bullet->SetCollisionProfile("PlayerAttack");

	Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldRotation(GetWorldRot() + Vector3(0.f, 0.f, -45.f));
	Bullet->SetCollisionProfile("PlayerAttack");
}

void CPlayer2D::test(float DeltatTime)
{
	int a = 0;
}

void CPlayer2D::UpdateAnimDir()
{
	if (CInput::GetInst()->IsKeyDown("MoveUp") || CInput::GetInst()->IsKeyDown("MoveDown"))
	{
		if (!CInput::GetInst()->IsKeyDown("MoveLeft") && IsDir(Character_Direction::Left))
			ClearDir(Character_Direction::Left);

		if (!CInput::GetInst()->IsKeyDown("MoveRight") && IsDir(Character_Direction::Right))
			ClearDir(Character_Direction::Right);
	}

	else if (CInput::GetInst()->IsKeyDown("MoveLeft") || CInput::GetInst()->IsKeyDown("MoveRight"))
	{
		if (!CInput::GetInst()->IsKeyDown("MoveUp") && IsDir(Character_Direction::Up))
			ClearDir(Character_Direction::Up);

		if (!CInput::GetInst()->IsKeyDown("MoveDown") && IsDir(Character_Direction::Down))
			ClearDir(Character_Direction::Down);
	}

	ChangeAnimIdle();
	ChangeAnimWalk();
}

void CPlayer2D::Action(float DeltaTime)
{
	if (m_Dodge)
	{
		if (!m_Sprite->GetAnimationInstance()->CheckCurrentAnimation("PlayerDodgeD"))
		{
			m_Dodge = false;
			m_EnableInput = true;
		}

		else
			m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_Y) * -600.f * DeltaTime);
	}
}

void CPlayer2D::MovePointDown(float DeltaTime)
{
	Vector2 MousePos = CInput::GetInst()->GetMouseWorld2DPos();

	m_Scene->GetNavigationManager()->FindPath<CPlayer2D>(this, &CPlayer2D::PathResult, GetWorldPos(),
														 Vector3(MousePos.x, MousePos.y, 0.f));
}

void CPlayer2D::PathResult(const std::list<Vector3>& PathList)
{
	if (PathList.empty())
	{
	}

	else
	{
	}
}

void CPlayer2D::ChangeAnimIdle()
{
	if (!m_Move)
	{
		if (IsDir(Character_Direction::Down) && !IsDir(Character_Direction::Left) && !IsDir(Character_Direction::Right))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Idle_D");
		}

		else if (IsDir(Character_Direction::Up))
		{
			if (IsDir(Character_Direction::Left))
			{
				m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Idle_UL");
				return;
			}

			else if (IsDir(Character_Direction::Right))
			{
				m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Idle_UR");
				return;
			}

			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Idle_U");
		}

		else if (IsDir(Character_Direction::Left))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Idle_DL");
			return;
		}

		else if (IsDir(Character_Direction::Right))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Idle_DR");
			return;
		}
	}
}

void CPlayer2D::ChangeAnimWalk()
{
	if (m_Move)
	{
		if (IsDir(Character_Direction::Down) && !IsDir(Character_Direction::Left) && !IsDir(Character_Direction::Right))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Walk_D");
		}

		else if (IsDir(Character_Direction::Up))
		{
			if (IsDir(Character_Direction::Left))
			{
				m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Walk_UL");
				return;
			}

			else if (IsDir(Character_Direction::Right))
			{
				m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Walk_UR");
				return;
			}

			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Walk_U");
		}

		else if (IsDir(Character_Direction::Left))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Walk_DL");
			return;
		}

		else if (IsDir(Character_Direction::Right))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Walk_DR");
			return;
		}
	}
}

bool CPlayer2D::IsNormalTile(const Vector3& NextWorldPos)
{
	CSceneMode* SceneMode = CSceneManager::GetInst()->GetSceneMode();
	CMainScene* Scene = dynamic_cast<CMainScene*>(SceneMode);

	if (!Scene)
		return false;

	CTileMap* TileMap = Scene->GetTileMap();

	if (!TileMap)
		return false;

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
		if (TileMap->GetTileType(MoveDir[i] + NextWorldPos) != Tile_Type::Normal)
			return false;
	}

	return true;
}
