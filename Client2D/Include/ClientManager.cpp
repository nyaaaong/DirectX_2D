#include "ClientManager.h"
#include "Engine.h"
#include "resource.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/MainScene.h"
#include "Scene/StartScene.h"
#include "Resource/ResourceManager.h"
#include "Widget/MouseCursor.h"
#include "Object/Player2D.h"
#include "Object/TileMap.h"
#include "Component/TileMapComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/WidgetComponent.h"
#include "Component/ParticleComponent.h"

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
	TCHAR	Title[256] = {};

#ifdef _DEBUG
	lstrcpy(Title, TEXT("Enter The Gungeon (Debug Mode)"));
#else
	lstrcpy(Title, TEXT("Enter The Gungeon Editor"));
#endif // _DEBUG

	if (!CEngine::GetInst()->Init(hInst, Title, 1280, 720, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	CSceneManager::GetInst()->SetCreateSceneModeFunction<CClientManager>(this, &CClientManager::CreateSceneMode);
	CSceneManager::GetInst()->SetCreateObjectFunction<CClientManager>(this, &CClientManager::CreateObject);
	CSceneManager::GetInst()->SetCreateComponentFunction<CClientManager>(this, &CClientManager::CreateComponent);

	CInput::GetInst()->CreateKey("MoveUp", 'W');
	CInput::GetInst()->CreateKey("MoveDown", 'S');
	CInput::GetInst()->CreateKey("MoveLeft", 'A');
	CInput::GetInst()->CreateKey("MoveRight", 'D');
	CInput::GetInst()->CreateKey("Dodge", VK_RBUTTON);
	CInput::GetInst()->CreateKey("Attack", VK_LBUTTON);
	CInput::GetInst()->CreateKey("NoWeapon", '1');
	CInput::GetInst()->CreateKey("Weapon1", '2');
	CInput::GetInst()->CreateKey("Weapon2", '3');
	CInput::GetInst()->CreateKey("Weapon3", '4');

	CResourceManager::GetInst()->CreateSoundChannelGroup("UI");
	CResourceManager::GetInst()->SetVolume("UI", 50);
	CResourceManager::GetInst()->CreateSoundChannelGroup("BGM");
	CResourceManager::GetInst()->SetVolume("BGM", 50);
	CResourceManager::GetInst()->CreateSoundChannelGroup("Effect");
	CResourceManager::GetInst()->SetVolume("Effect", 30);

	// 마우스 위젯 설정
	CMouseCursor* MouseCursor = CEngine::GetInst()->CreateMouse<CMouseCursor>(Mouse_State::Normal, "MouseCursor");

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
	if (Type == typeid(CGameObject).hash_code())
	{
		CGameObject* Obj = Scene->LoadGameObject<CGameObject>();

		return Obj;
	}

	else if (Type == typeid(CPlayer2D).hash_code())
	{
		CPlayer2D* Obj = Scene->LoadGameObject<CPlayer2D>();

		return Obj;
	}

	else if (Type == typeid(CTileMap).hash_code())
	{
		CTileMap* Obj = Scene->LoadGameObject<CTileMap>();

		return Obj;
	}

	return nullptr;
}

CComponent* CClientManager::CreateComponent(CGameObject * Obj, size_t Type)
{
	CSceneComponent* Root = Obj->GetRootComponent();

	if (Type == typeid(CSceneComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CSceneComponent>();

		if (Root)
			Root->AddChild((CSceneComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CSpriteComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CSpriteComponent>();

		if (Root)
			Root->AddChild((CSpriteComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CStaticMeshComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CStaticMeshComponent>();

		if (Root)
			Root->AddChild((CStaticMeshComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CTileMapComponent).hash_code())
	{
		CTileMapComponent* Component = Obj->LoadComponent<CTileMapComponent>();

		if (Root)
			Root->AddChild((CTileMapComponent*)Component);

		Component->EnableEditMode(true);

		return Component;
	}

	else if (Type == typeid(CColliderBox2D).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CColliderBox2D>();

		if (Root)
			Root->AddChild((CColliderBox2D*)Component);

		return Component;
	}

	else if (Type == typeid(CColliderCircle).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CColliderCircle>();

		if (Root)
			Root->AddChild((CColliderCircle*)Component);

		return Component;
	}

	else if (Type == typeid(CColliderPixel).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CColliderPixel>();

		if (Root)
			Root->AddChild((CColliderPixel*)Component);

		return Component;
	}

	else if (Type == typeid(CCameraComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CCameraComponent>();

		if (Root)
			Root->AddChild((CCameraComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CWidgetComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CWidgetComponent>();

		if (Root)
			Root->AddChild((CWidgetComponent*)Component);

		return Component;
	}

	else if (Type == typeid(CParticleComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CParticleComponent>();

		if (Root)
			Root->AddChild((CParticleComponent*)Component);

		return Component;
	}

	return nullptr;
}
