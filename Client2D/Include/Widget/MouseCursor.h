#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Image.h"

class CMouseCursor :
	public CWidgetWindow
{
	friend class CViewport;
	friend class CWidgetComponent;
	friend class CEngine;

protected:
	CMouseCursor();
	CMouseCursor(const CMouseCursor& window);
	virtual ~CMouseCursor();

private:
	CSharedPtr<CImage>	m_Image;
	bool	m_CheckTileInfo;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CMouseCursor* Clone();

private:
	void CameraUpdater(float DeltaTime);
};

