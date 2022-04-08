
#include "Player2D.h"
#include "Bullet.h"
#include "Input.h"
#include "PlayerAnimation2D.h"
#include "Device.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/Material/Material.h"
#include "Component/CameraComponent.h"
#include "../Widget/PlayerWidget.h"
#include "../Scene/MainScene.h"

CPlayer2D::CPlayer2D() :
	m_EnableInput(true),
	m_AttackDelay(0.f),
	m_DodgeTimer(0.f),
	m_DodgeTimerMax(0.5f),
	m_AttackCoolDown(false),
	m_DodgeCoolDown(false),
	m_Move(false),
	m_SetCameraInfo(false),
	m_PierceBullet(false),
	m_Dir(0),
	m_MoveDir(0),
	m_DodgeSpeed(0.f),
	m_MouseAngle(0.f),
	m_NoHitTimer(0.f),
	m_NoHitTimerMax(3.f),
	m_BlinkTimer(0.f),
	m_BlinkTimerMax(0.3f),
	m_WeaponSlot(Weapon_Slot::None),
	m_CurWeapon(nullptr),
	m_PlayerUI(nullptr),
	m_HasRifle(false),
	m_HasSniper(false),
	m_Invisible(false),
	m_Invincibility(false)
{
	SetTypeID<CPlayer2D>();
	m_Opacity = 1.f;

	m_AttackDelayMax = 0.6f;

	m_Type = Character_Type::Player;

	m_MoveSpeed = 500.f;

	m_TopOffsetY = 1.4f;
	m_BottomOffsetY = 0.2f;

	m_UsePaperburn = false;
}

