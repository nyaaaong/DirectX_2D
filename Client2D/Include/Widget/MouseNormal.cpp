#include "MouseNormal.h"

CMouseNormal::CMouseNormal()
{
}

CMouseNormal::CMouseNormal(const CMouseNormal& window) :
    CWidgetWindow(window)
{
    m_Image = FindWidget<CImage>("Image");
}

CMouseNormal::~CMouseNormal()
{
}

void CMouseNormal::Start()
{
}

bool CMouseNormal::Init()
{
    if (!CWidgetWindow::Init())
        return false;

    SetSize(32.f, 31.f);

    m_Image = CreateWidget<CImage>("Image");

    std::vector<TCHAR*> vecFileName;

    for (int i = 0; i <= 12; ++i)
    {
        TCHAR* FileName = DBG_NEW TCHAR[MAX_PATH];
        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("Mouse/Default/%d.png"), i);

        vecFileName.push_back(FileName);
    }

    m_Image->SetTexture("MouseNormal", vecFileName);

    for (int i = 0; i <= 12; ++i)
    {
        SAFE_DELETE_ARRAY(vecFileName[i]);
    }

    return true;
}

void CMouseNormal::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);
}

void CMouseNormal::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CMouseNormal::Render()
{
    CWidgetWindow::Render();
}

CMouseNormal* CMouseNormal::Clone()
{
    return DBG_NEW CMouseNormal(*this);
}
