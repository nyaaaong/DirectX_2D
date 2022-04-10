
#include "EndingScene.h"

CEndingScene::CEndingScene()
{
	SetTypeID<CEndingScene>();
}

CEndingScene::~CEndingScene()
{
}

void CEndingScene::Start()
{
	CSceneMode::Start();
}

bool CEndingScene::Init()
{
	if (!CSceneMode::Init())
		return false;

	UseCamera(false);

	return true;
}

void CEndingScene::CreateSound()
{
}
