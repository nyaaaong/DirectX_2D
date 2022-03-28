
#include "BulletKin.h"
#include "Bullet.h"
#include "BulletKinAnim.h"
#include "Scene/Scene.h"

CBulletKin::CBulletKin()
{
	SetTypeID<CBulletKin>();
}

CBulletKin::CBulletKin(const CBulletKin& obj)	:
	CMonster(obj)
{
	SetTypeID<CBulletKin>();

	m_Sprite->CreateAnimationInstance<CBulletKinAnim>();

	m_Weapon = (CSpriteComponent*)FindComponent("WeaponSprite");
	m_WeaponL = (CSpriteComponent*)FindComponent("WeaponLSprite");

	m_CurWeapon = nullptr;
}

CBulletKin::~CBulletKin()
{
}

void CBulletKin::Start()
{
	CMonster::Start();
}

bool CBulletKin::Init()
{
	if (!CMonster::Init())
		return false;

	m_Sprite->CreateAnimationInstance<CBulletKinAnim>();

	m_Body->SetExtent(18.f, 33.f);

	m_Weapon = CreateComponent<CSpriteComponent>("WeaponSprite");
	m_WeaponL = CreateComponent<CSpriteComponent>("WeaponLSprite");

	m_Weapon->SetRelativeScale(51.f, 39.f, 1.f);
	m_WeaponL->SetRelativeScale(51.f, 39.f, 1.f);

	m_Weapon->SetRelativePos(10.f, -26.f, 0.f);
	m_WeaponL->SetRelativePos(-10.f, 0.f, 0.f);

	m_Weapon->SetPivotX(-1.f);
	m_WeaponL->SetPivotX(-1.f);

	m_Sprite->AddChild(m_Weapon);
	m_Sprite->AddChild(m_WeaponL);

	m_Weapon->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "Weapon", TEXT("Weapon/Monster/Weapon1.png"));
	m_WeaponL->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "WeaponL", TEXT("Weapon/Monster/Weapon1L.png"));

	HideAllWeapon();

	return true;
}

void CBulletKin::Update(float DeltaTime)
{
	CMonster::Update(DeltaTime);
}

CBulletKin* CBulletKin::Clone()
{
	return DBG_NEW CBulletKin(*this);
}

void CBulletKin::PlaySoundDie()
{
	int i = rand() % 4 + 1;
	char Name[256] = {};

	sprintf_s(Name, "BulletKin_Die%d", i);

	m_Scene->GetResource()->SoundPlay(Name);
}

void CBulletKin::Attack(float DeltaTime)
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
	Bullet->SetBulletType(Bullet_Type::Pistol);
}