CPlayer2D::CPlayer2D(const CPlayer2D& obj) :
	CCharacter(obj)
{
	SetTypeID<CPlayer2D>();

	m_Sprite = (CSpriteComponent*)FindComponent("PlayerSprite");

	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_PlayerWidget = (CWidgetComponent*)FindComponent("PlayerWidget");

	m_Opacity = obj.m_Opacity;
	m_Move = false;
	m_PierceBullet = false;

	m_AttackDelay = 0.f;
	m_AttackDelayMax = obj.m_AttackDelayMax;
	m_AttackCoolDown = false;

	m_DodgeSpeed = 0.f;
	m_DodgeTimer = 0.f;
	m_DodgeTimerMax = obj.m_DodgeTimerMax;
	m_DodgeCoolDown = false;

	m_Dir = 0;
	m_MoveDir = 0;
	m_MouseAngle = 0.f;
	m_NoHitTimer = 0.f;
	m_NoHitTimerMax = obj.m_BlinkTimerMax;
	m_BlinkTimer = 0.f;
	m_BlinkTimerMax = obj.m_BlinkTimerMax;

	m_SetCameraInfo = false;
	m_Invisible = false;
	m_Invincibility = false;

	m_WeaponSlot = Weapon_Slot::None;

	m_Type = Character_Type::Player;

	m_UsePaperburn = false;

	m_HasRifle = false;
	m_HasSniper = false;

	m_PlayerUI = nullptr;
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::AddWeaponRifle()
{
	m_HasRifle = true;

	Weapon2(CEngine::GetInst()->GetDeltaTime());
}

void CPlayer2D::AddWeaponSniper()
{
	m_HasSniper = true;

	Weapon3(CEngine::GetInst()->GetDeltaTime());
}

bool CPlayer2D::Init()
{
	if (!CCharacter::Init())
		return false;

	m_Sprite = CreateComponent<CSpriteComponent>("PlayerSprite");

	m_Sprite->SetTransparency(true);
	m_Sprite->CreateAnimationInstance<CPlayerAnimation2D>();
	m_Sprite->SetRelativePos(650.f, 600.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	SetRootComponent(m_Sprite);

	m_Body->SetExtent(30.f, 30.f);
	m_Body->SetCollisionProfile("Player");
	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CPlayer2D::OnCollisionBegin);

	m_Sprite->AddChild(m_Body);

	m_Weapon1 = CreateComponent<CSpriteComponent>("Weapon1Sprite");
	m_Weapon1L = CreateComponent<CSpriteComponent>("Weapon1LSprite");
	m_Weapon2 = CreateComponent<CSpriteComponent>("Weapon2Sprite");
	m_Weapon2L = CreateComponent<CSpriteComponent>("Weapon2LSprite");
	m_Weapon3 = CreateComponent<CSpriteComponent>("Weapon3Sprite");
	m_Weapon3L = CreateComponent<CSpriteComponent>("Weapon3LSprite");

	m_Sprite->AddChild(m_Weapon1);
	m_Sprite->AddChild(m_Weapon1L);
	m_Sprite->AddChild(m_Weapon2);
	m_Sprite->AddChild(m_Weapon2L);
	m_Sprite->AddChild(m_Weapon3);
	m_Sprite->AddChild(m_Weapon3L);

	m_Weapon1->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Weapon1", TEXT("Weapon/Right/Weapon1.png"));
	m_Weapon2->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Weapon2", TEXT("Weapon/Right/Weapon2.png"));
	m_Weapon3->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Weapon3", TEXT("Weapon/Right/Weapon3.png"));
	m_Weapon1L->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Weapon1L", TEXT("Weapon/Left/Weapon1L.png"));
	m_Weapon2L->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Weapon2L", TEXT("Weapon/Left/Weapon2L.png"));
	m_Weapon3L->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Weapon3L", TEXT("Weapon/Left/Weapon3L.png"));

	m_Weapon1->SetRelativeScale(54.f, 30.f, 1.f);
	m_Weapon1L->SetRelativeScale(54.f, 30.f, 1.f);
	m_Weapon2->SetRelativeScale(78.f, 21.f, 1.f);
	m_Weapon2L->SetRelativeScale(78.f, 21.f, 1.f);
	m_Weapon3->SetRelativeScale(90.f, 27.f, 1.f);
	m_Weapon3L->SetRelativeScale(90.f, 27.f, 1.f);

	m_Weapon1->SetRelativePos(-15.f, -26.f, 0.f);
	m_Weapon1L->SetRelativePos(15.f, 0.f, 0.f);
	m_Weapon2->SetRelativePos(-15.f, -26.f, 0.f);
	m_Weapon2L->SetRelativePos(15.f, 0.f, 0.f);
	m_Weapon3->SetRelativePos(-15.f, -26.f, 0.f);
	m_Weapon3L->SetRelativePos(15.f, 0.f, 0.f);

	m_Weapon1->SetPivotX(-1.f);
	m_Weapon1L->SetPivotX(-1.f);
	m_Weapon2->SetPivotX(-1.f);
	m_Weapon2L->SetPivotX(-1.f);
	m_Weapon3->SetPivotX(-1.f);
	m_Weapon3L->SetPivotX(-1.f);

	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Camera->OnViewportCenter();

	m_Sprite->AddChild(m_Camera);

	m_PlayerWidget = CreateComponent<CWidgetComponent>("PlayerWidget");
	m_PlayerWidget->SetRelativePos(-50.f, 50.f, 0.f);

	m_PlayerUI = m_PlayerWidget->CreateWidgetWindow<CPlayerWidget>("PlayerUI");
	m_PlayerUI->SetHPDir(ProgressBar_Dir::RightToLeft);

	m_Sprite->AddChild(m_PlayerWidget);

	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveUp", KeyState_Push, this, &CPlayer2D::MoveUp);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveDown", KeyState_Push, this, &CPlayer2D::MoveDown);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveLeft", KeyState_Push, this, &CPlayer2D::MoveLeft);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("MoveRight", KeyState_Push, this, &CPlayer2D::MoveRight);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Dodge", KeyState_Down, this, &CPlayer2D::DodgeStart);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Attack", KeyState_Push, this, &CPlayer2D::Attack);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("NoWeapon", KeyState_Down, this, &CPlayer2D::NoWeapon);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Weapon1", KeyState_Down, this, &CPlayer2D::Weapon1);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Weapon2", KeyState_Down, this, &CPlayer2D::Weapon2);
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Weapon3", KeyState_Down, this, &CPlayer2D::Weapon3);

	return true;
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

void CPlayer2D::SetMoveDir(Character_Direction Dir)
{
	switch (Dir)
	{
	case Character_Direction::Down:
		m_MoveDir &= ~(int)Character_Direction::Up;
		break;
	case Character_Direction::Left:
		m_MoveDir &= ~(int)Character_Direction::Right;
		break;
	case Character_Direction::Right:
		m_MoveDir &= ~(int)Character_Direction::Left;
		break;
	case Character_Direction::Up:
		m_MoveDir &= ~(int)Character_Direction::Down;
		break;
	}

	m_MoveDir |= (int)Dir;
}

