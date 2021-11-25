
#include "Costume.h"

CCostume::CCostume()	:
	m_Player(nullptr)
{
}

CCostume::CCostume(const CCostume& obj)	:
	CPlayer2D(obj)
{
	m_Player = obj.m_Player;
}

CCostume::~CCostume()
{
}

void CCostume::Start()
{
	CGameObject::Start();

	if (m_Player)
	{
		m_PlayerSprite = dynamic_cast<CSpriteComponent*>(m_Player->FindComponent("PlayerSprite"));

		m_PlayerSprite->AddChild(m_CostumeComponentLeft);
		m_PlayerSprite->AddChild(m_CostumeComponentRight);

		m_CostumeComponentLeft->SetRelativePos(Vector3(-30.f, -50.f, 0.f));
		m_CostumeComponentRight->SetRelativePos(Vector3(30.f, -50.f, 0.f));

		m_CostumeComponentLeft->SetRelativeRotationZ(-30.f);
		m_CostumeComponentRight->SetRelativeRotationZ(30.f);
	}
}

bool CCostume::Init()
{
	CGameObject::Init();

	m_CostumeComponentLeft = CreateComponent<CSpriteComponent>("CostumeLeft");
	m_CostumeComponentRight = CreateComponent<CSpriteComponent>("CostumeRight");

	m_CostumeComponentLeft->SetRelativeScale(10.f, 50.f, 0.f);
	m_CostumeComponentRight->SetRelativeScale(10.f, 50.f, 0.f);

	m_CostumeComponentLeft->SetInheritScale(false);
	m_CostumeComponentRight->SetInheritScale(false);

	m_CostumeComponentLeft->SetPivot(0.5f, 1.f, 0.f);
	m_CostumeComponentRight->SetPivot(0.5f, 1.f, 0.f);

	m_CostumeComponentLeft->SetInheritRotZ(true);
	m_CostumeComponentRight->SetInheritRotZ(true);

	return true;
}

void CCostume::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

CCostume* CCostume::Clone()
{
	return new CCostume(*this);
}
