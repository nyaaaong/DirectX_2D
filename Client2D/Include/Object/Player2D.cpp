
#include "Player2D.h"
#include "Bullet.h"
#include "BulletTornaido.h"
#include "Scene/Scene.h"

CPlayer2D::CPlayer2D()
{
	m_SolW = false;
	m_WDistance = 0.f;
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

	m_ChildLeftMuzzle = CreateComponent<CSceneComponent>("LeftMuzzle");
	m_ChildRightMuzzle = CreateComponent<CSceneComponent>("RightMuzzle");

	m_Child1Sprite = CreateComponent<CSpriteComponent>("PlayerChild1Sprite");
	m_Child2Sprite = CreateComponent<CSpriteComponent>("PlayerChild2Sprite");
	m_Child3Sprite = CreateComponent<CSpriteComponent>("PlayerChild3Sprite");
	m_Child4Sprite = CreateComponent<CSpriteComponent>("PlayerChild4Sprite");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_ChildLeftSprite);
	m_Sprite->AddChild(m_ChildRightSprite);
	m_Sprite->AddChild(m_Muzzle);
	m_Sprite->AddChild(m_ChildRoot);


	m_ChildLeftSprite->AddChild(m_ChildLeftMuzzle);
	m_ChildRightSprite->AddChild(m_ChildRightMuzzle);


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

	m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	m_Sprite->SetRelativePos(100.f, 50.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

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

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_Sprite->AddRelativeRotationZ(-180.f * DeltaTime);
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_Sprite->AddRelativeRotationZ(180.f * DeltaTime);
	}


	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_Y) * 300.f * DeltaTime);
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_Sprite->AddRelativePos(m_Sprite->GetWorldAxis(AXIS_Y) * 300.f * -DeltaTime);
	}

	static bool SolW = false;

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SolW = true;
		//m_ChildSprite->AddWorldPos(30.f * DeltaTime, 0.f, 0.f);
		//m_ChildSprite->AddRelativePos(30.f * DeltaTime, 0.f, 0.f);
	}

	else if (SolW)
	{
		SolW = false;
		m_SolW = true;
	}

	if (m_SolW)
	{
		float	Dist = 50.f * DeltaTime;
		m_WDistance += Dist;


		if (m_WDistance >= 100.f)
		{
			m_SolW = false;

			Dist -= (m_WDistance - 100.f);

			m_WDistance = 100.f;
		}

		m_Child1Sprite->AddRelativePos(Dist, 0.f, 0.f);
		m_Child2Sprite->AddRelativePos(-Dist, 0.f, 0.f);
		m_Child3Sprite->AddRelativePos(0.f, Dist, 0.f);
		m_Child4Sprite->AddRelativePos(0.f, -Dist, 0.f);
	}

	static bool Fire = false;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Fire = true;
	}

	else if (Fire)
	{
		Fire = false;

		CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
		Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());

		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
		Bullet->SetWorldPos(m_ChildLeftMuzzle->GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());

		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
		Bullet->SetWorldPos(m_ChildRightMuzzle->GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());
	}

	static bool Fire1 = false;

	if (GetAsyncKeyState('1') & 0x8000)
	{
		Fire1 = true;
	}

	else if (Fire1)
	{
		Fire1 = false;

		CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
		Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot());

		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
		Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot() + Vector3(0.f, 0.f, 45.f));

		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		//Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
		Bullet->SetWorldPos(m_Muzzle->GetWorldPos());
		Bullet->SetWorldRotation(GetWorldRot() + Vector3(0.f, 0.f, -45.f));
	}

	static bool Fire2 = false;

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
	}

	m_ChildRoot->AddRelativeRotation(0.f, 0.f, 180.f * DeltaTime);
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer2D* CPlayer2D::Clone()
{
	return new CPlayer2D(*this);
}
