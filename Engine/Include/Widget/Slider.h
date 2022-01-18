#pragma once
#include "Widget.h"
class CSlider :
    public CWidget
{
	friend class CWidgetWindow;

protected:
	CSlider();
	CSlider(const CSlider& widget);
	virtual ~CSlider();

protected:
	WidgetImageInfo	m_Info;
	std::function<void(float)>	m_SliderCallback;
	float	m_PrevMousePosX;
	float	m_CurMousePosX;
	float	m_SliderBarMin;
	float	m_SliderBarMax;
	float	m_Value;
	float	m_Gap;
	bool	m_CheckSliderInClick;
	bool	m_CheckSliderOutClick;

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
	bool SetTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
	bool SetTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath);
	void SetTextureTint(const Vector4& Tint);
	void SetTextureTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void AddFrameData(const Vector2& Start, const Vector2& Size);
	void SetPlayTime(float PlayTime);
	void SetPlayScale(float PlayScale);

public:
	virtual void Update(float DeltaTime);
	virtual void Render();
	virtual CSlider* Clone();

public:
	template <typename T>
	void SetSliderInfo(T* SliderBar)
	{
		// 슬라이더 바의 중간부분에 슬라이더를 위치하게 한다.
		float	SliderBarCenter = SliderBar->GetWindowPos().y + (SliderBar->GetWindowSize().y * 0.5f);
		
		m_Pos = Vector2(SliderBar->GetWindowPos().x, SliderBarCenter);
		m_Pos.y -= (m_Size.y * 0.5f);

		m_SliderBarMin = SliderBar->GetWindowPos().x;
		m_SliderBarMax = m_SliderBarMin + SliderBar->GetWindowSize().x - m_Size.x;
	}

	void SetSliderCallback(void (*Func)(float))
	{
		m_SliderCallback = std::bind(Func, std::placeholders::_1);
	}

	template <typename T>
	void SetSliderCallback(T* Obj, void (T::* Func)(float))
	{
		m_SliderCallback = std::bind(Func, Obj, std::placeholders::_1);
	}
};