#include "LoadingWidget.h"
#include "Engine.h"
#include "../Scene/MainScene.h"
#include "Scene/SceneManager.h"

CLoadingWidget::CLoadingWidget()	:
	m_Percent(0.f)
{
}

CLoadingWidget::CLoadingWidget(const CLoadingWidget& window) :
    CWidgetWindow(window)
{
    m_Back = FindWidget<CImage>("Back");
	m_Loading = FindWidget<CImage>("Loading");

	m_Percent = 0.f;
}

CLoadingWidget::~CLoadingWidget()
{
}

void CLoadingWidget::Start()
{
	CWidgetWindow::Start();
}

bool CLoadingWidget::Init()
{
    if (!CWidgetWindow::Init())
        return false;

    SetSize(1280.f, 720.f);

    m_Back = CreateWidget<CImage>("Back");
	m_Loading = CreateWidget<CImage>("Loading");

    m_Back->SetTexture("LoadingBack", TEXT("Loading/LoadingScreen.png"));
    m_Back->SetSize(1280.f, 720.f);

	m_Loading->SetPos(1000.f, 150.f);
	m_Loading->SetSize(411.f * 0.7f, 431.f * 0.7f);
	m_Loading->SetPlayTime(2.f);

	std::vector<TCHAR*>	vecFileName;

	for (int i = 0; i < 34; ++i)
	{
		TCHAR* FileName = DBG_NEW TCHAR[MAX_PATH];
		memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

		wsprintf(FileName, TEXT("Loading/1-%d.png"), i);

		vecFileName.push_back(FileName);
	}

	m_Loading->SetTexture("Loading", vecFileName);
	m_Loading->AddFrameData(34);
	m_Loading->SetZOrder(1);

	for (int i = 0; i < 34; ++i)
	{
		SAFE_DELETE_ARRAY(vecFileName[i]);
	}


    return true;
}

void CLoadingWidget::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);
}

void CLoadingWidget::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CLoadingWidget::Render()
{
    CWidgetWindow::Render();
}

CLoadingWidget* CLoadingWidget::Clone()
{
    return DBG_NEW CLoadingWidget(*this);
}
