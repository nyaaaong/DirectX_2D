#pragma once

#include "Widget.h"

class CSliderBar :
    public CWidget
{
	friend class CWidgetWindow;

protected:
	CSliderBar();
	CSliderBar(const CSliderBar& widget);
	virtual ~CSliderBar();

protected:
	WidgetImageInfo	m_Info;

public:
	virtual void Enable(bool bEnable)
	{
		CWidget::Enable(bEnable);
	}

	void SetTexture(CTexture* Texture)
	{
		m_Info.Texture = Texture;

		SetUseTexture(true);
	}

	bool SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	bool SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void SetTextureTint(const Vector4& Tint);
	void SetTextureTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void AddFrameData(const Vector2& Start, const Vector2& Size);

public:
	virtual void Render();
	virtual CSliderBar* Clone();
};