void CPlayer2D::DeleteDir(Character_Direction Dir)
{
	m_Dir &= ~(int)Dir;
}

void CPlayer2D::DeleteMoveDir(Character_Direction Dir)
{
	m_MoveDir &= ~(int)Dir;
}

void CPlayer2D::Start()
{
	CCharacter::Start();

	Vector3	WorldPos = GetWorldPos();

	m_Body->SetWorldPos(WorldPos);

	CSharedPtr<CSceneMode> SceneMode = CSceneManager::GetInst()->GetSceneMode();

	CharacterInfo	PlayerInfo = SceneMode->GetPlayerInfo();
	m_PrevHP = PlayerInfo.HP;
	m_HP = PlayerInfo.HP;
	m_HPMax = PlayerInfo.HP;
	m_MoveSpeed = PlayerInfo.MoveSpeed;
	m_Damage = PlayerInfo.Damage;

	m_DodgeSpeed = m_MoveSpeed * 2.f;
}

void CPlayer2D::Calc(float DeltaTime)
{
	CCharacter::Calc(DeltaTime);

	if (!CEngine::GetInst()->IsFocusClient())
		return;

	UpdateMouseAngle();
	UpdatePlayerLife(DeltaTime);
	UpdateMousePos();
	UpdateGun();

	UpdateAttackCoolDown(DeltaTime);
	UpdateDodgeCoolDown(DeltaTime);

	UpdateAnimDir();

	if (m_DodgeCoolDown)
		Dodge(DeltaTime);
}

void CPlayer2D::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	if (!CEngine::GetInst()->IsFocusClient())
		return;

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

			EndPos.x = TileMap->GetTileCountX() * TileMap->GetTileSize().x;
			EndPos.y = TileMap->GetTileCountY() * TileMap->GetTileSize().y;

			m_Camera->SetCameraLimit(StartPos, EndPos);
		}
	}

	if (m_Sprite && m_Move)
	{
		if (!CInput::GetInst()->IsKeyDown("MoveUp") && !CInput::GetInst()->IsKeyDown("MoveDown") &&
			!CInput::GetInst()->IsKeyDown("MoveLeft") && !CInput::GetInst()->IsKeyDown("MoveRight"))
			m_Move = false;
	}
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	if (m_HP < 1.f)
		m_HP = 1.f;
}

CPlayer2D* CPlayer2D::Clone()
{
	return DBG_NEW CPlayer2D(*this);
}

void CPlayer2D::Hit(float DeltaTime)
{
	if (m_Hit)
	{
		UpdateBlink(DeltaTime);

		m_NoHitTimer += DeltaTime;

		if (m_NoHitTimer >= m_NoHitTimerMax)
		{
			m_NoHitTimer = 0.f;
			m_BlinkTimer = 0.f;

			m_Sprite->SetRender(true);

			if (m_CurWeapon)
				m_CurWeapon->SetRender(true);

			m_Invincibility = false;

			m_Hit = false;
		}
	}
}

void CPlayer2D::OnCollisionBegin(const CollisionResult& result)
{
	if (m_Invincibility)
		return;

	std::string	DestName = result.Dest->GetCollisionProfile()->Name;

	if (DestName == "Monster" || DestName == "MonsterAttack")
	{
		CCharacter::OnCollisionBegin(result);

		m_Invincibility = true;

		m_Scene->GetResource()->SoundPlay("Hit");
	}
}

