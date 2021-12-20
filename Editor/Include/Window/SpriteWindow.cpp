#include "SpriteWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "IMGUIRadio.h"
#include "Engine.h"
#include "Input.h"
#include "PathManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneResource.h"
#include "Component/SpriteComponent.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "Animation/AnimationSequence2DInstance.h"
#include "Animation/AnimationSequence2DData.h"
#include "../EditorManager.h"
#include "../Object/DragObject.h"
#include "../Object/SpriteEditObject.h"

CSpriteWindow::CSpriteWindow()  :
	m_Sprite(nullptr),
	m_SpriteFrame(nullptr),
	m_SpriteObject(nullptr),
	m_AnimationList(nullptr),
	m_AnimationFrameList(nullptr),
	m_AnimName(nullptr),
	m_AnimFrameName(nullptr),
	m_Capture(nullptr),
	m_Drag(nullptr),
	m_AnimInstance(nullptr),
	m_AnimSizeX(nullptr),
	m_AnimSizeY(nullptr),
	m_AnimStartFrameX(nullptr),
	m_AnimStartFrameY(nullptr),
	m_AnimEndFrameX(nullptr),
	m_AnimEndFrameY(nullptr),
	m_PlayAnimButton(nullptr),
	m_PlayAnim(false),
	m_Mode(0)
{
}

CSpriteWindow::~CSpriteWindow()
{
	SAFE_DELETE(m_AnimInstance);
}

