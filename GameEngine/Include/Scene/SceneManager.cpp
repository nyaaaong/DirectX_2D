
#include "SceneManager.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()	:
	m_pScene(nullptr),
	m_pNextScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pNextScene);
	SAFE_DELETE(m_pScene);
}

bool CSceneManager::Init()
{
	m_pScene = new CScene;

	return true;
}

bool CSceneManager::Update(float fTime)
{
	m_pScene->Update(fTime);

	return false;
}

bool CSceneManager::PostUpdate(float fTime)
{
	m_pScene->PostUpdate(fTime);

	return false;
}
