
#include "MainWidget.h"
#include "Engine.h"

CMainWidget::CMainWidget()	:
	m_Text{}
{
}

CMainWidget::CMainWidget(const CMainWidget& window) :
	CWidgetWindow(window)
{
	m_FPSText = FindWidget<CText>("FPSText");
	m_DebugText = FindWidget<CText>("DebugText");
	
	memset(m_Text, 0, sizeof(char) * 256);
}


CMainWidget::~CMainWidget()
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

	m_DebugText = CreateWidget<CText>("DebugText");
	m_DebugText->SetPos(0.f, PosY);
	m_DebugText->SetSize(300.f, 14.f);
	m_DebugText->SetZOrder(1);
	m_DebugText->SetColor(1.f, 1.f, 1.f);
	m_DebugText->SetAlignH(TEXT_ALIGN_H::Left);
	m_DebugText->SetShadowEnable(true);
	m_DebugText->SetShadowOffset(2.f, 2.f);

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

	//

	memset(Text, 0, sizeof(char) * 256);
	sprintf_s(Text, "%s", m_Text);

	memset(ConvertText, 0, sizeof(TCHAR) * 256);

	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, ConvertText, Length);

	m_DebugText->SetText(ConvertText);
#endif // _DEBUG
}

CMainWidget* CMainWidget::Clone()
{
	return DBG_NEW CMainWidget(*this);
}
