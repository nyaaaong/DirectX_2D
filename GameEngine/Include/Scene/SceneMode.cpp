
#include "SceneMode.h"

CSceneMode::CSceneMode()	:
	m_pScene(nullptr)
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

void CSceneMode::Update(float fTime)
{
}

void CSceneMode::PostUpdate(float fTime)
{
}
