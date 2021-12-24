
#include "SceneCollision.h"
#include "../Engine.h"

CSceneCollision::CSceneCollision()
{
}

CSceneCollision::~CSceneCollision()
{
}

void CSceneCollision::Start()
{
	if (CEngine::GetInst()->GetEngineSpace() == Engine_Space::Space2D)
	{
	}

	else
	{
	}
}

bool CSceneCollision::Init()
{
	return true;
}
