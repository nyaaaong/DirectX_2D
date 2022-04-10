#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/ProgressBar.h"

class CPlayerWidget :
	public CWidgetWindow
{
	friend class CViewport;
	friend class CWidgetComponent;

protected:
	CPlayerWidget();
	CPlayerWidget(const CPlayerWidget& window);
	virtual ~CPlayerWidget();

private:
	CSharedPtr<CProgressBar>	m_HPBar;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CPlayerWidget* Clone();

public:
	void AddPercent(float Percent);
	void SetPercent(float Percent);
};

