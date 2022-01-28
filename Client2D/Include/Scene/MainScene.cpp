
#include "MainScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "../Object/Player2D.h"
#include "../Object/Monster.h"
#include "../Object/PixelTest.h"
#include "../Object/BubbleParticle.h"
#include "Resource/Particle/Particle.h"

CMainScene::CMainScene()
{
	SetTypeID<CMainScene>();
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CreateMaterial();

	CreateAnimationSequence();

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

	CBubbleParticle* BubbleParticle = m_Scene->CreateGameObject<CBubbleParticle>("BubbleParticle");

	m_MainWidget = m_Scene->GetViewport()->CreateWidgetWindow<CMainWidget>("MainWidget");

	return true;
}

void CMainScene::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("Bubble");
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("Bubble");

	Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "Bubble", TEXT("Particle/Bubbles99px.png"));

	Material->SetShader("ParticleRenderShader");
}

void CMainScene::CreateAnimationSequence()
{
	m_Scene->GetResource()->CreateAnimationSequence2D("PlayerIdleD", "Player", TEXT("Player.png"), Vector2(66.f, 117.f), Vector2(42.f, 66.f), 4, 6);

	m_Scene->GetResource()->CreateAnimationSequence2D("PlayerDodgeD", "Player", TEXT("Player.png"), Vector2(66.f, 876.f), Vector2(48.f, 87.f), 9, 6);
}

void CMainScene::CreateParticle()
{
	m_Scene->GetResource()->CreateParticle("Bubble");
	CParticle* Particle = m_Scene->GetResource()->FindParticle("Bubble");

	CMaterial* Material = m_Scene->GetResource()->FindMaterial("Bubble");

	Particle->SetMaterial(Material);
	Particle->SetSpawnCountMax(100);
	Particle->SetLifeTimeMin(1.f);
	Particle->SetLifeTimeMax(2.f);
	Particle->SetScaleMin(Vector3(20.f, 20.f, 1.f));
	Particle->SetScaleMax(Vector3(50.f, 50.f, 1.f));
	Particle->SetSpeedMin(100.f);
	Particle->SetSpeedMax(300.f);
	Particle->SetMoveDir(Vector3(0.f, 1.f, 0.f));
	Particle->SetStartMin(Vector3(-30.f, -30.f, 0.f));
	Particle->SetStartMax(Vector3(30.f, 30.f, 0.f));
	Particle->SetMove(true);
}