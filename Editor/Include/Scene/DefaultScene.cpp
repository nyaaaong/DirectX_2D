#include "DefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"

CDefaultScene::CDefaultScene()
{
	SetTypeID<CDefaultScene>();
}

CDefaultScene::~CDefaultScene()
{
}

bool CDefaultScene::Init()
{
	if (!CSceneMode::Init())
		return false;

	if (!LoadAnimationSequence2D())
		return false;

    return true;
}

bool CDefaultScene::LoadAnimationSequence2D()
{
	m_Scene->GetResource()->LoadSequence2D("Player_Idle_Down.sqc");

	return true;
}