bool CSpriteWindow::Init()
{
	if (!CIMGUIWindow::Init())
		return false;

	CIMGUIButton*	Button = nullptr;
	CIMGUISameLine*	Line = nullptr;
	CIMGUILabel*	Label = nullptr;
	CIMGUIText*		Text = nullptr;

	Button = AddWidget<CIMGUIButton>("LoadTexture", 200.f, 20.f);
	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::LoadTextureButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("SaveSequence", 100.f, 20.f);
	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::SaveSequence);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("LoadSequence", 92.f, 20.f);
	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::LoadSequence);

	Label = AddWidget<CIMGUILabel>("EditMode", 200.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("AnimationFramePosition", 200.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	m_Capture = AddWidget<CIMGUIRadio>("Capture", 40.f, 20.f);
	m_Capture->RadioButton(&m_Mode, EM_CAPTURE);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetSpacing(73.f);

	m_Drag = AddWidget<CIMGUIRadio>("Drag", 40.f, 20.f);
	m_Drag->RadioButton(&m_Mode, EM_DRAG);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("StartX", 40.f, 20.f);
	Label->SetColor(15, 15, 15);
	Label->SetAlign(1.f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimStartFrameX = AddWidget<CIMGUITextInput>("StartXInput", 40.f, 20.f);
	m_AnimStartFrameX->SetHideName();
	m_AnimStartFrameX->AddFlag(ImGuiInputTextFlags_CharsDecimal); // ���ڿ� - �� ��ȣ������ �Է�
	//m_AnimStartFrameX->ReadOnly()

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetSpacing(20.f);

	Label = AddWidget<CIMGUILabel>("StartY", 40.f, 20.f);
	Label->SetColor(15, 15, 15);
	Label->SetAlign(1.f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetSpacing(12.f);

	m_AnimStartFrameY = AddWidget<CIMGUITextInput>("StartYInput", 40.f, 20.f);
	m_AnimStartFrameY->SetHideName();
	m_AnimStartFrameY->AddFlag(ImGuiInputTextFlags_CharsDecimal); // ���ڿ� - �� ��ȣ������ �Է�
	//m_AnimFrameX->ReadOnly()

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("Modify", 80.f, 20.f);
	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::Modify);

	Label = AddWidget<CIMGUILabel>("SizeX", 40.f, 20.f);
	Label->SetColor(15, 15, 15);
	Label->SetAlign(1.f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimSizeX = AddWidget<CIMGUITextInput>("SizeXInput", 40.f, 20.f);
	m_AnimSizeX->SetHideName();
	m_AnimSizeX->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_AnimSizeX->ReadOnly();

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetSpacing(24.f);

	Label = AddWidget<CIMGUILabel>("SizeY", 40.f, 20.f);
	Label->SetColor(15, 15, 15);
	Label->SetAlign(1.f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimSizeY = AddWidget<CIMGUITextInput>("SizeYInput", 40.f, 20.f);
	m_AnimSizeY->SetHideName();
	m_AnimSizeY->AddFlag(ImGuiInputTextFlags_CharsDecimal);
	m_AnimSizeY->ReadOnly();

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetSpacing(8.f);

	Label = AddWidget<CIMGUILabel>("EndX", 40.f, 20.f);
	Label->SetColor(15, 15, 15);
	Label->SetAlign(1.f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimEndFrameX = AddWidget<CIMGUITextInput>("EndXInput", 40.f, 20.f);
	m_AnimEndFrameX->SetHideName();
	m_AnimEndFrameX->AddFlag(ImGuiInputTextFlags_CharsDecimal); // ���ڿ� - �� ��ȣ������ �Է�
	//m_AnimEndFrameX->ReadOnly()

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetSpacing(24.f);

	Label = AddWidget<CIMGUILabel>("EndY", 40.f, 20.f);
	Label->SetColor(15, 15, 15);
	Label->SetAlign(1.f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimEndFrameY = AddWidget<CIMGUITextInput>("EndYInput", 40.f, 20.f);
	m_AnimEndFrameY->SetHideName();
	m_AnimEndFrameY->AddFlag(ImGuiInputTextFlags_CharsDecimal); // ���ڿ� - �� ��ȣ������ �Է�
	//m_AnimEndFrameY->ReadOnly()

	Label = AddWidget<CIMGUILabel>("AnimationListName", 200.f, 20.f);
	Label->SetColor(31, 81, 150);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Label = AddWidget<CIMGUILabel>("AnimationFrameName", 200.f, 20.f);
	Label->SetColor(31, 81, 183);
	Label->SetAlign(0.5f, 0.f);

	m_AnimationList = AddWidget<CIMGUIListBox>("AnimationList", 200.f, 300.f);
	m_AnimationList->SetHideName(true);
	m_AnimationList->SetPageItemCount(6);
	m_AnimationList->SetSelectCallback<CSpriteWindow>(this, &CSpriteWindow::SelectAnimation);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimationFrameList = AddWidget<CIMGUIListBox>("AnimationFrameList", 200.f, 300.f);
	m_AnimationFrameList->SetHideName(true);
	m_AnimationFrameList->SetPageItemCount(6);
	m_AnimationFrameList->SetSelectCallback<CSpriteWindow>(this, &CSpriteWindow::SelectAnimationFrame);

	m_AnimName = AddWidget<CIMGUITextInput>("AnimNameInput", 200.f, 20.f);
	m_AnimName->SetHideName(true);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_AnimFrameName = AddWidget<CIMGUITextInput>("AnimFrameNameInput", 200.f, 20.f);
	m_AnimFrameName->SetHideName(true);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_PlayAnimButton = AddWidget<CIMGUIButton>("AnimPlay", 80.f, 20.f);
	m_PlayAnimButton->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::PlayAnimation);

	Button = AddWidget<CIMGUIButton>("AddAnim", 100.f, 20.f);
	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::AddAnimationButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("DeleteAnim", 92.f, 20.f);
	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::DeleteAnimationButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("AddFrame", 100.f, 20.f);
	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::AddAnimationFrameButton);

	Line = AddWidget<CIMGUISameLine>("Line");

	Button = AddWidget<CIMGUIButton>("DeleteFrame", 92.f, 20.f);
	Button->SetClickCallback<CSpriteWindow>(this, &CSpriteWindow::DeleteFrameButton);

	m_Sprite = AddWidget<CIMGUIImage>("Sprite", 200.f, 200.f);
	m_Sprite->SetTexture("Teemo", TEXT("teemo.png"));

	Line = AddWidget<CIMGUISameLine>("Line");

	m_SpriteFrame = AddWidget<CIMGUIImage>("SpriteFrame", 200.f, 200.f);

	m_AnimInstance = DBG_NEW CAnimationSequence2DInstance;

	m_AnimInstance->Init();
	m_AnimInstance->Stop();

	return true;
}

void CSpriteWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);

	m_AnimInstance->Update(DeltaTime);

	if (m_AnimInstance->IsPlay())
	{
		CAnimationSequence2DData* AnimData = m_AnimInstance->GetCurrentAnimation();

		if (AnimData)
		{
			int Frame = AnimData->GetCurrentFrame();

			AnimationFrameData  FrameData = AnimData->GetAnimationSequence()->GetFrameData(Frame);

			m_SpriteFrame->SetImageStart(FrameData.Start.x, FrameData.Start.y);

			m_SpriteFrame->SetImageEnd(FrameData.Start.x + FrameData.Size.x, FrameData.Start.y + FrameData.Size.y);
		}
	}

	EditMode();

}

void CSpriteWindow::LoadTextureButton()
{
	if (CEditorManager::GetInst()->GetEditMode() != EditMode::Sprite)
		return;

	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("�׸����� (*.dds, *.tga, *.png, *.jpg, *.jpeg, *.bmp)\0*.dds;*.tga;*.png;*.jpg;*.jpeg;*.bmp\0DDS (*.dds)\0*.dds\0TGA (*.tga)\0*.tga\0PNG (*.png)\0*.png\0JPG (*.jpg)\0*.jpg\0JPEG (*.jpeg)\0*.jpeg\0BMP (*.bmp)\0*.bmp");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		TCHAR   FileName[MAX_PATH] = {};

		_wsplitpath_s(FilePath, 0, 0, 0, 0, FileName, MAX_PATH, 0, 0);

		char    ConvertFileName[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FileName, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FileName, -1, ConvertFileName, Length, 0, 0);

		m_Sprite->SetTextureFullPath(ConvertFileName, FilePath);

		m_SpriteObject->GetSpriteComponent()->SetTextureFullPath(0, 0, (int)ConstantBuffer_Shader_Type::Pixel,  ConvertFileName, FilePath);

		m_SpriteObject->GetSpriteComponent()->SetWorldScale((float)m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTextureWidth(), 
			(float)m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTextureHeight(), 1.f);
	}
}

bool CSpriteWindow::Start()
{
	if (!CIMGUIWindow::Start())
		return false;

	CEditorManager::GetInst()->SetEditMode(EditMode::Sprite);

	if (!m_SpriteObject)
		m_SpriteObject = CSceneManager::GetInst()->GetScene()->CreateGameObject<CSpriteEditObject>("SpriteEditObject");

	return true;
}

void CSpriteWindow::AddAnimationButton()
{
	if (m_AnimName->Empty())
		return;

	const char* Text = m_AnimName->GetTextMultibyte();

	if (m_AnimationList->CheckItem(Text))
		return;

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	if (!Resource->CreateAnimationSequence2D(Text, m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()))
		return;

	m_AnimationList->AddItem(Text);

	m_AnimInstance->AddAnimation(Text, Text, true, 1.f, 1.f, false);
}

void CSpriteWindow::AddAnimationFrameButton()
{
	int SelectIndex = m_AnimationList->GetSelectIndex();

	if (SelectIndex == -1)
		return;

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(m_AnimationList->GetItem(SelectIndex));

	CDragObject* DragObj = CEditorManager::GetInst()->GetDragObj();

	Vector2 Size = DragObj->GetEndPos() - DragObj->GetStartPos();
	Size.x = abs(Size.x);
	Size.y = abs(Size.y);

	// StartPos�� �̹��������� ��ġ�� �����Ѵ�.

	Vector2 ConvertImagePos;
	ConvertImagePos.x = DragObj->GetStartPos().x - m_SpriteObject->GetWorldPos().x;
	ConvertImagePos.y = m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight() - (DragObj->GetStartPos().y - m_SpriteObject->GetWorldPos().y);

	Anim->AddFrame(ConvertImagePos, Size);

	int FrameCount = Anim->GetFrameCount() - 1;

	char    FrameName[32] = {};
	sprintf_s(FrameName, "%d", FrameCount);

	m_AnimationFrameList->AddItem(FrameName);

	m_SpriteFrame->SetTexture(m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture());

	Vector2 ImageStartPos = DragObj->GetStartPos();
	Vector2 ImageEndPos = DragObj->GetEndPos();

	ImageStartPos.x -= m_SpriteObject->GetWorldPos().x;
	ImageStartPos.y -= m_SpriteObject->GetWorldPos().y;

	ImageEndPos.x -= m_SpriteObject->GetWorldPos().x;
	ImageEndPos.y -= m_SpriteObject->GetWorldPos().y;

	ImageEndPos.y = m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight() - ImageEndPos.y;
	ImageStartPos.y = m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight() - ImageStartPos.y;

	Vector2 StartPos, EndPos;
	StartPos.x = ImageStartPos.x < ImageEndPos.x ? ImageStartPos.x : ImageEndPos.x;
	StartPos.y = ImageStartPos.y < ImageEndPos.y ? ImageStartPos.y : ImageEndPos.y;

	EndPos.x = ImageStartPos.x > ImageEndPos.x ? ImageStartPos.x : ImageEndPos.x;
	EndPos.y = ImageStartPos.y > ImageEndPos.y ? ImageStartPos.y : ImageEndPos.y;

	m_SpriteFrame->SetImageStart(StartPos.x, StartPos.y);
	m_SpriteFrame->SetImageEnd(EndPos.x, EndPos.y);
}

void CSpriteWindow::EditMode()
{
	if (m_Mode == EM_CAPTURE)
	{
		m_AnimSizeX->ReadOnly();
		m_AnimSizeY->ReadOnly();
	}

	else
	{
		m_AnimSizeX->ReadOnly(false);
		m_AnimSizeY->ReadOnly(false);
	}
}

void CSpriteWindow::Modify()
{
	int SelectFrameIndex = m_AnimationFrameList->GetSelectIndex();

	if (SelectFrameIndex == -1)
		return;

	int SelectAnimIndex = m_AnimationList->GetSelectIndex();

	if (SelectAnimIndex == -1)
		return;

	if (m_AnimStartFrameX->Empty() || m_AnimStartFrameY->Empty() ||
		m_AnimEndFrameX->Empty() || m_AnimEndFrameY->Empty())
		return;

	float StartX = static_cast<float>(atoi(m_AnimStartFrameX->GetTextMultibyte()));
	float StartY = static_cast<float>(atoi(m_AnimStartFrameY->GetTextMultibyte()));
	float EndX = static_cast<float>(atoi(m_AnimEndFrameX->GetTextMultibyte()));
	float EndY = static_cast<float>(atoi(m_AnimEndFrameY->GetTextMultibyte()));

	float SizeX = abs(StartX - EndX);
	float SizeY = abs(StartY - EndY);

	m_AnimSizeX->SetText(SizeX);
	m_AnimSizeY->SetText(SizeY);

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(m_AnimationList->GetItem(SelectAnimIndex));

	Anim->SetFrameData(SelectFrameIndex, Vector2(StartX, StartY), Vector2(SizeX, SizeY));

	m_SpriteFrame->SetImageStart(StartX, StartY);
	m_SpriteFrame->SetImageEnd(EndX, EndY);

	CDragObject* DragObject = CEditorManager::GetInst()->GetDragObj();

	DragObject->SetStartPos(Vector2(StartX, StartY));
	DragObject->SetEndPos(Vector2(EndX, EndY));
}

void CSpriteWindow::DeleteAnimation(const std::string& SequenceName)
{
	int Index = m_AnimationList->GetItemIndex(SequenceName);

	if (Index == -1)
		return;

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(SequenceName);

	Resource->ReleaseAnimationSequence2D(SequenceName);

	m_AnimationList->DeleteItem(Index);

	m_AnimInstance->DeleteAnimation(SequenceName);

	int MaxIndex = m_AnimationList->GetItemCount();

	if (Index < MaxIndex)
	{
		std::string NextData = m_AnimationList->GetItem(Index);

		SelectAnimation(Index, NextData.c_str());
	}

	else
	{
		m_AnimationList->SetSelectIndex(-1);

		m_AnimationFrameList->Clear();
	}
}

void CSpriteWindow::DeleteAnimationButton()
{
	int SelectAnimIndex = m_AnimationList->GetSelectIndex();

	if (SelectAnimIndex == -1)
		return;

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(m_AnimationList->GetItem(SelectAnimIndex));

	std::string AnimName = Anim->GetName();

	Resource->ReleaseAnimationSequence2D(AnimName);

	Anim->ClearFrame();

	m_AnimationList->DeleteItem(SelectAnimIndex);

	m_AnimInstance->DeleteAnimation(AnimName);

	int MaxIndex = m_AnimationList->GetItemCount();

	if (SelectAnimIndex < MaxIndex)
	{
		std::string NextData = m_AnimationList->GetItem(SelectAnimIndex);

		SelectAnimation(SelectAnimIndex, NextData.c_str());
	}

	else
	{
		m_AnimationList->SetSelectIndex(-1);

		m_AnimationFrameList->Clear();
	}
}

void CSpriteWindow::DeleteFrameButton()
{
	int SelectFrameIndex = m_AnimationFrameList->GetSelectIndex();

	if (SelectFrameIndex == -1)
		return;

	int SelectAnimIndex = m_AnimationList->GetSelectIndex();

	if (SelectAnimIndex == -1)
		return;

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(m_AnimationList->GetItem(SelectAnimIndex));

	Anim->DeleteFrame(SelectFrameIndex);

	m_AnimationFrameList->DeleteItem(SelectFrameIndex);

	int MaxIndex = m_AnimationFrameList->GetItemCount() - 1;

	if (SelectFrameIndex < MaxIndex)
	{
		std::string NextData = m_AnimationFrameList->GetItem(SelectFrameIndex);

		SelectAnimationFrame(SelectFrameIndex, NextData.c_str());
	}

	else
		m_AnimationFrameList->SetSelectIndex(-1);
}

void CSpriteWindow::SelectAnimation(int Index, const char* Item)
{
	if (!m_AnimInstance)
		ASSERT("if (!m_AnimInstance)");

	m_AnimInstance->SetCurrentAnimation(Item);

	int FrameCount = m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetFrameCount();

	m_AnimationFrameList->Clear();

	for (int i = 0; i < FrameCount; ++i)
	{
		char    FrameName[32] = {};
		sprintf_s(FrameName, "%d", i);
		m_AnimationFrameList->AddItem(FrameName);
	}

	m_SpriteFrame->SetTexture(m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetTexture());

	if (FrameCount > 0)
	{
		AnimationFrameData  Data = m_AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetFrameData(Index);

		m_SpriteFrame->SetImageStart(Data.Start.x, Data.Start.y);

		m_SpriteFrame->SetImageEnd(Data.Start.x + Data.Size.x, Data.Start.y + Data.Size.y);
	}
}

void CSpriteWindow::SelectAnimationFrame(int Index, const char* Item)
{
	if (Index == -1)
		return;

	int SelectIndex = m_AnimationList->GetSelectIndex();

	if (SelectIndex == -1)
		return;

	CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

	CAnimationSequence2D* Anim = Resource->FindAnimationSequence2D(m_AnimationList->GetItem(SelectIndex));

	AnimationFrameData  Data = Anim->GetFrameData(Index);

	m_SpriteFrame->SetImageStart(Data.Start.x, Data.Start.y);
	m_SpriteFrame->SetImageEnd(Data.Start.x + Data.Size.x, Data.Start.y + Data.Size.y);

	Vector2	StartPos = m_SpriteFrame->GetImageStart();
	Vector2	EndPos = m_SpriteFrame->GetImageEnd();

	CDragObject* DragObject = CEditorManager::GetInst()->GetDragObj();

	float   ImageHeight = (float)m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight();

	StartPos.x = Data.Start.x + m_SpriteObject->GetWorldPos().x;
	StartPos.y = ImageHeight - Data.Start.y + m_SpriteObject->GetWorldPos().y;

	EndPos.x = StartPos.x + Data.Size.x;
	EndPos.y = StartPos.y - Data.Size.y;

	DragObject->SetStartPos(StartPos);
	DragObject->SetEndPos(EndPos);

	// StartPos�� �̹��������� ��ġ�� �����Ѵ�.

	Vector2 Size = DragObject->GetEndPos() - DragObject->GetStartPos();
	Size.x = abs(Size.x);
	Size.y = abs(Size.y);

	Vector2 ConvertImagePos;
	ConvertImagePos.x = DragObject->GetStartPos().x - m_SpriteObject->GetWorldPos().x;
	ConvertImagePos.y = m_SpriteObject->GetSpriteComponent()->GetMaterial()->GetTexture()->GetHeight() - (DragObject->GetStartPos().y - m_SpriteObject->GetWorldPos().y);

	InputSize(Size);
	InputStartFrameData(ConvertImagePos);
	InputEndFrameData(ConvertImagePos + Size);
}

void CSpriteWindow::PlayAnimation()
{
	if (!m_SpriteObject)
		return;

	if (!m_PlayAnim)
	{
		m_PlayAnim = true;

		m_PlayAnimButton->SetName("AnimStop");
		m_AnimInstance->Play();
	}

	else
	{
		m_PlayAnim = false;

		m_PlayAnimButton->SetName("AnimPlay");
		m_AnimInstance->Stop();
	}
}

void CSpriteWindow::InputSize(const Vector2& size)
{
	m_AnimSizeX->SetText(size.x);
	m_AnimSizeY->SetText(size.y);
}

void CSpriteWindow::InputStartFrameData(const Vector2& Data)
{
	m_AnimStartFrameX->SetText(Data.x);
	m_AnimStartFrameY->SetText(Data.y);
}

void CSpriteWindow::InputEndFrameData(const Vector2& Data)
{
	m_AnimEndFrameX->SetText(Data.x);
	m_AnimEndFrameY->SetText(Data.y);
}

void CSpriteWindow::SaveSequence()
{
	int SelectAnimIndex = m_AnimationList->GetSelectIndex();

	if (SelectAnimIndex == -1)
		return;

	int SelectFrameIndex = m_AnimationFrameList->GetItemCount();

	if (SelectFrameIndex == 0)
		return;

	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("Sequence (*.sqc)\0*.sqc");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(ANIMATION_PATH)->Path;

	if (GetSaveFileName(&OpenFile) != 0)
	{
		// .sqc�� �پ����� Ȯ��
		int	iPathLength = static_cast<int>(lstrlen(FilePath));

		TCHAR	sqc[5] = TEXT("cqs.");
		bool	Find = true;

		for (int i = 1; i < 5; ++i)
		{
			if (FilePath[iPathLength - i] != sqc[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // anm Ȯ���ڰ� ���� �ʾ��� ��� �ٿ��ش�.
			lstrcat(FilePath, TEXT(".sqc"));

		char    FullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, FullPath, Length, 0, 0);

		FILE* File = nullptr;

		fopen_s(&File, FullPath, "wb");

		if (!File)
			ASSERT("if (!File)");

		m_AnimInstance->Save(File, FullPath);

		fclose(File);
	}
}

void CSpriteWindow::LoadSequence()
{
	TCHAR   FilePath[MAX_PATH] = {};

	OPENFILENAME    OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	OpenFile.lpstrFilter = TEXT("Sequence (*.sqc)\0*.sqc");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(ANIMATION_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		// .sqc�� �پ����� Ȯ��
		int	iPathLength = static_cast<int>(lstrlen(FilePath));

		TCHAR	anm[5] = TEXT("cqs.");
		bool	Find = true;

		for (int i = 1; i < 5; ++i)
		{
			if (FilePath[iPathLength - i] != anm[i - 1])
			{
				Find = false;
				break;
			}
		}

		if (!Find) // sqc Ȯ���ڰ� ���� �ʾ��� ��� �ٿ��ش�.
			lstrcat(FilePath, TEXT(".cqs"));

		char    FullPath[MAX_PATH] = {};

		int Length = WideCharToMultiByte(CP_ACP, 0, FilePath, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, FilePath, -1, FullPath, Length, 0, 0);

		CSceneResource* Resource = CSceneManager::GetInst()->GetScene()->GetResource();

		std::string	SequenceName;

		FILE* File = nullptr;

		fopen_s(&File, FullPath, "rb");

		if (!File)
			ASSERT("if (!File)");

		if (!Resource->LoadSequence2D(File, m_AnimationFrameList, SequenceName, FullPath))
			fclose(File);

		else
		{
			// ������ ����Ʈ�ڽ� ���
			m_AnimationList->AddItem(SequenceName);

			// ������ ����Ʈ�ڽ� ���
			m_AnimInstance->Load(File, SequenceName, m_AnimationFrameList, FullPath);

			fclose(File);

			int Index = m_AnimationFrameList->GetItemIndex(SequenceName);

			if (Index == -1)
				Index = 0;

			SelectAnimation(Index, SequenceName.c_str());
		}
	}
}