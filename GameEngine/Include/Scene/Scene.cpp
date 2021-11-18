
#include "Scene.h"

CScene::CScene()
{
	m_pMode = new CSceneMode;
}

CScene::~CScene()
{
}

void CScene::Update(float fTime)
{
	m_pMode->Update(fTime);
}

void CScene::PostUpdate(float fTime)
{
	m_pMode->PostUpdate(fTime);
}
