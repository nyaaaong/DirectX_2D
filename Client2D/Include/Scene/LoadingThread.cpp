
#include "LoadingThread.h"
#include "MainScene.h"
#include "EndingScene.h"
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
	case SceneMode_Type::Ending:
	{
		CEndingScene* EndingScene = CSceneManager::GetInst()->CreateSceneModeEmpty<CEndingScene>(false);

		EndingScene->Init();
	}
	return;
	}

	AddMessage(true, 1.f);
}
