
#include "Player2D.h"
#include "Bullet.h"
#include "BulletTornaido.h"
#include "Input.h"
#include "PlayerAnimation2D.h"
#include "BulletCamera.h"
#include "Scene/Scene.h"
#include "Resource/Material/Material.h"

CPlayer2D::CPlayer2D()	:
	m_EnableInput(true),
	m_Dodge(false)
{
	SetTypeID<CPlayer2D>();
	m_SolW = false;
	m_WDistance = 0.f;
	m_Opacity = 1.f;
}

CPlayer2D::CPlayer2D(const CPlayer2D& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("PlayerSprite");
	m_ChildLeftSprite = (CSpriteComponent*)FindComponent("PlayerChildLeftSprite");
	m_ChildRightSprite = (CSpriteComponent*)FindComponent("PlayerChildRightSprite");
	m_ChildLeftMuzzle = (CSceneComponent*)FindComponent("LeftMuzzle");
	m_ChildRightMuzzle = (CSceneComponent*)FindComponent("RightMuzzle");
	m_ChildRoot = (CSceneComponent*)FindComponent("PlayerChildRoot");
	m_Muzzle = (CSceneComponent*)FindComponent("Muzzle");

	m_Child1Sprite = (CSpriteComponent*)FindComponent("PlayerChild1Sprite");
	m_Child2Sprite = (CSpriteComponent*)FindComponent("PlayerChild2Sprite");
	m_Child3Sprite = (CSpriteComponent*)FindComponent("PlayerChild3Sprite");
	m_Child4Sprite = (CSpriteComponent*)FindComponent("PlayerChild4Sprite");

	m_Body = (CColliderBox2D*)FindComponent("Body");

	m_Opacity = obj.m_Opacity;
	m_Dodge = false;
}

CPlayer2D::~CPlayer2D()
{
}

