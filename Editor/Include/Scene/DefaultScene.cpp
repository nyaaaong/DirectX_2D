#include "DefaultScene.h"

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

    return true;
}
