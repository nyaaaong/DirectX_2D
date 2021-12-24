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
	m_Scene->GetResource()->LoadSequence2D("PlayerIdle.sqc");
	m_Scene->GetResource()->LoadSequence2D("PlayerRun.sqc");

	return true;
}
