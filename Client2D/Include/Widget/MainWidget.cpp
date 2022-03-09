#include "MainWidget.h"
#include "Engine.h"
#include "Input.h"
#include "../Object/Player2D.h"
#include "Scene/ViewPort.h"
#include "Scene/Scene.h"

CMainWidget::CMainWidget()
{
}

CMainWidget::CMainWidget(const CMainWidget& window) :
	CWidgetWindow(window)
{
	m_FPSText = FindWidget<CText>("FPSText");
	m_MouseDirXText = FindWidget<CText>("MouseDirX");
	m_MouseDirYText = FindWidget<CText>("MouseDirY");
}


CMainWidget::~CMainWidget()
{
}

void CMainWidget::Start()
{
}

bool CMainWidget::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(1280.f, 720.f);

	m_FPSText = CreateWidget<CText>("FPSText");

	m_FPSText->SetPos(900.f, 650.f);
	m_FPSText->SetSize(300.f, 40.f);
	m_FPSText->SetZOrder(1);
	m_FPSText->SetColor(1.f, 1.f, 1.f);
	m_FPSText->SetAlignH(TEXT_ALIGN_H::Left);
	m_FPSText->SetShadowEnable(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);

	m_MouseDirXText = CreateWidget<CText>("MouseDirXText");

	m_MouseDirXText->SetPos(900.f, 620.f);
	m_MouseDirXText->SetSize(300.f, 40.f);
	m_MouseDirXText->SetZOrder(1);
	m_MouseDirXText->SetColor(1.f, 1.f, 1.f);
	m_MouseDirXText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseDirXText->SetShadowEnable(true);
	m_MouseDirXText->SetShadowOffset(2.f, 2.f);

	m_MouseDirYText = CreateWidget<CText>("MouseDirYText");

	m_MouseDirYText->SetPos(900.f, 590.f);
	m_MouseDirYText->SetSize(300.f, 40.f);
	m_MouseDirYText->SetZOrder(1);
	m_MouseDirYText->SetColor(1.f, 1.f, 1.f);
	m_MouseDirYText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseDirYText->SetShadowEnable(true);
	m_MouseDirYText->SetShadowOffset(2.f, 2.f);

	m_MouseXText = CreateWidget<CText>("MouseXText");

	m_MouseXText->SetPos(900.f, 560.f);
	m_MouseXText->SetSize(300.f, 40.f);
	m_MouseXText->SetZOrder(1);
	m_MouseXText->SetColor(1.f, 1.f, 1.f);
	m_MouseXText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseXText->SetShadowEnable(true);
	m_MouseXText->SetShadowOffset(2.f, 2.f);

	m_MouseYText = CreateWidget<CText>("MouseYText");

	m_MouseYText->SetPos(900.f, 530.f);
	m_MouseYText->SetSize(300.f, 40.f);
	m_MouseYText->SetZOrder(1);
	m_MouseYText->SetColor(1.f, 1.f, 1.f);
	m_MouseYText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseYText->SetShadowEnable(true);
	m_MouseYText->SetShadowOffset(2.f, 2.f);

	m_WorldMouseXText = CreateWidget<CText>("WorldMouseXText");

	m_WorldMouseXText->SetPos(900.f, 500.f);
	m_WorldMouseXText->SetSize(300.f, 40.f);
	m_WorldMouseXText->SetZOrder(1);
	m_WorldMouseXText->SetColor(1.f, 1.f, 1.f);
	m_WorldMouseXText->SetAlignH(TEXT_ALIGN_H::Left);
	m_WorldMouseXText->SetShadowEnable(true);
	m_WorldMouseXText->SetShadowOffset(2.f, 2.f);

	m_WorldMouseYText = CreateWidget<CText>("WorldMouseYText");

	m_WorldMouseYText->SetPos(900.f, 470.f);
	m_WorldMouseYText->SetSize(300.f, 40.f);
	m_WorldMouseYText->SetZOrder(1);
	m_WorldMouseYText->SetColor(1.f, 1.f, 1.f);
	m_WorldMouseYText->SetAlignH(TEXT_ALIGN_H::Left);
	m_WorldMouseYText->SetShadowEnable(true);
	m_WorldMouseYText->SetShadowOffset(2.f, 2.f);

	return true;
}

void CMainWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	char	Text[256] = {};
	sprintf_s(Text, "FPS : %.5f", CEngine::GetInst()->GetFPS());

	TCHAR   ConvertText[256] = {};

	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_FPSText->SetText(ConvertText);

	Vector2	UIMouse = CInput::GetInst()->GetMousePos();

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseX : %.f", UIMouse.x);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseXText->SetText(ConvertText);

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseY : %.f", UIMouse.y);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseYText->SetText(ConvertText);

	Vector2	WorldMouse = CInput::GetInst()->GetMouseWorld2DPos();

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "WorldMouseX : %.f", WorldMouse.x);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_WorldMouseXText->SetText(ConvertText);

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "WorldMouseY : %.f", WorldMouse.y);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_WorldMouseYText->SetText(ConvertText);

	CGameObject* Obj = m_Viewport->GetScene()->GetPlayerObject();
	CPlayer2D* Player = dynamic_cast<CPlayer2D*>(Obj);
	Vector3	Dir = Player->GetMouseDir();

	if (!Player)
		return;

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseDirX : %.3f", Dir.x);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseDirXText->SetText(ConvertText);

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseDirY : %.3f", Dir.y);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseDirYText->SetText(ConvertText);
}

void CMainWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CMainWidget::Render()
{
	CWidgetWindow::Render();
}

CMainWidget* CMainWidget::Clone()
{
	return DBG_NEW CMainWidget(*this);
}
