
#include "Bandana.h"
#include "BandanaAnim.h"
#include "Bullet.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

CBandana::CBandana()	:
	m_BurstTimer(0.f),
	m_BurstTimerMax(1.f),
	m_BurstCoolDownTimer(0.f),
	m_BurstCoolDownTimerMax(1.5f),
	m_BurstCooldown(false)
{
	SetTypeID<CBandana>();
}

CBandana::CBandana(const CBandana& obj) :
	CMonster(obj)
{
	SetTypeID<CBandana>();

	m_Sprite->CreateAnimationInstance<CBandanaAnim>();

	m_Weapon = (CSpriteComponent*)FindComponent("M_Weapon2Sprite");
	m_WeaponL = (CSpriteComponent*)FindComponent("M_Weapon2LSprite");

	m_CurWeapon = nullptr;
}

CBandana::~CBandana()
{
}

void CBandana::Start()
{
	CMonster::Start();

	CSharedPtr<CSceneMode> SceneMode = CSceneManager::GetInst()->GetSceneMode();

	MonsterInfo	Info = SceneMode->GetMonsterInfo(Object_Type::M_Bandana);
	m_PrevHP = Info.HP;
	m_HP = Info.HP;
	m_HPMax = Info.HP;
	m_MoveSpeed = Info.MoveSpeed;
	m_Damage = Info.Damage;
	m_AttackDelayMax = Info.AttackDelayMax;
}

bool CBandana::Init()
{
	if (!CMonster::Init())
		return false;

	m_Sprite->CreateAnimationInstance<CBandanaAnim>();

	m_Body->SetExtent(18.f, 33.f);

	m_Weapon = CreateComponent<CSpriteComponent>("M_Weapon2Sprite");
	m_WeaponL = CreateComponent<CSpriteComponent>("M_Weapon2LSprite");

	m_Weapon->SetRelativeScale(78.f, 21.f, 1.f);
	m_WeaponL->SetRelativeScale(78.f, 21.f, 1.f);

	m_Weapon->SetRelativePos(10.f, -26.f, 0.f);
	m_WeaponL->SetRelativePos(-10.f, 0.f, 0.f);

	m_Weapon->SetPivotX(-1.f);
	m_WeaponL->SetPivotX(-1.f);

	m_Sprite->AddChild(m_Weapon);
	m_Sprite->AddChild(m_WeaponL);

	m_Weapon->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "M_Weapon2", TEXT("Weapon/Monster/Weapon2.png"));
	m_WeaponL->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "M_Weapon2L", TEXT("Weapon/Monster/Weapon2L.png"));

	HideAllWeapon();

	return true;
}

void CBandana::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);
}

CBandana* CBandana::Clone()
{
	return DBG_NEW CBandana(*this);
}

void CBandana::Calc(float DeltaTime)
{
	CMonster::Calc(DeltaTime);

	if (m_CanUpdate)
	{
		m_BurstTimer += DeltaTime;

		if (m_BurstTimer >= m_BurstTimerMax)
		{
			m_BurstTimer = 0.f;
			m_BurstCooldown = true;
			return;
		}

		if (m_BurstCooldown)
		{
			m_BurstCoolDownTimer += DeltaTime;

			if (m_BurstCoolDownTimer >= m_BurstCoolDownTimerMax)
			{
				m_BurstCoolDownTimer = 0.f;
				m_BurstCooldown = false;
			}
		}
	}
}

void CBandana::PlaySoundDie()
{
	int i = rand() % 4 + 1;
	char Name[256] = {};

	sprintf_s(Name, "BulletKin_Die%d", i);

	m_Scene->GetResource()->SoundPlay(Name);
}

void CBandana::Attack(float DeltaTime)
{
	if (m_BurstCooldown)
		return;

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	Bullet->SetOwner(this);
	Bullet->SetBulletDir(m_PlayerDir);
	Bullet->SetWorldPos(GetWorldPos());
	Bullet->SetWorldRotation(m_CurWeapon->GetWorldRot());
	Bullet->SetCharacterType(Character_Type::Monster);
	Bullet->SetBulletType(Bullet_Type::Rifle);
}

void CBandana::ChangePatternStartFunc(float DeltaTime)
{
	m_BurstCooldown = false;
	m_BurstCoolDownTimer = 0.f;
}
