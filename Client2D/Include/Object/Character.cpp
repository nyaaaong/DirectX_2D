
#include "Character.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Animation/AnimationSequence2DInstance.h"

CCharacter::CCharacter() :
	m_HP(50.f),
	m_HitEffectTime(0.f),
	m_HitEffectTimeMax(0.3f),
	m_IsDied(false),
	m_IsPaperBurn(false),
	m_Hit(false),
	m_IsPlayedHitSound(false),
	m_Damage(3.f),
	m_Type(Character_Type::Max)
{
	SetTypeID<CCharacter>();
}

CCharacter::CCharacter(const CCharacter& obj) :
	CGameObject(obj)
{
	SetTypeID<CCharacter>();

	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_PaperBurn = (CPaperBurnComponent*)FindComponent("PaperBurn");

	m_HP = obj.m_HP;
	m_IsDied = false;
	m_IsPaperBurn = false;
	m_Hit = false;
	m_IsPlayedHitSound = false;
	m_Type = obj.m_Type;

	m_Damage = obj.m_Damage;
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

	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Hit(DeltaTime);
	Dead(DeltaTime);
}

void CCharacter::OnCollisionBegin(const CollisionResult& result)
{
	m_Hit = true;
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

void CCharacter::Destroy()
{
	CGameObject::Destroy();
}