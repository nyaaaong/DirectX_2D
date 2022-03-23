
#include "BulletKin.h"
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
	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBulletKin::OnCollisionBegin);

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

void CBulletKin::Destroy()
{
	CMonster::Destroy();
}

void CBulletKin::OnCollisionBegin(const CollisionResult& result)
{
	CMonster::OnCollisionBegin(result);
}

void CBulletKin::PaperBurnEnd()
{
	CMonster::PaperBurnEnd();
}

void CBulletKin::Dead(float DeltaTime)
{
	CMonster::Dead(DeltaTime);
}

void CBulletKin::Hit(float DeltaTime)
{
	CMonster::Hit(DeltaTime);
}

void CBulletKin::PlaySoundDie()
{
	int i = rand() % 4 + 1;
	char Name[256] = {};

	sprintf_s(Name, "BulletKin_Die%d", i);

	m_Scene->GetResource()->SoundPlay(Name);
}