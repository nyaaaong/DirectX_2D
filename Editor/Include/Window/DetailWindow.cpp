
#include "DetailWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "Engine.h"
#include "PathManager.h"
#include "../EditorManager.h"
#include "../Object/SpriteEditObject.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Component/SpriteComponent.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "../Object/DragObject.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Animation/AnimationSequence2DData.h"
#include "ObjectHierarchy.h"
#include "IMGUIManager.h"

CDetailWindow::CDetailWindow()	:
	m_PosX(nullptr),
	m_PosY(nullptr),
	m_PosZ(nullptr),
	m_RotX(nullptr),
	m_RotY(nullptr),
	m_RotZ(nullptr)
{
}

CDetailWindow::~CDetailWindow()
{
}

bool CDetailWindow::Init()
{
	CIMGUILabel* Label = nullptr;
	CIMGUISameLine* Line = nullptr;

	CIMGUIWindow::Init();

	Label = AddWidget<CIMGUILabel>("Transform", 98.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Label = AddWidget<CIMGUILabel>("Position", 60.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PosX = AddWidget<CIMGUITextInput>("PositionX", 60.f, 20.f);
	m_PosX->SetHideName(true);
	m_PosX->SetTextType(ImGuiText_Type::Float);
	m_PosX->SetCallback(this, &CDetailWindow::PositionXCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PosY = AddWidget<CIMGUITextInput>("PositionY", 60.f, 20.f);
	m_PosY->SetHideName(true);
	m_PosY->SetTextType(ImGuiText_Type::Float);
	m_PosY->SetCallback(this, &CDetailWindow::PositionYCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PosZ = AddWidget<CIMGUITextInput>("PositionZ", 60.f, 20.f);
	m_PosZ->SetHideName(true);
	m_PosZ->SetTextType(ImGuiText_Type::Float);
	m_PosZ->SetCallback(this, &CDetailWindow::PositionZCallback);

	Label = AddWidget<CIMGUILabel>("Rotation", 60.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_RotX = AddWidget<CIMGUITextInput>("RotationX", 60.f, 20.f);
	m_RotX->SetHideName(true);
	m_RotX->SetTextType(ImGuiText_Type::Float);
	m_RotX->SetCallback(this, &CDetailWindow::RotationXCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_RotY = AddWidget<CIMGUITextInput>("RotationY", 60.f, 20.f);
	m_RotY->SetHideName(true);
	m_RotY->SetTextType(ImGuiText_Type::Float);
	m_RotY->SetCallback(this, &CDetailWindow::RotationYCallback);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_RotZ = AddWidget<CIMGUITextInput>("RotationZ", 60.f, 20.f);
	m_RotZ->SetHideName(true);
	m_RotZ->SetTextType(ImGuiText_Type::Float);
	m_RotZ->SetCallback(this, &CDetailWindow::RotationZCallback);

	return true;
}

void CDetailWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CDetailWindow::PositionXCallback()
{
	CObjectHierarchy*	Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
		return;

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
		return;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
		return;

	Vector3	Pos = Obj->GetRootComponent()->GetWorldPos();

	Pos.x = m_PosX->GetValueFloat();

	Obj->GetRootComponent()->SetWorldPos(Pos);
}

void CDetailWindow::PositionYCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
		return;

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
		return;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
		return;

	Vector3	Pos = Obj->GetRootComponent()->GetWorldPos();

	Pos.y = m_PosY->GetValueFloat();

	Obj->GetRootComponent()->SetWorldPos(Pos);
}

void CDetailWindow::PositionZCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
		return;

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
		return;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
		return;

	Vector3	Pos = Obj->GetRootComponent()->GetWorldPos();

	Pos.z = m_PosZ->GetValueFloat();

	Obj->GetRootComponent()->SetWorldPos(Pos);
}


void CDetailWindow::RotationXCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
		return;

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
		return;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
		return;

	Vector3	Rot = Obj->GetRootComponent()->GetWorldRot();

	Rot.x = m_RotX->GetValueFloat();

	Obj->GetRootComponent()->SetWorldRotationX(Rot.x);
}

void CDetailWindow::RotationYCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
		return;

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
		return;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
		return;

	Vector3	Rot = Obj->GetRootComponent()->GetWorldRot();

	Rot.y = m_RotY->GetValueFloat();

	Obj->GetRootComponent()->SetWorldRotationY(Rot.y);
}

void CDetailWindow::RotationZCallback()
{
	CObjectHierarchy* Hierarchy = (CObjectHierarchy*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectHierarchy");

	if (!Hierarchy)
		return;

	CGameObject* Obj = nullptr;

	CIMGUIListBox* ObjList = Hierarchy->GetObjectList();

	if (ObjList->GetSelectIndex() == -1)
		return;

	Obj = CSceneManager::GetInst()->GetScene()->FindObject(ObjList->GetSelectItem());

	if (!Obj)
		return;

	Vector3	Rot = Obj->GetRootComponent()->GetWorldRot();

	Rot.z = m_RotZ->GetValueFloat();

	Obj->GetRootComponent()->SetWorldRotationZ(Rot.z);
}
