#include "EditorManager.h"
#include "Engine.h"
#include "Device.h"
#include "resource.h"
#include "Input.h"
#include "IMGUIManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/DefaultScene.h"
#include "Window/SpriteWindow.h"
#include "Window/DetailWindow.h"
#include "Window/EditorMenu.h"
#include "Window/ObjectHierarchy.h"
#include "Render/RenderManager.h"
#include "Object/SpriteEditObject.h"
#include "Object/DragObject.h"
#include "Object/Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/StaticMeshComponent.h"
#include "Animation/AnimationSequence2DInstance.h"

DEFINITION_SINGLE(CEditorManager)

CEditorManager::CEditorManager()	:
	m_EditMode(EditMode::Scene),
	m_DragObj(nullptr),
	m_SpriteWindow(nullptr),
	m_DetailWindow(nullptr),
	m_EditorMenu(nullptr),
	m_ObjectHierarchy(nullptr)
{
}

CEditorManager::~CEditorManager()
{
	CEngine::DestroyInst();
}

void CEditorManager::SetEditMode(EditMode Mode)
{
	m_EditMode = Mode;

	if (m_EditMode == EditMode::Sprite)
	{
		if (m_DragObj)
			m_DragObj->Destroy();
		
		m_DragObj = CSceneManager::GetInst()->GetScene()->CreateGameObject<CDragObject>("DragObject");
		m_DragObj->SetWorldScale(0.f, 0.f, 1.f);
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

	// IMGUI�� �����Ϳ��� ����� �����츦 ������ش�.
	m_SpriteWindow = CIMGUIManager::GetInst()->AddWindow<CSpriteWindow>("SpriteWindow");
	m_DetailWindow = CIMGUIManager::GetInst()->AddWindow<CDetailWindow>("DetailWindow");
	m_EditorMenu = CIMGUIManager::GetInst()->AddWindow<CEditorMenu>("EditorMenu");
	m_ObjectHierarchy = CIMGUIManager::GetInst()->AddWindow<CObjectHierarchy>("ObjectHierarchy");

	CInput::GetInst()->CreateKey("MouseClick", VK_LBUTTON);

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
	CInput::GetInst()->CreateKey("RotationZInv", 'A');
	CInput::GetInst()->CreateKey("RotationZ", 'D');

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

void CEditorManager::MouseLButtonDown(float DeltaTime)
{
	if (!m_DragObj)
		return;

	else if (!m_SpriteWindow)
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
	if (!m_DragObj)
		return;

	else if (!m_SpriteWindow)
		return;

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

void CEditorManager::MouseLButtonUp(float DeltaTime)
{
}

void CEditorManager::KeyboardUp(float DeltaTime)
{
	if (m_DragObj)
	{
		m_DragObj->AddWorldPos(0.f, 1.f, 0.f);

		Vector2	Result2D = Vector2(0.f, 1.f);
		m_DragObj->AddStartPos(Result2D);
		m_DragObj->AddEndPos(Result2D);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (RectPos.y > ImgSize.y)
			RectPos.y = ImgSize.y;

		m_DragObj->SetWorldPos(RectPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::KeyboardDown(float DeltaTime)
{
	if (m_DragObj)
	{
		m_DragObj->AddWorldPos(0.f, -1.f, 0.f);

		Vector2	Result2D = Vector2(0.f, -1.f);
		m_DragObj->AddStartPos(Result2D);
		m_DragObj->AddEndPos(Result2D);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();
		Vector2		DragSize = m_DragObj->GetEndPos() - m_DragObj->GetStartPos();

		if (RectPos.y + DragSize.y < 0.f)
			RectPos.y = -DragSize.y;

		m_DragObj->SetWorldPos(RectPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::KeyboardLeft(float DeltaTime)
{
	if (m_DragObj)
	{
		m_DragObj->AddWorldPos(-1.f, 0.f, 0.f);

		Vector2	Result2D = Vector2(-1.f, 0.f);
		m_DragObj->AddStartPos(Result2D);
		m_DragObj->AddEndPos(Result2D);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (RectPos.x < 0.f)
			RectPos.x = 0.f;

		m_DragObj->SetWorldPos(RectPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::KeyboardRight(float DeltaTime)
{
	if (m_DragObj)
	{
		m_DragObj->AddWorldPos(1.f, 0.f, 0.f);

		Vector2	Result2D = Vector2(1.f, 0.f);
		m_DragObj->AddStartPos(Result2D);
		m_DragObj->AddEndPos(Result2D);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();
		Vector2		DragSize = m_DragObj->GetEndPos() - m_DragObj->GetStartPos();

		if (RectPos.x + DragSize.x > ImgSize.x)
			RectPos.x = ImgSize.x - DragSize.x;

		m_DragObj->SetWorldPos(RectPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::MoveTabUp(float DeltaTime)
{
	if (m_DragObj)
	{
		float	DragPosY = m_DragObj->GetStartPos().y;
		float	ResH = (float)CDevice::GetInst()->GetResolution().Height;

		if (DragPosY >= ResH)
			return;

		Vector2	Size = m_DragObj->GetStartPos() - m_DragObj->GetEndPos();
		float	ResultY = abs(Size.y);

		if (ResultY + DragPosY >= ResH)
			ResultY = ResH - DragPosY;

		m_DragObj->AddWorldPos(0.f, ResultY, 0.f);

		Vector2	Result2D = Vector2(0.f, ResultY);
		m_DragObj->AddStartPos(Result2D);
		m_DragObj->AddEndPos(Result2D);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (RectPos.y > ImgSize.y)
			RectPos.y = ImgSize.y;

		m_DragObj->SetWorldPos(RectPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::MoveTabDown(float DeltaTime)
{
	if (m_DragObj)
	{
		float	DragPosY = m_DragObj->GetEndPos().y;

		if (DragPosY <= 0.f)
			return;

		Vector2	Size = m_DragObj->GetStartPos() - m_DragObj->GetEndPos();
		float	ResultY = -abs(Size.y);

		if (ResultY + DragPosY <= 0.f)
			ResultY = -DragPosY;

		m_DragObj->AddWorldPos(0.f, ResultY, 0.f);

		Vector2	Result2D = Vector2(0.f, ResultY);
		m_DragObj->AddStartPos(Result2D);
		m_DragObj->AddEndPos(Result2D);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();
		Vector2		DragSize = m_DragObj->GetEndPos() - m_DragObj->GetStartPos();

		if (RectPos.y + DragSize.y < 0.f)
			RectPos.y = -DragSize.y;

		m_DragObj->SetWorldPos(RectPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::MoveTabLeft(float DeltaTime)
{
	if (m_DragObj)
	{
		float	DragPosX = m_DragObj->GetStartPos().x;

		if (DragPosX <= 0.f)
			return;

		Vector2	Size = m_DragObj->GetStartPos() - m_DragObj->GetEndPos();
		float	ResultX = -abs(Size.x);

		if (ResultX + DragPosX <= 0.f)
			ResultX = -DragPosX;

		m_DragObj->AddWorldPos(ResultX, 0.f, 0.f);

		Vector2	Result2D = Vector2(ResultX, 0.f);
		m_DragObj->AddStartPos(Result2D);
		m_DragObj->AddEndPos(Result2D);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();

		if (RectPos.x < 0.f)
			RectPos.x = 0.f;

		m_DragObj->SetWorldPos(RectPos);

		m_SpriteWindow->RefreshInput();
	}
}

void CEditorManager::MoveTabRight(float DeltaTime)
{
	if (m_DragObj)
	{
		float	DragPosX = m_DragObj->GetEndPos().x;
		float	ResW = (float)CDevice::GetInst()->GetResolution().Width;

		if (DragPosX >= ResW)
			return;

		Vector2	Size = m_DragObj->GetStartPos() - m_DragObj->GetEndPos();
		float	ResultX = abs(Size.x);

		if (ResultX + DragPosX >= ResW)
			ResultX = ResW - DragPosX;

		m_DragObj->AddWorldPos(ResultX, 0.f, 0.f);

		Vector2	Result2D = Vector2(ResultX, 0.f);
		m_DragObj->AddStartPos(Result2D);
		m_DragObj->AddEndPos(Result2D);

		Vector3		RectPos = m_DragObj->GetWorldPos();
		Vector3		ImgSize = m_SpriteWindow->GetSpriteSize();
		Vector2		DragSize = m_DragObj->GetEndPos() - m_DragObj->GetStartPos();

		if (RectPos.x + DragSize.x > ImgSize.x)
			RectPos.x = ImgSize.x - DragSize.x;

		m_DragObj->SetWorldPos(RectPos);

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
	if (Type == typeid(CSceneComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CSceneComponent>();

		return Component;
	}

	else if (Type == typeid(CSpriteComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CSpriteComponent>();

		return Component;
	}

	else if (Type == typeid(CStaticMeshComponent).hash_code())
	{
		CComponent* Component = Obj->LoadComponent<CStaticMeshComponent>();

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