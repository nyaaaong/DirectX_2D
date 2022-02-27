#include "IMGUITestWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUITextInput.h"
#include "IMGUICheckBox.h"
#include "IMGUIRadio.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUIImage.h"
#include "IMGUITree.h"

CIMGUITestWindow::CIMGUITestWindow()	:
	m_CheckBoxValue1(true),
	m_CheckBoxValue2(false),
	m_RadioValue(0),
	m_CB1(nullptr),
	m_CB2(nullptr),
	m_Radio1(nullptr),
	m_Radio2(nullptr),
	m_Radio3(nullptr),
	m_Tree(nullptr)
{
}

CIMGUITestWindow::~CIMGUITestWindow()
{
}

bool CIMGUITestWindow::Init()
{
	CIMGUIWindow::Init();

	CIMGUIButton*		Button = nullptr;
	CIMGUISameLine*		Line = nullptr;
	CIMGUILabel*		Label = nullptr;
	CIMGUIText*			Text = nullptr;
	CIMGUIListBox*		ListBox = nullptr;
	CIMGUIComboBox*		ComboBox = nullptr;
	CIMGUIImage*		Image = nullptr;
	CIMGUITextInput*	TextInput = nullptr;
	CIMGUITree*			Tree = nullptr;

	Button = AddWidget<CIMGUIButton>("Button1");
	Button->SetClickCallback<CIMGUITestWindow>(this, &CIMGUITestWindow::ClickButton1);

	Line = AddWidget<CIMGUISameLine>("Line");
	Line->SetOffsetX(200.f);
	Line->SetSpacing(100.f);

	Button = AddWidget<CIMGUIButton>("Button2", 100.f, 30.f);
	Button->SetClickCallback<CIMGUITestWindow>(this, &CIMGUITestWindow::ClickButton2);

	Label = AddWidget<CIMGUILabel>("Test", 100.f, 30.f);
	Label->SetColor(255, 0, 0);
	Label->SetAlign(0.5f, 0.f);

	Line = AddWidget<CIMGUISameLine>("Line");

	Text = AddWidget<CIMGUIText>("Text", 100.f, 30.f);
	Text->SetText("«—±€∆–ƒ° º∫∞¯");
	Text->SetColor(255, 255, 0);

	ListBox = AddWidget<CIMGUIListBox>("ListBox", 200.f, 30.f);
	ListBox->SetHideName(true);

	ListBox->AddItem("∆º∏");
	ListBox->AddItem("∞°∫ÿ¿Ã");
	ListBox->AddItem("øÏ∫ÿ¿Ã");
	ListBox->AddItem("øÏ∫ÿ¿Ã1");

	ComboBox = AddWidget<CIMGUIComboBox>("ComboBox", 200.f, 30.f);
	ComboBox->SetHideName(true);
	ComboBox->AddItem("∆º∏");
	ComboBox->AddItem("∞°∫ÿ¿Ã");
	ComboBox->AddItem("øÏ∫ÿ¿Ã");

	Image = AddWidget<CIMGUIImage>("Image", 200.f, 200.f);
	Image->SetTexture("TeemoTest", TEXT("Teemo.jpg"));
	Image->SetImageStart(0.f, 0.f);
	Image->SetImageEnd(1215.f, 717.f);
	Image->SetTint(255, 0, 0);

	TextInput = AddWidget<CIMGUITextInput>("TextInput", 200.f, 30.f);
	TextInput->SetHideName(true);

	m_Tree = AddWidget<CIMGUITree>("Tree1");
	m_Tree->SetOpenCallback<CIMGUITestWindow>(this, &CIMGUITestWindow::OpenTree);
	m_Tree->SetCloseCallback<CIMGUITestWindow>(this, &CIMGUITestWindow::CloseTree);

	//

	m_CB1 = AddWidget<CIMGUICheckBox>("CheckBox1", 100.f, 100.f);
	m_CB1->CheckBox(&m_CheckBoxValue1);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_CB2 = AddWidget<CIMGUICheckBox>("CheckBox2", 100.f, 100.f);
	m_CB2->CheckBox(&m_CheckBoxValue2);

	//

	m_Radio1 = AddWidget<CIMGUIRadio>("Radio1");
	m_Radio1->RadioButton(&m_RadioValue, RT_NONE);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_Radio2 = AddWidget<CIMGUIRadio>("Radio2");
	m_Radio2->RadioButton(&m_RadioValue, RT_TEST);

	Line = AddWidget<CIMGUISameLine>("Line");

	m_Radio3 = AddWidget<CIMGUIRadio>("Radio3");
	m_Radio3->RadioButton(&m_RadioValue, RT_MAX);

	return true;
}

void CIMGUITestWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CIMGUITestWindow::ClickButton1()
{
	MessageBox(0, TEXT("aa"), TEXT("aa"), MB_OK);
}

void CIMGUITestWindow::ClickButton2()
{
	MessageBox(0, TEXT("bb"), TEXT("bb"), MB_OK);
}

void CIMGUITestWindow::OpenTree()
{
	m_CB1->Enable();
	m_CB2->Enable();

	m_Radio1->Enable();
	m_Radio2->Enable();
	m_Radio3->Enable();
}

void CIMGUITestWindow::CloseTree()
{
	m_CB1->Disable();
	m_CB2->Disable();

	m_Radio1->Disable();
	m_Radio2->Disable();
	m_Radio3->Disable();
}

