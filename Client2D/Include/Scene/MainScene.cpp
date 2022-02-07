
#include "MainScene.h"
#include "Device.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "../Object/Player2D.h"
#include "../Object/Monster.h"
#include "../Object/PixelTest.h"
#include "../Object/BubbleParticle.h"
#include "Resource/Particle/Particle.h"

CMainScene::CMainScene()	:
	m_BubbleParticle(nullptr)
{
	SetTypeID<CMainScene>();
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CreateMaterial();

	CreateParticle();

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.3f);

	CPlayer2D* Player = m_Scene->CreateGameObject<CPlayer2D>("Player");

	SetPlayerObject(Player);

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.6f);

	CMonster* Monster = m_Scene->CreateGameObject<CMonster>("Monster");

	if (m_LoadingFunction)
		m_LoadingFunction(false, 0.8f);

	CPixelTest* PixelTest = m_Scene->CreateGameObject<CPixelTest>("PixelTest");

	m_BubbleParticle = m_Scene->CreateGameObject<CBubbleParticle>("BubbleParticle");

	/*BubbleParticle = m_Scene->CreateGameObject<CBubbleParticle>("BubbleParticle");

	BubbleParticle->SetRelativePos(-100.f, 0.f, 0.f);*/
	m_MainWidget = m_Scene->GetViewport()->CreateWidgetWindow<CMainWidget>("MainWidget");

	return true;
}

void CMainScene::Update(float DeltaTime)
{
	if (!m_BubbleParticle)
		return;

	Resolution	RS = CDevice::GetInst()->GetResolution();

	float	Rand = float(rand() % RS.Width - 500.f);
	//rand() % (置企 - 置社 + 1) + 置社
		
	m_BubbleParticle->SetWorldPos(Rand, (float)RS.Height, 0.f);
}

void CMainScene::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("Bubble");
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("Bubble");

	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "Bubble", TEXT("Particle/Bubbles99px.png"));

	Material->SetShader("ParticleRenderShader");
	Material->SetRenderState("AlphaBlend");
}

void CMainScene::CreateParticle()
{
	m_Scene->GetResource()->CreateParticle("Bubble");

	CParticle* Particle = m_Scene->GetResource()->FindParticle("Bubble");

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("Bubble");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(1000);
	Particle->SetLifeTimeMin(10.f);
	Particle->SetLifeTimeMax(10.f);
	Particle->SetScaleMin(Vector3(20.f, 20.f, 1.f));
	Particle->SetScaleMax(Vector3(20.f, 20.f, 1.f));
	Particle->SetSpeedMin(300.f);
	Particle->SetSpeedMax(300.f);
	Particle->SetMoveDir(Vector3(0.f, -1.f, 0.f));
	Particle->SetStartMin(Vector3(-30.f, -30.f, 0.f));
	Particle->SetStartMax(Vector3(30.f, 30.f, 0.f));
	Particle->SetColorMin(Vector4(1.f, 1.f, 1.f, 1.f));
	Particle->SetColorMax(Vector4(1.f, 1.f, 1.f, 1.f));
	Particle->SetMoveAngle(Vector3(0.f, 0.f, 30.f));
	Particle->SetGravity(true);
	Particle->SetMove(true);
}