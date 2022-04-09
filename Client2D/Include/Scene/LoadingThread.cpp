
#include "LoadingThread.h"
#include "MainScene.h"
#include "Scene/SceneManager.h"

CLoadingThread::CLoadingThread()
{
}

CLoadingThread::~CLoadingThread()
{
}

bool CLoadingThread::Init()
{
	if (!CThread::Init())
		return false;

	return true;
}

void CLoadingThread::Run()
{
	// ·Îµù
	CSceneManager::GetInst()->CreateNextScene(false);

	switch (CSceneManager::GetInst()->GetSceneModeType())
	{
	case SceneMode_Type::Main:
	{
		CMainScene* MainScene = CSceneManager::GetInst()->CreateSceneModeEmpty<CMainScene>(false);

		MainScene->SetLoadingFunction<CLoadingThread>(this, &CLoadingThread::AddMessage);
		MainScene->Init();
	}
		break;
	case SceneMode_Type::Boss:
	{
		/*CMainScene* MainScene = CSceneManager::GetInst()->CreateSceneModeEmpty<CMainScene>(false);

		MainScene->SetLoadingFunction<CLoadingThread>(this, &CLoadingThread::AddMessage);
		MainScene->Init();*/
	}
		break;
	case SceneMode_Type::Ending:
	{
		/*CMainScene* MainScene = CSceneManager::GetInst()->CreateSceneModeEmpty<CMainScene>(false);

		MainScene->SetLoadingFunction<CLoadingThread>(this, &CLoadingThread::AddMessage);
		MainScene->Init();*/
	}
		break;
	}

	AddMessage(true, 1.f);
}