void CPlayer2D::MoveUp(float DeltaTime)
{
	if (!m_EnableInput || !CEngine::GetInst()->IsFocusClient())
		return;

	m_Move = true;

	if (m_WeaponSlot == Weapon_Slot::None)
		SetDir(Character_Direction::Up);

	SetMoveDir(Character_Direction::Up);

	Vector3	Result = m_Sprite->GetWorldAxis(AXIS_Y) * m_MoveSpeed * DeltaTime;
	//Result.Ceil();

	if (IsWallTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::MoveDown(float DeltaTime)
{
	if (!m_EnableInput || !CEngine::GetInst()->IsFocusClient())
		return;

	m_Move = true;

	if (m_WeaponSlot == Weapon_Slot::None)
		SetDir(Character_Direction::Down);

	SetMoveDir(Character_Direction::Down);

	Vector3	Result = m_Sprite->GetWorldAxis(AXIS_Y) * -m_MoveSpeed * DeltaTime;
	//Result.Ceil();

	if (IsWallTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::MoveLeft(float DeltaTime)
{
	if (!m_EnableInput || !CEngine::GetInst()->IsFocusClient())
		return;

	m_Move = true;

	if (m_WeaponSlot == Weapon_Slot::None)
		SetDir(Character_Direction::Left);

	SetMoveDir(Character_Direction::Left);

	Vector3	Result = m_Sprite->GetWorldAxis(AXIS_X) * -m_MoveSpeed * DeltaTime;
	//Result.Ceil();

	if (IsWallTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::MoveRight(float DeltaTime)
{
	if (!m_EnableInput || !CEngine::GetInst()->IsFocusClient())
		return;

	m_Move = true;

	if (m_WeaponSlot == Weapon_Slot::None)
		SetDir(Character_Direction::Right);

	SetMoveDir(Character_Direction::Right);

	Vector3	Result = m_Sprite->GetWorldAxis(AXIS_X) * m_MoveSpeed * DeltaTime;
	//Result.Ceil();

	if (IsWallTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::DodgeStart(float DeltaTime)
{
	if (!m_EnableInput || !CEngine::GetInst()->IsFocusClient())
		return;

	m_Move = true;
	
	m_EnableInput = false;

	m_DodgeCoolDown = true;

	m_Invincibility = true;

	m_Scene->GetResource()->SoundPlay("Dodge");
}

void CPlayer2D::Dodge(float DeltaTime)
{
	Vector3	Result;

	if (IsMoveDir(Character_Direction::Up))
		Result = m_Sprite->GetWorldAxis(AXIS_Y) * m_DodgeSpeed * DeltaTime;

	else if (IsMoveDir(Character_Direction::Down))
		Result = m_Sprite->GetWorldAxis(AXIS_Y) * -m_DodgeSpeed * DeltaTime;

	if (IsMoveDir(Character_Direction::Left))
		Result += (m_Sprite->GetWorldAxis(AXIS_X) * -m_DodgeSpeed * DeltaTime);

	else if (IsMoveDir(Character_Direction::Right))
		Result += (m_Sprite->GetWorldAxis(AXIS_X) * m_DodgeSpeed * DeltaTime);

	//Result.Ceil();

	if (IsWallTile(Result))
		return;

	m_Sprite->AddRelativePos(Result);
}

void CPlayer2D::NoWeapon(float DeltaTime)
{
	m_WeaponSlot = Weapon_Slot::None;

	m_PierceBullet = false;
}

void CPlayer2D::Weapon1(float DeltaTime)
{
	m_WeaponSlot = Weapon_Slot::Pistol;
	m_AttackDelayMax = 0.6f;
	m_Damage = 3.f;

	m_PierceBullet = false;
}

void CPlayer2D::Weapon2(float DeltaTime)
{
	if (!m_HasRifle)
		return;

	m_WeaponSlot = Weapon_Slot::Rifle;
	m_AttackDelayMax = 0.1f;
	m_Damage = 3.f;

	m_PierceBullet = false;
}

void CPlayer2D::Weapon3(float DeltaTime)
{
	if (!m_HasSniper)
		return;

	m_WeaponSlot = Weapon_Slot::Sniper;
	m_AttackDelayMax = 1.3f;
	m_Damage = 20.f;

	m_PierceBullet = true;
}

void CPlayer2D::HideAllWeapon()
{
	m_Weapon1->SetRender(false);
	m_Weapon1L->SetRender(false);
	m_Weapon2->SetRender(false);
	m_Weapon2L->SetRender(false);
	m_Weapon3->SetRender(false);
	m_Weapon3L->SetRender(false);

	m_CurWeapon = nullptr;
}

void CPlayer2D::Attack(float DeltaTime)
{
	if (!m_EnableInput || m_AttackCoolDown || m_WeaponSlot == Weapon_Slot::None || !m_CurWeapon || !CEngine::GetInst()->IsFocusClient())
		return;

	Vector3	WorldPos = GetWorldPos();

	m_AttackCoolDown = true;

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	Bullet->SetOwner(this);
	Bullet->SetBulletDir(Vector3::ConvertDir(m_MouseAngle));
	Bullet->SetWorldPos(GetWorldPos());
	Bullet->SetWorldRotation(m_CurWeapon->GetWorldRot());
	Bullet->SetCharacterType(Character_Type::Player);
	Bullet->SetWeaponSlot(m_WeaponSlot);
	Bullet->Pierce(m_PierceBullet);
}

void CPlayer2D::UpdatePlayerLife(float DeltaTime)
{
	if (m_HP != m_PrevHP)
		m_PlayerUI->SetHPPercent(m_HP / m_HPMax);
}

void CPlayer2D::UpdateAttackCoolDown(float DeltaTime)
{
	if (m_AttackCoolDown)
	{
		m_AttackDelay += DeltaTime;

		if (m_AttackDelay >= m_AttackDelayMax)
		{
			m_AttackDelay = 0.f;
			m_AttackCoolDown = false;
		}
	}
}

void CPlayer2D::UpdateDodgeCoolDown(float DeltaTime)
{
	if (m_DodgeCoolDown)
	{
		m_DodgeTimer += DeltaTime;

		if (m_DodgeTimer >= m_DodgeTimerMax)
		{
			m_DodgeTimer = 0.f;
			m_DodgeCoolDown = false;

			m_EnableInput = true;

			m_Move = false;

			if (!m_Hit)
				m_Invincibility = false;
		}
	}
}

void CPlayer2D::UpdateMouseAngle()
{
	Vector2	CamLeftButtom = m_Scene->GetCameraManager()->GetCurrentCamera()->GetLeftBottom();
	Vector3	PlayerPos = GetWorldPos() - Vector3(CamLeftButtom.x, CamLeftButtom.y, 0.f);

	Vector3	MousePos = CInput::GetInst()->GetMousePos3D();

	// 마우스를 향해서 앵글 변경
	m_MouseAngle = atan2(MousePos.y - PlayerPos.y, MousePos.x - PlayerPos.x) * (180.f / PI);
}

void CPlayer2D::UpdateMousePos()
{
	if (m_WeaponSlot == Weapon_Slot::None)
		return;

	DeleteDir(Character_Direction::All);

	if (105.f >= m_MouseAngle && m_MouseAngle > 75.f)
		SetDir(Character_Direction::Up);

	else if (-105.f <= m_MouseAngle && m_MouseAngle < -75.f)
		SetDir(Character_Direction::Down);

	else if (180.f >= m_MouseAngle && m_MouseAngle > 105.f)
		SetDir(Character_Direction::UpLeft);

	else if (-180.f <= m_MouseAngle && m_MouseAngle < -105.f)
		SetDir(Character_Direction::DownLeft);

	else if ((75.f >= m_MouseAngle && m_MouseAngle > 0.f) ||
			(75.f > m_MouseAngle && m_MouseAngle >= 0.f))
		SetDir(Character_Direction::UpRight);

	else if ((-75.f <= m_MouseAngle && m_MouseAngle < 0.f) ||
		(-75.f < m_MouseAngle && m_MouseAngle <= 0.f))
		SetDir(Character_Direction::DownRight);
}

void CPlayer2D::UpdateGun()
{
	HideAllWeapon();

	if (!m_EnableInput || !CEngine::GetInst()->IsFocusClient())
		return;

	switch (m_WeaponSlot)
	{
	case Weapon_Slot::Pistol:
		
		if ((180.999f >= m_MouseAngle && m_MouseAngle > 90.999f) ||
			(-180.999f <= m_MouseAngle && m_MouseAngle < -90.999f))
		{
			m_Weapon1L->SetRender(true);
			m_CurWeapon = m_Weapon1L;
		}
		else
		{
			m_Weapon1->SetRender(true);
			m_CurWeapon = m_Weapon1;
		}
		
		break;
	case Weapon_Slot::Rifle:
		if ((180.999f >= m_MouseAngle && m_MouseAngle > 90.999f) ||
			(-180.999f <= m_MouseAngle && m_MouseAngle < -90.999f))
		{
			m_Weapon2L->SetRender(true);
			m_CurWeapon = m_Weapon2L;
		}
		else
		{
			m_Weapon2->SetRender(true);
			m_CurWeapon = m_Weapon2;
		}
		break;
	case Weapon_Slot::Sniper:
		if ((180.999f >= m_MouseAngle && m_MouseAngle > 90.999f) ||
			(-180.999f <= m_MouseAngle && m_MouseAngle < -90.999f))
		{
			m_Weapon3L->SetRender(true);
			m_CurWeapon = m_Weapon3L;
		}
		else
		{
			m_Weapon3->SetRender(true);
			m_CurWeapon = m_Weapon3;
		}
		break;
	}

	if (m_CurWeapon)
	{
		UpdateGunDir(m_CurWeapon);

		if (!m_Hit && !m_CurWeapon->IsRender())
			m_CurWeapon->SetRender(true);
	}
}

void CPlayer2D::UpdateGunDir(CSpriteComponent* Weapon)
{
	Weapon->SetRelativeRotationZ(m_MouseAngle);

	if (IsDir(Character_Direction::Up))
	{
		Weapon->SetLayerName("PrevDefault");
		return;
	}

	Weapon->SetLayerName("Default");
}

void CPlayer2D::UpdateAnimDir()
{
	if (m_EnableInput)
	{
		if (m_WeaponSlot == Weapon_Slot::None)
		{
			if (CInput::GetInst()->IsKeyDown("MoveUp") || CInput::GetInst()->IsKeyDown("MoveDown"))
			{
				if (!CInput::GetInst()->IsKeyDown("MoveLeft") && IsDir(Character_Direction::Left))
					DeleteDir(Character_Direction::Left);

				if (!CInput::GetInst()->IsKeyDown("MoveRight") && IsDir(Character_Direction::Right))
					DeleteDir(Character_Direction::Right);
			}

			else if (CInput::GetInst()->IsKeyDown("MoveLeft") || CInput::GetInst()->IsKeyDown("MoveRight"))
			{
				if (!CInput::GetInst()->IsKeyDown("MoveUp") && IsDir(Character_Direction::Up))
					DeleteDir(Character_Direction::Up);

				if (!CInput::GetInst()->IsKeyDown("MoveDown") && IsDir(Character_Direction::Down))
					DeleteDir(Character_Direction::Down);
			}
		}

		if (CInput::GetInst()->IsKeyDown("MoveUp") || CInput::GetInst()->IsKeyDown("MoveDown"))
		{
			if (!CInput::GetInst()->IsKeyDown("MoveLeft") && IsMoveDir(Character_Direction::Left))
				DeleteMoveDir(Character_Direction::Left);

			if (!CInput::GetInst()->IsKeyDown("MoveRight") && IsMoveDir(Character_Direction::Right))
				DeleteMoveDir(Character_Direction::Right);
		}

		else if (CInput::GetInst()->IsKeyDown("MoveLeft") || CInput::GetInst()->IsKeyDown("MoveRight"))
		{
			if (!CInput::GetInst()->IsKeyDown("MoveUp") && IsMoveDir(Character_Direction::Up))
				DeleteMoveDir(Character_Direction::Up);

			if (!CInput::GetInst()->IsKeyDown("MoveDown") && IsMoveDir(Character_Direction::Down))
				DeleteMoveDir(Character_Direction::Down);
		}
	}

	ChangeAnimIdle();
	ChangeAnimWalk();
	ChangeAnimDodge();
}

void CPlayer2D::UpdateBlink(float DeltaTime)
{
	m_BlinkTimer += DeltaTime;

	m_Sprite->SetRender(m_Invisible);

	if (m_CurWeapon)
		m_CurWeapon->SetRender(m_Invisible);

	if (m_BlinkTimer >= m_BlinkTimerMax)
	{
		m_BlinkTimer = 0.f;

		m_Invisible = !m_Invisible;
	}
}

void CPlayer2D::ChangeAnimIdle()
{
	if (!m_Move && !m_DodgeCoolDown)
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
	if (m_Move && !m_DodgeCoolDown)
	{
		if (IsDir(Character_Direction::Down) && !IsDir(Character_Direction::Left) && !IsDir(Character_Direction::Right))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Walk_D");
			return;
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

void CPlayer2D::ChangeAnimDodge()
{
	if (m_DodgeCoolDown)
	{
		if (IsMoveDir(Character_Direction::Down) && !IsMoveDir(Character_Direction::Left) && !IsMoveDir(Character_Direction::Right))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Dodge_D");
			return;
		}

		else if (IsMoveDir(Character_Direction::Up))
		{
			if (IsMoveDir(Character_Direction::Left))
			{
				m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Dodge_UL");
				return;
			}

			else if (IsMoveDir(Character_Direction::Right))
			{
				m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Dodge_UR");
				return;
			}

			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Dodge_U");
		}

		else if (IsMoveDir(Character_Direction::Left))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Dodge_DL");
			return;
		}

		else if (IsMoveDir(Character_Direction::Right))
		{
			m_Sprite->GetAnimationInstance()->ChangeAnimation("Player_Dodge_DR");
			return;
		}
	}
}
