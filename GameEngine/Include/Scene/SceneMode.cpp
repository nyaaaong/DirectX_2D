
#include "SceneMode.h"

CSceneMode::CSceneMode()	:
	m_Scene(nullptr)
{
	SetTypeID<CSceneMode>();
}

CSceneMode::~CSceneMode()
{
}

bool CSceneMode::Init()
{
	return true;
}

void CSceneMode::Update(float DeltaTime)
{
}

void CSceneMode::PostUpdate(float DeltaTime)
{
}
