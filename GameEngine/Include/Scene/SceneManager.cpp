
#include "SceneManager.h"
#include "../Render/RenderManager.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()	:
	m_Scene(nullptr),
	m_NextScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_Scene);
	SAFE_DELETE(m_NextScene);
}

bool CSceneManager::Init()
{
	m_Scene = new CScene;

	CRenderManager::GetInst()->SetObjectList(&m_Scene->m_ObjList);

	return true;
}

bool CSceneManager::Update(float DeltaTime)
{
	if (!m_Scene->IsStart())
		m_Scene->Start();

	m_Scene->Update(DeltaTime);

	return false;
}

bool CSceneManager::PostUpdate(float DeltaTime)
{
	m_Scene->PostUpdate(DeltaTime);

	return false;
}
