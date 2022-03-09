#include "EditorManager.h"
#include "Engine.h"
#include "Device.h"
#include "resource.h"
#include "Input.h"
#include "IMGUIManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/DefaultScene.h"
#include "Scene/CameraManager.h"
#include "Window/SpriteWindow.h"
#include "Window/DetailWindow.h"
#include "Window/EditorMenu.h"
#include "Window/ObjectHierarchy.h"
#include "Window/TileMapWindow.h"
#include "Window/TileWindow.h"
#include "Window/SceneWindow.h"
#include "Render/RenderManager.h"
#include "Object/SpriteEditObject.h"
#include "Object/DragObject.h"
#include "Object/Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/WidgetComponent.h"
#include "Component/ParticleComponent.h"
#include "Animation/AnimationSequence2DInstance.h"

DEFINITION_SINGLE(CEditorManager)

CEditorManager::CEditorManager()	:
	m_EditMode(EditMode::Scene),
	m_DragObj(nullptr),
	m_SpriteWindow(nullptr),
	m_DetailWindow(nullptr),
	m_EditorMenu(nullptr),
	m_ObjectHierarchy(nullptr),
	m_TileMapWindow(nullptr),
	m_TileWindow(nullptr),
	m_SceneWindow(nullptr),
	m_CameraMoveSpeed(3000.f),
	m_MousePush(false)
{
}

CEditorManager::~CEditorManager()
{
	CEngine::DestroyInst();
}

void CEditorManager::SetEditMode(EditMode Mode)
{
	m_EditMode = Mode;

	switch (m_EditMode)
	{
	case EditMode::Scene:
		break;
	case EditMode::Sprite:
		if (m_DragObj)
			m_DragObj->Destroy();
		m_DragObj = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDragObject>("DragObject");
		m_DragObj->SetWorldScale(0.f, 0.f, 1.f);
		break;
	case EditMode::TileMap:
		/*if (m_DragObj)
		{
			m_DragObj->Destroy();
			m_DragObj = nullptr;
		}*/
		break;
	}

	if (m_EditMode == EditMode::Sprite)
	{
	}
}

