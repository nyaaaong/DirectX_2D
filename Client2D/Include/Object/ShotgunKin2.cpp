
#include "ShotgunKin2.h"
#include "ShotgunKin2Anim.h"
#include "Bullet.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

CShotgunKin2::CShotgunKin2()	:
	m_arrAngle{}, 
	m_BulletAngle(10.f)
{
	SetTypeID<CShotgunKin2>();
}

CShotgunKin2::CShotgunKin2(const CShotgunKin2& obj) :
	CMonster(obj)
{
	SetTypeID<CShotgunKin2>();

	m_Sprite->CreateAnimationInstance<CShotgunKin2Anim>();

	m_Weapon = (CSpriteComponent*)FindComponent("M_Weapon3Sprite");
	m_WeaponL = (CSpriteComponent*)FindComponent("M_Weapon3LSprite");

	m_CurWeapon = nullptr;

	memset(m_arrAngle, 0, sizeof(float) * 4);

	m_BulletAngle = obj.m_BulletAngle;
}

CShotgunKin2::~CShotgunKin2()
{
}

void CShotgunKin2::Start()
{
	CMonster::Start();

	CSharedPtr<CSceneMode> SceneMode = CSceneManager::GetInst()->GetSceneMode();

	CharacterInfo	Info = SceneMode->GetMonsterInfo(Object_Type::ShotgunKin2);
	m_PrevHP = Info.HP;
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

	m_Weapon = CreateComponent<CSpriteComponent>("M_Weapon3Sprite");
	m_WeaponL = CreateComponent<CSpriteComponent>("M_Weapon3LSprite");

	m_Weapon->SetRelativeScale(72.f, 15.f, 1.f);
	m_WeaponL->SetRelativeScale(72.f, 15.f, 1.f);

	m_Weapon->SetRelativePos(10.f, -36.f, 0.f);
	m_WeaponL->SetRelativePos(-10.f, -10.f, 0.f);

	m_Weapon->SetPivotX(-1.f);
	m_WeaponL->SetPivotX(-1.f);

	m_Sprite->AddChild(m_Weapon);
	m_Sprite->AddChild(m_WeaponL);

	m_Weapon->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "M_Weapon3", TEXT("Weapon/Monster/Weapon3.png"));
	m_WeaponL->SetTexture(0, 0, (int)Buffer_Shader_Type::Pixel, "M_Weapon3L", TEXT("Weapon/Monster/Weapon3L.png"));

	HideAllWeapon();

	m_AttackDelayMax = 1.4f;

	m_UsePaperburn = false;

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

void CShotgunKin2::Calc(float DeltaTime)
{
	CMonster::Calc(DeltaTime);

	m_arrAngle[0] = m_PlayerAngle + m_BulletAngle;
	m_arrAngle[1] = m_arrAngle[0] + m_BulletAngle;

	m_arrAngle[2] = m_PlayerAngle - m_BulletAngle;
	m_arrAngle[3] = m_arrAngle[2] - m_BulletAngle;

	for (int i = 0; i < 4; ++i)
	{
		m_arrDir[i] = Vector3::ConvertDir(m_arrAngle[i]);
	}
}

void CShotgunKin2::Destroy()
{
	CMonster::Destroy();
}

void CShotgunKin2::DestroyBefore()
{
	CMonster::DestroyBefore();

	for (int i = 0; i < 8; ++i)
	{
		CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
		Bullet->SetOwner(this);
		Bullet->SetBulletDir(Vector3::ConvertDir(i * 45.f));
		Bullet->SetWorldPos(GetWorldPos());
		Bullet->SetCollisionProfile("MonsterAttack");
		Bullet->SetCharacterType(Character_Type::Monster);
		Bullet->SetBulletType(Bullet_Type::Pistol);
		Bullet->SetBulletSpeed(500.f);
	}

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
	m_Scene->GetResource()->SoundPlay("Shotgun");

	CBullet* Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
	Bullet->SetOwner(this);
	Bullet->SetBulletDir(m_PlayerDir);
	Bullet->SetWorldPos(GetWorldPos());
	Bullet->SetWorldRotation(m_CurWeapon->GetWorldRot());
	Bullet->SetCollisionProfile("MonsterAttack");
	Bullet->SetCharacterType(Character_Type::Monster);
	Bullet->SetBulletType(Bullet_Type::Shotgun);

	for (int i = 0; i < 4; ++i)
	{
		Bullet = m_Scene->CreateGameObject<CBullet>("Bullet");
		Bullet->SetOwner(this);
		Bullet->SetBulletDir(m_arrDir[i]);
		Bullet->SetWorldPos(GetWorldPos());
		Bullet->SetWorldRotation(m_CurWeapon->GetWorldRot());
		Bullet->SetCollisionProfile("MonsterAttack");
		Bullet->SetCharacterType(Character_Type::Monster);
		Bullet->SetBulletType(Bullet_Type::Shotgun);
	}
}