bool CPlayer2D::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("PlayerSprite");
	m_ChildLeftSprite = CreateComponent<CSpriteComponent>("PlayerChildLeftSprite");
	m_ChildRightSprite = CreateComponent<CSpriteComponent>("PlayerChildRightSprite");
	m_ChildRoot = CreateComponent<CSceneComponent>("PlayerChildRoot");
	m_Muzzle = CreateComponent<CSceneComponent>("Muzzle");

	m_Body = CreateComponent<CColliderBox2D>("Body");

	m_ChildLeftMuzzle = CreateComponent<CSceneComponent>("LeftMuzzle");
	m_ChildRightMuzzle = CreateComponent<CSceneComponent>("RightMuzzle");

	m_Child1Sprite = CreateComponent<CSpriteComponent>("PlayerChild1Sprite");
	m_Child2Sprite = CreateComponent<CSpriteComponent>("PlayerChild2Sprite");
	m_Child3Sprite = CreateComponent<CSpriteComponent>("PlayerChild3Sprite");
	m_Child4Sprite = CreateComponent<CSpriteComponent>("PlayerChild4Sprite");

	m_Camera = CreateComponent<CCameraComponent>("Camera");

	SetRootComponent(m_Sprite);

	m_Body->SetCollisionProfile("Player");

	m_Camera->OnViewportCenter();
	//m_Camera->SetViewportRatio(0.7f, 0.7f);

	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Camera);
	m_Sprite->AddChild(m_ChildLeftSprite);
	m_Sprite->AddChild(m_ChildRightSprite);
	m_Sprite->AddChild(m_Muzzle);
	m_Sprite->AddChild(m_ChildRoot);

	m_Sprite->SetTransparency(true);

	m_Sprite->CreateAnimationInstance<CPlayerAnimation2D>();

	m_ChildLeftSprite->AddChild(m_ChildLeftMuzzle);
	m_ChildRightSprite->AddChild(m_ChildRightMuzzle);


	m_ChildLeftSprite->SetTexture(0, 0, (int)ConstantBuffer_Shader_Type::Pixel, "Teemo", TEXT("Teemo.jpg"));
	m_ChildRightSprite->SetTexture(0, 0, (int)ConstantBuffer_Shader_Type::Pixel, "Teemo", TEXT("Teemo.jpg"));

	m_ChildLeftSprite->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	m_ChildRightSprite->SetBaseColor(1.f, 0.f, 0.f, 1.f);

	m_ChildRoot->AddChild(m_Child1Sprite);
	m_ChildRoot->AddChild(m_Child2Sprite);
	m_ChildRoot->AddChild(m_Child3Sprite);
	m_ChildRoot->AddChild(m_Child4Sprite);

	m_Muzzle->SetRelativePos(0.f, 150.f, 0.f);
	m_Muzzle->SetInheritRotZ(true);

	m_ChildLeftMuzzle->SetRelativePos(0.f, 100.f, 0.f);
	m_ChildLeftMuzzle->SetInheritRotZ(true);

	m_ChildRightMuzzle->SetRelativePos(0.f, 100.f, 0.f);
	m_ChildRightMuzzle->SetInheritRotZ(true);

	m_Sprite->SetRelativeScale(42.f, 66.f, 1.f);
	m_Sprite->SetRelativePos(100.f, 50.f, 0.f);
	m_Sprite->SetPivot(0.5f, 1.f, 0.f);

	m_ChildRightSprite->SetRelativeScale(50.f, 50.f, 1.f);
	m_ChildRightSprite->SetInheritScale(false);
	m_ChildRightSprite->SetRelativePos(100.f, 0.f, 0.f);
	m_ChildRightSprite->SetPivot(0.5f, 0.5f, 0.f);
	m_ChildRightSprite->SetInheritRotZ(true);

	m_ChildLeftSprite->SetRelativeScale(50.f, 50.f, 1.f);
	m_ChildLeftSprite->SetInheritScale(false);
	m_ChildLeftSprite->SetRelativePos(-100.f, 0.f, 0.f);
	m_ChildLeftSprite->SetPivot(0.5f, 0.5f, 0.f);
	m_ChildLeftSprite->SetInheritRotZ(true);

	m_Child1Sprite->SetRelativeScale(25.f, 25.f, 1.f);
	m_Child1Sprite->SetInheritScale(false);
	m_Child1Sprite->SetRelativePos(200.f, 0.f, 0.f);
	m_Child1Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Child1Sprite->SetInheritRotZ(true);

	m_Child2Sprite->SetRelativeScale(25.f, 25.f, 1.f);
	m_Child2Sprite->SetInheritScale(false);
	m_Child2Sprite->SetRelativePos(-200.f, 0.f, 0.f);
	m_Child2Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Child2Sprite->SetInheritRotZ(true);

	m_Child3Sprite->SetRelativeScale(25.f, 25.f, 1.f);
	m_Child3Sprite->SetInheritScale(false);
	m_Child3Sprite->SetRelativePos(0.f, 200.f, 0.f);
	m_Child3Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Child3Sprite->SetInheritRotZ(true);

	m_Child4Sprite->SetRelativeScale(25.f, 25.f, 1.f);
	m_Child4Sprite->SetInheritScale(false);
	m_Child4Sprite->SetRelativePos(0.f, -200.f, 0.f);
	m_Child4Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Child4Sprite->SetInheritRotZ(true);

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
	CInput::GetInst()->SetKeyCallback<CPlayer2D>("Skill1", KeyState_Down, this, &CPlayer2D::Skill1);

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	static bool Fire2 = false;

	static bool	Hide = false;

	if (GetAsyncKeyState('2') & 0x8000)
	{
		Fire2 = true;
	}

	else if (Fire2)
	{
		Fire2 = false;

		CBulletTornaido* Bullet = m_Scene->CreateGameObject<CBulletTornaido>("Bullet");

		//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
		Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());

		Hide = true;
	}

	m_ChildRoot->AddRelativeRotation(0.f, 0.f, 180.f * DeltaTime);

	if (Hide)
	{
		m_Opacity -= DeltaTime / 5.f;

		if (m_Opacity < 0.f)
			m_Opacity = 0.f;

		m_Sprite->SetOpacity(m_Opacity);
	}

	Action(DeltaTime);
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

	m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_Y) * 300.f * DeltaTime);
}

void CPlayer2D::MoveDown(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_Y) * -300.f * DeltaTime);
}

void CPlayer2D::MoveLeft(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_X) * -300.f * DeltaTime);
}

void CPlayer2D::MoveRight(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_X) * 300.f * DeltaTime);
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

	m_EnableInput = false;
	m_Dodge = true;

	m_Sprite->GetAnimationInstance()->ChangeAnimation("PlayerDodgeD");
}

void CPlayer2D::DodgeEnd(float DeltaTime)
{
	m_EnableInput = true;

	m_Sprite->GetAnimationInstance()->ChangeAnimation("PlayerIdleD");
}

void CPlayer2D::Attack(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());

	Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldPos(m_ChildLeftMuzzle->GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());

	Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldPos(m_ChildRightMuzzle->GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());
}

void CPlayer2D::Attack1(float DeltaTime)
{
	if (!m_EnableInput)
		return;

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());

	Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot() + Vector3(0.f, 0.f, 45.f));

	Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot() + Vector3(0.f, 0.f, -45.f));
}

void CPlayer2D::test(float DeltatTime)
{
	int a = 0;
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

void CPlayer2D::Skill1(float DeltaTime)
{
	CBulletCamera* Bullet = m_Scene->CreateGameObject<CBulletCamera>("Bullet");

	//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
	Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());
}
