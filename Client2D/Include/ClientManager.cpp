#include "ClientManager.h"
#include "Engine.h"
#include "resource.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/MainScene.h"
#include "Scene/StartScene.h"
#include "Resource/ResourceManager.h"
#include "Widget/MouseNormal.h"
#include "Widget/MouseAttack.h"

DEFINITION_SINGLE(CClientManager)

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
	CEngine::DestroyInst();
}

bool CClientManager::Init(HINSTANCE hInst)
{
	if (!CEngine::GetInst()->Init(hInst, TEXT("GameEngine"),
		1280, 720, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	CSceneManager::GetInst()->SetCreateSceneModeFunction<CClientManager>(this, &CClientManager::CreateSceneMode);
	CSceneManager::GetInst()->SetCreateObjectFunction<CClientManager>(this, &CClientManager::CreateObject);

	CInput::GetInst()->CreateKey("MoveUp", 'W');
	CInput::GetInst()->CreateKey("MoveDown", 'S');
	CInput::GetInst()->CreateKey("MoveLeft", 'A');
	CInput::GetInst()->CreateKey("MoveRight", 'D');
	CInput::GetInst()->CreateKey("RotationZInv", VK_LEFT);
	CInput::GetInst()->CreateKey("RotationZ", VK_RIGHT);
	//CInput::GetInst()->CreateKey("Dodge", VK_SPACE);
	CInput::GetInst()->CreateKey("Attack1", VK_LBUTTON);
	CInput::GetInst()->CreateKey("test", VK_RETURN);
	CInput::GetInst()->CreateKey("Skill1", '1');

	CResourceManager::GetInst()->CreateSoundChannelGroup("UI");
	CResourceManager::GetInst()->SetVolume(10);

	// 마우스 위젯 설정
	CMouseNormal* MouseNormal = CEngine::GetInst()->CreateMouse<CMouseNormal>(Mouse_State::Normal, "MouseNormal");
	CMouseAttack* MouseAttack = CEngine::GetInst()->CreateMouse<CMouseAttack>(Mouse_State::State1, "MouseAttack");

	return true;
}

void CClientManager::CreateDefaultSceneMode()
{
	CSceneManager::GetInst()->CreateSceneMode<CStartScene>();
}

int CClientManager::Run()
{
	return CEngine::GetInst()->Run();
}

void CClientManager::CreateSceneMode(CScene* Scene, size_t Type)
{
}

CGameObject* CClientManager::CreateObject(CScene* Scene, size_t Type)
{
	return nullptr;
}
