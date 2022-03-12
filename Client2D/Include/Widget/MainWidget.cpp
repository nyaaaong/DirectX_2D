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
	m_MouseXText = FindWidget<CText>("MouseXText");
	m_MouseYText = FindWidget<CText>("MouseYText");
	m_WorldMouseXText = FindWidget<CText>("WorldMouseXText");
	m_WorldMouseYText = FindWidget<CText>("WorldMouseYText");
	m_MouseDirXText = FindWidget<CText>("MouseDirXText");
	m_MouseDirYText = FindWidget<CText>("MouseDirYText");
	m_MouseAngleText = FindWidget<CText>("MouseAngleText");
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

	float	PosY = 720.f - 14.f;

	m_FPSText = CreateWidget<CText>("FPSText");
	m_FPSText->SetPos(0.f, PosY);
	m_FPSText->SetSize(300.f, 14.f);
	m_FPSText->SetZOrder(1);
	m_FPSText->SetColor(1.f, 1.f, 1.f);
	m_FPSText->SetAlignH(TEXT_ALIGN_H::Left);
	m_FPSText->SetShadowEnable(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);

#if _DEBUG

	PosY -= 14.f;

	m_MouseDirXText = CreateWidget<CText>("MouseDirXText");
	m_MouseDirXText->SetPos(0.f, PosY);
	m_MouseDirXText->SetSize(300.f, 14.f);
	m_MouseDirXText->SetZOrder(1);
	m_MouseDirXText->SetColor(1.f, 1.f, 1.f);
	m_MouseDirXText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseDirXText->SetShadowEnable(true);
	m_MouseDirXText->SetShadowOffset(2.f, 2.f);

	PosY -= 14.f;

	m_MouseDirYText = CreateWidget<CText>("MouseDirYText");
	m_MouseDirYText->SetPos(0.f, PosY);
	m_MouseDirYText->SetSize(300.f, 14.f);
	m_MouseDirYText->SetZOrder(1);
	m_MouseDirYText->SetColor(1.f, 1.f, 1.f);
	m_MouseDirYText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseDirYText->SetShadowEnable(true);
	m_MouseDirYText->SetShadowOffset(2.f, 2.f);

	PosY -= 14.f;

	m_MouseXText = CreateWidget<CText>("MouseXText");
	m_MouseXText->SetPos(0.f, PosY);
	m_MouseXText->SetSize(300.f, 14.f);
	m_MouseXText->SetZOrder(1);
	m_MouseXText->SetColor(1.f, 1.f, 1.f);
	m_MouseXText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseXText->SetShadowEnable(true);
	m_MouseXText->SetShadowOffset(2.f, 2.f);

	PosY -= 14.f;

	m_MouseYText = CreateWidget<CText>("MouseYText");
	m_MouseYText->SetPos(0.f, PosY);
	m_MouseYText->SetSize(300.f, 14.f);
	m_MouseYText->SetZOrder(1);
	m_MouseYText->SetColor(1.f, 1.f, 1.f);
	m_MouseYText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseYText->SetShadowEnable(true);
	m_MouseYText->SetShadowOffset(2.f, 2.f);

	PosY -= 14.f;

	m_WorldMouseXText = CreateWidget<CText>("WorldMouseXText");
	m_WorldMouseXText->SetPos(0.f, PosY);
	m_WorldMouseXText->SetSize(300.f, 14.f);
	m_WorldMouseXText->SetZOrder(1);
	m_WorldMouseXText->SetColor(1.f, 1.f, 1.f);
	m_WorldMouseXText->SetAlignH(TEXT_ALIGN_H::Left);
	m_WorldMouseXText->SetShadowEnable(true);
	m_WorldMouseXText->SetShadowOffset(2.f, 2.f);

	PosY -= 14.f;

	m_WorldMouseYText = CreateWidget<CText>("WorldMouseYText");
	m_WorldMouseYText->SetPos(0.f, PosY);
	m_WorldMouseYText->SetSize(300.f, 14.f);
	m_WorldMouseYText->SetZOrder(1);
	m_WorldMouseYText->SetColor(1.f, 1.f, 1.f);
	m_WorldMouseYText->SetAlignH(TEXT_ALIGN_H::Left);
	m_WorldMouseYText->SetShadowEnable(true);
	m_WorldMouseYText->SetShadowOffset(2.f, 2.f);

	PosY -= 14.f;

	m_MouseAngleText = CreateWidget<CText>("MouseAngleText");
	m_MouseAngleText->SetPos(0.f, PosY);
	m_MouseAngleText->SetSize(300.f, 14.f);
	m_MouseAngleText->SetZOrder(1);
	m_MouseAngleText->SetColor(1.f, 1.f, 1.f);
	m_MouseAngleText->SetAlignH(TEXT_ALIGN_H::Left);
	m_MouseAngleText->SetShadowEnable(true);
	m_MouseAngleText->SetShadowOffset(2.f, 2.f);
#endif // _DEBUG

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

#ifdef _DEBUG
	Vector2	UIMouse = CInput::GetInst()->GetMousePos();

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseX : %.f", UIMouse.x);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseXText->SetText(ConvertText);

	//

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseY : %.f", UIMouse.y);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseYText->SetText(ConvertText);

	//

	Vector2	WorldMouse = CInput::GetInst()->GetMouseWorld2DPos();

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "WorldMouseX : %.f", WorldMouse.x);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_WorldMouseXText->SetText(ConvertText);

	//

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "WorldMouseY : %.f", WorldMouse.y);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_WorldMouseYText->SetText(ConvertText);

	//

	CGameObject* Obj = m_Viewport->GetScene()->GetPlayerObject();
	CPlayer2D* Player = dynamic_cast<CPlayer2D*>(Obj);

	if (!Player)
		return;

	Vector3	Dir = Player->GetMouseDir();

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseDirX : %.2f", Dir.x);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseDirXText->SetText(ConvertText);

	//

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseDirY : %.2f", Dir.y);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseDirYText->SetText(ConvertText);

	//

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "MouseAngle : %.2f", Player->GetMouseAngle());

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_MouseAngleText->SetText(ConvertText);
#endif // _DEBUG
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
