#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/ProgressBar.h"
#include "Widget/Image.h"

class CLoadingWidget :
    public CWidgetWindow
{
	friend class CViewport;

protected:
	CLoadingWidget();
	CLoadingWidget(const CLoadingWidget& window);
	virtual ~CLoadingWidget();

private:
	CSharedPtr<CImage>	m_Back;
	CSharedPtr<CImage>	m_Loading;
	float	m_Percent;

public:
	void SetLoadingPercent(float Percent)
	{
		m_Percent = Percent;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CLoadingWidget* Clone();
};

