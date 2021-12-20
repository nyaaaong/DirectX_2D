#include "EditorManager.h"
#include "Engine.h"
#include "resource.h"
#include "Input.h"
#include "IMGUIManager.h"
#include "Scene/SceneManager.h"
#include "Scene/DefaultScene.h"
#include "Window/SpriteWindow.h"
#include "Window/DetailWindow.h"
#include "Window/EditorMenu.h"
#include "Window/ObjectHierarchy.h"
#include "Render/RenderManager.h"
#include "Object/SpriteEditObject.h"
#include "Object/DragObject.h"
#include "Component/SpriteComponent.h"

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

	CInput::GetInst()->CreateKey("TabUp", 'W');
	CInput::GetInst()->CreateKey("TabDown", 'S');
	CInput::GetInst()->CreateKey("TabLeft", 'A');
	CInput::GetInst()->CreateKey("TabRight", 'D');

	CInput::GetInst()->SetKeyCallback("TabUp", KeyState_Down, this, &CEditorManager::MoveTabUp);
	CInput::GetInst()->SetKeyCallback("TabDown", KeyState_Down, this, &CEditorManager::MoveTabDown);
	CInput::GetInst()->SetKeyCallback("TabLeft", KeyState_Down, this, &CEditorManager::MoveTabLeft);
	CInput::GetInst()->SetKeyCallback("TabRight", KeyState_Down, this, &CEditorManager::MoveTabRight);
}

bool CEditorManager::Init(HINSTANCE hInst)
{
	if (!CEngine::GetInst()->Init(hInst, TEXT("GameEngine"), 1280, 720, IDI_ICON1))
	{
		CEngine::DestroyInst();
		return false;
	}

	CInput::GetInst()->CreateKey("MouseClick", VK_LBUTTON);

	// IMGUI로 에디터에서 사용할 윈도우를 만들어준다.
	m_SpriteWindow = CIMGUIManager::GetInst()->AddWindow<CSpriteWindow>("SpriteWindow");
	m_DetailWindow = CIMGUIManager::GetInst()->AddWindow<CDetailWindow>("DetailWindow");
	m_EditorMenu = CIMGUIManager::GetInst()->AddWindow<CEditorMenu>("EditorMenu");
	m_ObjectHierarchy = CIMGUIManager::GetInst()->AddWindow<CObjectHierarchy>("ObjectHierarchy");

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

	if (m_SpriteWindow)
	{
		switch (m_SpriteWindow->GetCaptureMode())
		{
		case CM_CAPTURE:
			m_DragObj->SetStartPos(CInput::GetInst()->GetMousePos());
			break;
		case CM_DRAG:
		{
			Vector2	MousePos = CInput::GetInst()->GetMousePos();

			m_CurMousePos = Vector3(MousePos.x, MousePos.y, 0.f);
			m_PrevMousePos = m_CurMousePos;
		}
			break;
		}
	}
}

void CEditorManager::MouseLButtonPush(float DeltaTime)
{
	if (!m_DragObj)
		return;

	switch (m_SpriteWindow->GetCaptureMode())
	{
	case CM_CAPTURE:
	{
		m_DragObj->SetEndPos(CInput::GetInst()->GetMousePos());

		Vector2	StartPos = m_DragObj->GetStartPos();
		Vector2	EndPos = m_DragObj->GetEndPos();

		if (StartPos == EndPos)
			return;

		if (!m_SpriteWindow)
			return;

		// StartPos를 이미지에서의 위치로 변경한다.

		Vector2 Size = m_DragObj->GetEndPos() - m_DragObj->GetStartPos();
		Size.x = abs(Size.x);
		Size.y = abs(Size.y);

		Vector2 ConvertImagePos;
		ConvertImagePos.x = m_DragObj->GetStartPos().x - m_SpriteWindow->GetSpriteObject()->GetWorldPos().x;
		ConvertImagePos.y = m_SpriteWindow->GetSpriteObject()->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight() - (m_DragObj->GetStartPos().y - m_SpriteWindow->GetSpriteObject()->GetWorldPos().y);

		m_SpriteWindow->InputSize(Size);
		m_SpriteWindow->InputStartFrameData(ConvertImagePos);
		m_SpriteWindow->InputEndFrameData(ConvertImagePos + Size);
	}
		break;
	case CM_DRAG:
	{
		Vector2	MousePos = CInput::GetInst()->GetMousePos();
		m_CurMousePos = Vector3(MousePos.x, MousePos.y, 0.f);

		Vector3	DragLT = m_DragObj->GetWorldPos();
		Vector3	DragRB = DragLT + m_DragObj->GetWorldScale();

		if (DragLT.x < m_CurMousePos.x && DragLT.y > m_CurMousePos.y &&
			DragRB.x > m_CurMousePos.x && DragRB.y < m_CurMousePos.y)
		{
			m_DragObj->AddWorldPos(m_CurMousePos - m_PrevMousePos);
		}

		m_PrevMousePos = m_CurMousePos;
	}
		break;
	}

	
}

void CEditorManager::MouseLButtonUp(float DeltaTime)
{
}

void CEditorManager::KeyboardUp(float DeltaTime)
{
	if (m_DragObj)
		m_DragObj->AddWorldPos(0.f, 1.f, 0.f);
}

void CEditorManager::KeyboardDown(float DeltaTime)
{
	if (m_DragObj)
		m_DragObj->AddWorldPos(0.f, -1.f, 0.f);
}

void CEditorManager::KeyboardLeft(float DeltaTime)
{
	if (m_DragObj)
		m_DragObj->AddWorldPos(-1.f, 0.f, 0.f);
}

void CEditorManager::KeyboardRight(float DeltaTime)
{
	if (m_DragObj)
		m_DragObj->AddWorldPos(1.f, 0.f, 0.f);
}

void CEditorManager::MoveTabUp(float DeltaTime)
{
	if (m_DragObj)
	{
		Vector2	Size = m_DragObj->GetStartPos() - m_DragObj->GetEndPos();

		m_DragObj->AddWorldPos(0.f, abs(Size.y), 0.f);
	}
}

void CEditorManager::MoveTabDown(float DeltaTime)
{
	if (m_DragObj)
	{
		Vector2	Size = m_DragObj->GetStartPos() - m_DragObj->GetEndPos();

		m_DragObj->AddWorldPos(0.f, -abs(Size.y), 0.f);
	}
}

void CEditorManager::MoveTabLeft(float DeltaTime)
{
	if (m_DragObj)
	{
		Vector2	Size = m_DragObj->GetStartPos() - m_DragObj->GetEndPos();

		m_DragObj->AddWorldPos(-abs(Size.x), 0.f, 0.f);
	}
}

void CEditorManager::MoveTabRight(float DeltaTime)
{
	if (m_DragObj)
	{
		Vector2	Size = m_DragObj->GetStartPos() - m_DragObj->GetEndPos();

		m_DragObj->AddWorldPos(abs(Size.x), 0.f, 0.f);
	}
}