bool CEditorManager::Init(HINSTANCE hInst)
{
	//CEngine::GetInst()->SetPlay(false);

	if (!CEngine::GetInst()->Init(hInst, TEXT("GameEngine"), 1280, 720, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	CSceneManager::GetInst()->SetCreateSceneModeFunction<CEditorManager>(this, &CEditorManager::CreateSceneMode);
	CSceneManager::GetInst()->SetCreateObjectFunction<CEditorManager>(this, &CEditorManager::CreateObject);
	CSceneManager::GetInst()->SetCreateComponentFunction<CEditorManager>(this, &CEditorManager::CreateComponent);
	CSceneManager::GetInst()->SetCreateAnimInstanceFunction<CEditorManager>(this, &CEditorManager::CreateAnimInstance);

	// IMGUI로 에디터에서 사용할 윈도우를 만들어준다.
	m_SpriteWindow = CIMGUIManager::GetInst()->AddWindow<CSpriteWindow>("SpriteWindow");
	m_DetailWindow = CIMGUIManager::GetInst()->AddWindow<CDetailWindow>("DetailWindow");
	m_EditorMenu = CIMGUIManager::GetInst()->AddWindow<CEditorMenu>("EditorMenu");
	m_ObjectHierarchy = CIMGUIManager::GetInst()->AddWindow<CObjectHierarchy>("ObjectHierarchy");
	m_TileMapWindow = CIMGUIManager::GetInst()->AddWindow<CTileMapWindow>("TileMapWindow");
	m_TileWindow = CIMGUIManager::GetInst()->AddWindow<CTileWindow>("TileWindow");
	m_SceneWindow = CIMGUIManager::GetInst()->AddWindow<CSceneWindow>("SceneWindow");

	CInput::GetInst()->CreateKey("MouseClick", VK_LBUTTON);

	CInput::GetInst()->CreateKey("Esc", VK_ESCAPE);
	CInput::GetInst()->SetKeyCallback("Esc", KeyState_Down, this, &CEditorManager::Esc);

	CRenderManager::GetInst()->CreateLayer("DragLayer", INT_MAX);

	CInput::GetInst()->CreateKey("MouseLButton", VK_LBUTTON);
	CInput::GetInst()->SetKeyCallback("MouseLButton", KeyState_Down, this, &CEditorManager::MouseLButtonDown);
	CInput::GetInst()->SetKeyCallback("MouseLButton", KeyState_Push, this, &CEditorManager::MouseLButtonPush);
	CInput::GetInst()->SetKeyCallback("MouseLButton", KeyState_Up, this, &CEditorManager::MouseLButtonUp);

	CInput::GetInst()->CreateKey("Up", VK_UP);
	CInput::GetInst()->CreateKey("Down", VK_DOWN);
	CInput::GetInst()->CreateKey("Left", VK_LEFT);
	CInput::GetInst()->CreateKey("Right", VK_RIGHT);

	CInput::GetInst()->SetKeyCallback("Up", KeyState_Down, this, &CEditorManager::KeyboardUp);
	CInput::GetInst()->SetKeyCallback("Down", KeyState_Down, this, &CEditorManager::KeyboardDown);
	CInput::GetInst()->SetKeyCallback("Left", KeyState_Down, this, &CEditorManager::KeyboardLeft);
	CInput::GetInst()->SetKeyCallback("Right", KeyState_Down, this, &CEditorManager::KeyboardRight);

	CInput::GetInst()->CreateKey("MoveUp", 'W');
	CInput::GetInst()->CreateKey("MoveDown", 'S');
	CInput::GetInst()->CreateKey("MoveLeft", 'A');
	CInput::GetInst()->CreateKey("MoveRight", 'D');

	CInput::GetInst()->SetKeyCallback("MoveUp", KeyState_Push, this, &CEditorManager::MoveCameraUp);
	CInput::GetInst()->SetKeyCallback("MoveDown", KeyState_Push, this, &CEditorManager::MoveCameraDown);
	CInput::GetInst()->SetKeyCallback("MoveLeft", KeyState_Push, this, &CEditorManager::MoveCameraLeft);
	CInput::GetInst()->SetKeyCallback("MoveRight", KeyState_Push, this, &CEditorManager::MoveCameraRight);

	CInput::GetInst()->CreateKey("TabUp", VK_NUMPAD8);
	CInput::GetInst()->CreateKey("TabDown", VK_NUMPAD2);
	CInput::GetInst()->CreateKey("TabLeft", VK_NUMPAD4);
	CInput::GetInst()->CreateKey("TabRight", VK_NUMPAD6);

	CInput::GetInst()->SetKeyCallback("TabUp", KeyState_Down, this, &CEditorManager::MoveTabUp);
	CInput::GetInst()->SetKeyCallback("TabDown", KeyState_Down, this, &CEditorManager::MoveTabDown);
	CInput::GetInst()->SetKeyCallback("TabLeft", KeyState_Down, this, &CEditorManager::MoveTabLeft);
	CInput::GetInst()->SetKeyCallback("TabRight", KeyState_Down, this, &CEditorManager::MoveTabRight);

	return true;
}

void CEditorManager::CreateDefaultSceneMode()
{
	CSceneManager::GetInst()->CreateSceneMode<CDefaultScene>();
}

int CEditorManager::Run()
{
	return CEngine::GetInst()->Run();
}

void CEditorManager::Esc(float DeltaTime)
{
	if (!m_SpriteWindow)
		return;

	m_SpriteWindow->SelectCancelFrameList();
}

void CEditorManager::MouseLButtonDown(float DeltaTime)
{
	if (!m_DragObj || !m_SpriteWindow->HasSprite())
		return;
	
	Vector2		MousePos = CInput::GetInst()->GetMousePos();
	Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

	if (MousePos.x < 0.f)
		MousePos.x = 0.f;

	else if (MousePos.x > ImgSize.x)
		MousePos.x = ImgSize.x;

	if (MousePos.y < 0.f)
		MousePos.y = 0.f;

	else if (MousePos.y > ImgSize.y)
		MousePos.y = ImgSize.y;

	switch (m_SpriteWindow->GetCaptureMode())
	{
		case EM_CAPTURE:
		{
			m_DragObj->SetStartPos(MousePos);
			break;
		}
		case EM_DRAG:
		{
			m_CurMousePos = Vector3(MousePos.x, MousePos.y, 0.f);
			m_PrevMousePos = m_CurMousePos;
			break;
		}
	}	
}

void CEditorManager::MouseLButtonPush(float DeltaTime)
{
	m_MousePush = true;

	if (!m_DragObj || !m_SpriteWindow->HasSprite())
		return;

	if (m_SpriteWindow->HasSprite())
	{
		Vector2		MousePos = CInput::GetInst()->GetMousePos();
		Vector2		StartPos = m_DragObj->GetStartPos();
		Vector2		EndPos = m_DragObj->GetEndPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		switch (m_SpriteWindow->GetCaptureMode())
		{
		case EM_CAPTURE:
		{
			if (MousePos.x < 0.f)
				MousePos.x = 0.f;

			else if (MousePos.x > ImgSize.x)
				MousePos.x = ImgSize.x;

			if (MousePos.y < 0.f)
				MousePos.y = 0.f;

			else if (MousePos.y > ImgSize.y)
				MousePos.y = ImgSize.y;

			m_DragObj->SetEndPos(MousePos);

			if (StartPos == EndPos)
				return;

			m_SpriteWindow->RefreshInput();
			break;
		}
		case EM_DRAG:
		{
			m_CurMousePos = Vector3(MousePos.x, MousePos.y, 0.f);

			Vector3	Result3D = m_CurMousePos - m_PrevMousePos;
			Vector3	DragWorldPos = m_DragObj->GetWorldPos();
			Vector2	DragSize = m_DragObj->GetEndPos() - m_DragObj->GetStartPos();
			DragSize = Vector2(abs(DragSize.x), abs(DragSize.y));

			// Left, Top
			if (Result3D.x + DragWorldPos.x < 0.f)
				Result3D.x = -DragWorldPos.x;

			else if (Result3D.x + DragWorldPos.x + DragSize.x > ImgSize.x)
				Result3D.x = ImgSize.x - DragWorldPos.x - DragSize.x;

			if (Result3D.y + DragWorldPos.y - DragSize.y < 0.f)
				Result3D.y = -DragWorldPos.y + DragSize.y;

			else if (Result3D.y + DragWorldPos.y > ImgSize.y)
				Result3D.y = ImgSize.y - DragWorldPos.y;

			m_DragObj->AddWorldPos(Result3D);

			Vector2	Result2D = Vector2(Result3D.x, Result3D.y);
			m_DragObj->AddStartPos(Result2D);
			m_DragObj->AddEndPos(Result2D);

			m_PrevMousePos = m_CurMousePos;

			m_SpriteWindow->RefreshInput();
			break;
		}
		}
	}
}

void CEditorManager::MouseLButtonUp(float DeltaTime)
{
	m_MousePush = false;
}

void CEditorManager::KeyboardUp(float DeltaTime)
{
	if (m_DragObj && m_SpriteWindow->HasSprite())
	{
		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ResultPos = RectPos + Vector3(0.f, 1.f, 0.f);
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (ResultPos.y > ImgSize.y)
			ResultPos.y = ImgSize.y;

		Vector2	Result2DPos;
		Result2DPos.y = ResultPos.y - RectPos.y;

		m_DragObj->AddStartPos(Result2DPos);
		m_DragObj->AddEndPos(Result2DPos);
		m_DragObj->SetWorldPos(ResultPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::KeyboardDown(float DeltaTime)
{
	if (m_DragObj && m_SpriteWindow->HasSprite())
	{
		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ResultPos = RectPos + Vector3(0.f, -1.f, 0.f);
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();
		Vector2		DragSize = m_DragObj->GetEndPos() - m_DragObj->GetStartPos();

		if (ResultPos.y + DragSize.y < 0.f)
			ResultPos.y = -DragSize.y;

		Vector2	Result2DPos;
		Result2DPos.y = ResultPos.y - RectPos.y;

		m_DragObj->AddStartPos(Result2DPos);
		m_DragObj->AddEndPos(Result2DPos);

		m_DragObj->SetWorldPos(ResultPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::KeyboardLeft(float DeltaTime)
{
	if (m_DragObj && m_SpriteWindow->HasSprite())
	{
		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ResultPos = RectPos + Vector3(-1.f, 0.f, 0.f);
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (ResultPos.x < 0.f)
			ResultPos.x = 0.f;

		Vector2	Result2DPos;
		Result2DPos.x = ResultPos.x - RectPos.x;

		m_DragObj->AddStartPos(Result2DPos);
		m_DragObj->AddEndPos(Result2DPos);

		m_DragObj->SetWorldPos(ResultPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::KeyboardRight(float DeltaTime)
{
	if (m_DragObj && m_SpriteWindow->HasSprite())
	{
		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ResultPos = RectPos + Vector3(1.f, 0.f, 0.f);
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();
		Vector2		DragSize = m_DragObj->GetEndPos() - m_DragObj->GetStartPos();

		if (ResultPos.x + DragSize.x > ImgSize.x)
			ResultPos.x = ImgSize.x - DragSize.x;

		Vector2	Result2DPos;
		Result2DPos.x = ResultPos.x - RectPos.x;

		m_DragObj->AddStartPos(Result2DPos);
		m_DragObj->AddEndPos(Result2DPos);

		m_DragObj->SetWorldPos(ResultPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::MoveCameraUp(float DeltaTime)
{
	if (m_SpriteWindow->HasSprite())
		return;

	CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

	// ceil : 소숫점을 올림해서 타일간의 빈틈이 보이지 않게 한다.
	Camera->AddWorldPos(Vector3(0.f, ceil(m_CameraMoveSpeed * DeltaTime), 0.f));
}

void CEditorManager::MoveCameraDown(float DeltaTime)
{
	if (m_SpriteWindow->HasSprite())
		return;

	CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

	Camera->AddWorldPos(Vector3(0.f, ceil(-m_CameraMoveSpeed * DeltaTime), 0.f));
}

void CEditorManager::MoveCameraLeft(float DeltaTime)
{
	if (m_SpriteWindow->HasSprite())
		return;

	CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

	Camera->AddWorldPos(Vector3(ceil(-m_CameraMoveSpeed * DeltaTime), 0.f, 0.f));
}

void CEditorManager::MoveCameraRight(float DeltaTime)
{
	if (m_SpriteWindow->HasSprite())
		return;

	CCameraComponent* Camera = CSceneManager::GetInst()->GetScene()->GetCameraManager()->GetCurrentCamera();

	Camera->AddWorldPos(Vector3(ceil(m_CameraMoveSpeed * DeltaTime), 0.f, 0.f));
}

void CEditorManager::MoveTabUp(float DeltaTime)
{
	if (m_DragObj && m_SpriteWindow->HasSprite())
	{
		float		RectSizeY = m_DragObj->GetEndPos().y - m_DragObj->GetStartPos().y;
		float		MoveScale = abs(RectSizeY);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ResultPos = RectPos + Vector3(0.f, MoveScale, 0.f);
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (ResultPos.y > ImgSize.y)
			ResultPos.y = ImgSize.y;

		Vector2	Result2DPos;
		Result2DPos.y = ResultPos.y - RectPos.y;

		m_DragObj->AddStartPos(Result2DPos);
		m_DragObj->AddEndPos(Result2DPos);
		m_DragObj->SetWorldPos(ResultPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::MoveTabDown(float DeltaTime)
{
	if (m_DragObj && m_SpriteWindow->HasSprite())
	{
		float		RectSizeY = m_DragObj->GetEndPos().y - m_DragObj->GetStartPos().y;
		float		MoveScale = abs(RectSizeY);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ResultPos = RectPos + Vector3(0.f, -MoveScale, 0.f);
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (ResultPos.y + RectSizeY < 0.f)
			ResultPos.y = -RectSizeY;

		Vector2	Result2DPos;
		Result2DPos.y = ResultPos.y - RectPos.y;

		m_DragObj->AddStartPos(Result2DPos);
		m_DragObj->AddEndPos(Result2DPos);
		m_DragObj->SetWorldPos(ResultPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::MoveTabLeft(float DeltaTime)
{
	if (m_DragObj && m_SpriteWindow->HasSprite())
	{
		float		RectSizeX = m_DragObj->GetEndPos().x - m_DragObj->GetStartPos().x;
		float		MoveScale = abs(RectSizeX);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ResultPos = RectPos + Vector3(-MoveScale, 0.f, 0.f);
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (ResultPos.x < 0.f)
			ResultPos.x = 0.f;

		Vector2	Result2DPos;
		Result2DPos.x = ResultPos.x - RectPos.x;

		m_DragObj->AddStartPos(Result2DPos);
		m_DragObj->AddEndPos(Result2DPos);
		m_DragObj->SetWorldPos(ResultPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::MoveTabRight(float DeltaTime)
{
	if (m_DragObj && m_SpriteWindow->HasSprite())
	{
		float		RectSizeX = m_DragObj->GetEndPos().x - m_DragObj->GetStartPos().x;
		float		MoveScale = abs(RectSizeX);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ResultPos = RectPos + Vector3(MoveScale, 0.f, 0.f);
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (ResultPos.x + RectSizeX > ImgSize.x)
			ResultPos.x = ImgSize.x - RectSizeX;

		Vector2	Result2DPos;
		Result2DPos.x = ResultPos.x - RectPos.x;

		m_DragObj->AddStartPos(Result2DPos);
		m_DragObj->AddEndPos(Result2DPos);
		m_DragObj->SetWorldPos(ResultPos);

		m_SpriteWindow->RefreshInput();
	}
}
void CEditorManager::CreateSceneMode(CScene* Scene, size_t Type)
{
	if (Type == typeid(CDefaultScene).hash_code())
	{
		Scene->LoadSceneMode<CDefaultScene>();
	}
}

CGameObject* CEditorManager::CreateObject(CScene* Scene, size_t Type)
{
	if (Type == typeid(CGameObject).hash_code())
	{
		CGameObject* Obj = Scene->LoadGameObject<CGameObject>();

		return Obj;
	}

	else if (Type == typeid(CDragObject).hash_code())
	{
		CDragObject* Obj = Scene->LoadGameObject<CDragObject>();

		return Obj;
	}

	else if (Type == typeid(CSpriteEditObject).hash_code())
	{
		CSpriteEditObject* Obj = Scene->LoadGameObject<CSpriteEditObject>();

		return Obj;
	}

	else if (Type == typeid(CPlayer2D).hash_code())
	{
		CPlayer2D* Obj = Scene->LoadGameObject<CPlayer2D>();

		return Obj;
	}

	return nullptr;
}

CComponent* CEditorManager::CreateComponent(CGameObject* Obj, size_t Type)
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

void CEditorManager::CreateAnimInstance(CSpriteComponent* Sprite, size_t Type)
{
	if (Type == typeid(CAnimationSequence2DInstance).hash_code())
	{
		Sprite->LoadAnimationInstance<CAnimationSequence2DInstance>();
	}
}