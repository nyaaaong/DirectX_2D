
#include "Bullet.h"
#include "Monster.h"
#include "SparkParticle.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderCircle.h"

CBullet::CBullet() :
	m_Distance(600.f),
	m_SparkParticleObject(nullptr),
	m_SparkParticle(nullptr),
	m_SparkMaterial(nullptr)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& obj) :
	CGameObject(obj),
	m_SparkParticleObject(nullptr),
	m_SparkParticle(nullptr),
	m_SparkMaterial(nullptr)
{
	m_Sprite = (CSpriteComponent*)FindComponent("BulletSprite");
	m_Distance = obj.m_Distance;

	m_Body = (CColliderCircle*)FindComponent("Body");
}

CBullet::~CBullet()
{
}

void CBullet::SetCollisionProfile(const std::string& Name)
{
	m_Body->SetCollisionProfile(Name);
}

void CBullet::SetDamage(const CollisionResult& result)
{
	CColliderComponent* Src = result.Src;
	CColliderComponent* Dest = result.Dest;

	CGameObject* SrcObj = Src->GetGameObject();
	CGameObject* DestObj = Dest->GetGameObject();

	std::string SrcName = SrcObj->GetName();
	std::string DestName = DestObj->GetName();

	if (SrcName == "Bullet" &&
		DestName == "Monster")
	{
		CMonster* Monster = dynamic_cast<CMonster*>(DestObj);

		if (!Monster)
			ASSERT("if (!Monster)");

		Monster->SetDamage(1);
	}
}

void CBullet::Start()
{
	CGameObject::Start();
}

bool CBullet::Init()
{
	m_Sprite = CreateComponent<CSpriteComponent>("BulletSprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(50.f, 50.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Body = CreateComponent<CColliderCircle>("Body");

	m_Body->SetRadius(25.f);

	m_Sprite->AddChild(m_Body);

	m_Body->AddCollisionCallback(Collision_State::Begin, this, &CBullet::OnCollisionBegin);
	m_Body->AddCollisionCallback(Collision_State::End, this, &CBullet::OnCollisionEnd);

	CreateMaterial();
	/*CreateParticle();

	CSparkParticle* SparkParticle = m_Scene->CreateGameObject<CSparkParticle>("SparkParticle");*/

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	float	Dist = 500.f * DeltaTime;

	m_Distance -= Dist;

	if (m_Distance <= 0.f)
	{
		Destroy();
	}

	AddRelativePos(GetWorldAxis(AXIS_Y) * Dist);
}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBullet* CBullet::Clone()
{
	return DBG_NEW CBullet(*this);
}

void CBullet::OnCollisionBegin(const CollisionResult& result)
{
	Destroy();

	CreateParticle();

	m_SparkParticleObject = m_Scene->CreateGameObject<CSparkParticle>("SparkParticle");

	m_SparkParticleObject->SetRelativePos(GetRelativePos());

	m_SparkParticle->SetMoveDir(Vector3(0.f, 1.f, 0.f));
	//m_SparkParticleObject->SetRelativeRotationZ(GetWorldRot().z);
}

void CBullet::OnCollisionEnd(const CollisionResult& result)
{
}

void CBullet::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("Spark");
	m_SparkMaterial = m_Scene->GetResource()->FindMaterial("Spark");

	m_SparkMaterial->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "Spark", TEXT("Particle/Spark.png"));

	m_SparkMaterial->SetShader("ParticleRenderShader");
	m_SparkMaterial->SetRenderState("AlphaBlend");
}

void CBullet::CreateParticle()
{
	m_Scene->GetResource()->CreateParticle("Spark");
	m_SparkParticle = m_Scene->GetResource()->FindParticle("Spark");

	//CMaterial* Material = m_Scene->GetResource()->FindMaterial("Spark");

	m_SparkParticle->SetMaterial(m_SparkMaterial);
	m_SparkParticle->SetSpawnCountMax(100);
	m_SparkParticle->SetLifeTimeMax(3.f);
	m_SparkParticle->SetScaleMin(Vector3(50.f, 50.f, 1.f));
	m_SparkParticle->SetScaleMax(Vector3(50.f, 50.f, 1.f));
	m_SparkParticle->SetSpeedMin(50.f);
	m_SparkParticle->SetSpeedMax(50.f);
	//m_SparkParticle->SetMoveDir(Vector3(0.f, -1.f, 0.f));
	//m_SparkParticle->SetStartMin(Vector3(-30.f, -30.f, 0.f));
	//m_SparkParticle->SetStartMax(Vector3(30.f, 30.f, 0.f));
	//m_SparkParticle->SetColorMin(Vector4(0.2f, 0.1f, 0.8f, 1.f));
	//m_SparkParticle->SetColorMax(Vector4(0.2f, 0.1f, 0.8f, 1.f));
	m_SparkParticle->SetMoveAngle(Vector3(0.f, 0.f, 180.f));
	m_SparkParticle->SetGravity(true);
	m_SparkParticle->SetMove(true);
}
