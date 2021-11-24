
#include "Player2D.h"
#include "Bullet.h"
#include "Scene/Scene.h"

CPlayer2D::CPlayer2D()
{
}

CPlayer2D::CPlayer2D(const CPlayer2D& obj)	:
	CGameObject(obj)
{
}

CPlayer2D::~CPlayer2D()
{
}

bool CPlayer2D::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("PlayerSprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(100.f, 100.f, 1.f);
	m_Sprite->SetRelativePos(100.f, 50.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

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

	static bool Fire = false;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Fire = true;
	}

	else if (Fire)
	{
		Fire = false;

		CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

		Bullet->SetWorldPos(GetWorldPos() + GetWorldAxis(AXIS_Y) * 75.f);
		Bullet->SetWorldRotation(GetWorldRot());
	}
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPlayer2D* CPlayer2D::Clone()
{
	return new CPlayer2D(*this);
}
