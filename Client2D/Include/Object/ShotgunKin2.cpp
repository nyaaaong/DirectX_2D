
#include "ShotgunKin2.h"
#include "ShotgunKin2Anim.h"
#include "Bullet.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

CShotgunKin2::CShotgunKin2()
{
	SetTypeID<CShotgunKin2>();
}

CShotgunKin2::CShotgunKin2(const CShotgunKin2& obj) :
	CMonster(obj)
{
	SetTypeID<CShotgunKin2>();

	m_Sprite->CreateAnimationInstance<CShotgunKin2Anim>();

	m_Weapon = (CSpriteComponent*)FindComponent("WeaponSprite");
	m_WeaponL = (CSpriteComponent*)FindComponent("WeaponLSprite");

	m_CurWeapon = nullptr;
}

CShotgunKin2::~CShotgunKin2()
{
}

void CShotgunKin2::Start()
{
	CMonster::Start();

	CSharedPtr<CSceneMode> SceneMode = CSceneManager::GetInst()->GetSceneMode();

	CharacterInfo	Info = SceneMode->GetPlayerInfo();
	m_HP = Info.HP;
	m_HPMax = Info.HP;
	m_MoveSpeed = Info.MoveSpeed;
	m_Damage = Info.Damage;
}

bool CShotgunKin2::Init()
{
	if (!CMonster::Init())
		return false;

	m_Sprite->CreateAnimationInstance<CShotgunKin2Anim>();

	m_Body->SetExtent(18.f, 33.f);

	m_Weapon = CreateComponent<CSpriteComponent>("WeaponSprite");
	m_WeaponL = CreateComponent<CSpriteComponent>("WeaponLSprite");

	m_Weapon->SetRelativeScale(78.f, 21.f, 1.f);
	m_WeaponL->SetRelativeScale(78.f, 21.f, 1.f);

	m_Weapon->SetRelativePos(10.f, -26.f, 0.f);
	m_WeaponL->SetRelativePos(-10.f, 0.f, 0.f);

	m_Weapon->SetPivotX(-1.f);
	m_WeaponL->SetPivotX(-1.f);

	m_Sprite->AddChild(m_Weapon);
	m_Sprite->AddChild(m_WeaponL);

	m_Weapon->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Weapon", TEXT("Weapon/Monster/Weapon3.png"));
	m_WeaponL->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "WeaponL", TEXT("Weapon/Monster/Weapon3L.png"));

	HideAllWeapon();

	m_AttackTimerMax = 0.7f;

	return true;
}

void CShotgunKin2::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);
}

CShotgunKin2* CShotgunKin2::Clone()
{
	return DBG_NEW CShotgunKin2(*this);
}

void CShotgunKin2::PlaySoundDie()
{
	int i = rand() % 4 + 1;
	char Name[256] = {};

	sprintf_s(Name, "BulletKin_Die%d", i);

	m_Scene->GetResource()->SoundPlay(Name);
}

void CShotgunKin2::Attack(float DeltaTime)
{
	if (!m_InsideLimit || m_AttackCoolDown || m_IsDied)
		return;

	m_AttackCoolDown = true;

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");

	Bullet->SetOwner(this);
	Bullet->SetBulletDir(m_PlayerDir);
	Bullet->SetWorldPos(GetWorldPos());
	Bullet->SetWorldRotation(m_CurWeapon->GetWorldRot());
	Bullet->SetCollisionProfile("MonsterAttack");
	Bullet->SetCharacterType(Character_Type::Monster);
	Bullet->SetBulletType(Bullet_Type::Shotgun);
}