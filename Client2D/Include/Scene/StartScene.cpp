
#include "StartScene.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "../Object/Player2D.h"
#include "Scene/SceneResource.h"

CStartScene::CStartScene()
{
	SetTypeID<CStartScene>();
}

CStartScene::~CStartScene()
{
	m_Scene->GetResource()->SoundStop("Title");
}

void CStartScene::Start()
{
	CSceneMode::Start();

	m_Scene->GetResource()->SoundPlay("Title");
}

bool CStartScene::Init()
{
	UseCamera(false);

	m_StartWidget = m_Scene->GetViewport()->CreateWidgetWindow<CStartWidget>("StartWidget");

	CreateSound();

	return true;
}

void CStartScene::CreateSound()
{
	m_Scene->GetResource()->LoadSound("BGM", true, "Title", "BGM/Title.mp3");
	m_Scene->GetResource()->LoadSound("Effect", false, "Menu_Select", "UI/Menu_Select.wav");
	m_Scene->GetResource()->LoadSound("Effect", false, "Menu_MouseOver", "UI/Menu_MouseOver.wav");
}
