
#include "Slider.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"

CSlider::CSlider() :
	m_SliderCallback(nullptr),
	m_SliderBarMin(0.f),
	m_SliderBarMax(0.f),
	m_PrevMousePosX(0.f),
	m_CurMousePosX(0.f),
	m_Value(0.f),
	m_Gap(0.f),
	m_CheckSliderInClick(false),
	m_CheckSliderOutClick(false)
{
}

CSlider::CSlider(const CSlider& widget) :
	CWidget(widget),
	m_Value(0.f),
	m_Gap(0.f),
	m_PrevMousePosX(0.f),
	m_CurMousePosX(0.f),
	m_CheckSliderInClick(false),
	m_CheckSliderOutClick(false)
{
	m_SliderCallback = nullptr;

	m_SliderBarMin = widget.m_SliderBarMin;
	m_SliderBarMax = widget.m_SliderBarMax;
}

CSlider::~CSlider()
{
}

bool CSlider::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, FileName, PathName))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CSlider::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, FullPath))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CSlider::SetTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTexture(Name, vecFileName, PathName))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

bool CSlider::SetTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath)
{
	if (m_Owner->GetViewport())
	{
		if (!m_Owner->GetViewport()->GetScene()->GetResource()->LoadTextureFullPath(Name, vecFullPath))
			return false;

		m_Info.Texture = m_Owner->GetViewport()->GetScene()->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath);

		m_Info.Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	SetUseTexture(true);

	return true;
}

void CSlider::SetTextureTint(const Vector4& Tint)
{
	m_Info.Tint = Tint;
}

void CSlider::SetTextureTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_Info.Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CSlider::AddFrameData(const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info.vecFrameData.push_back(Data);
}

void CSlider::SetPlayTime(float PlayTime)
{
	m_Info.PlayTime = PlayTime;
}

void CSlider::SetPlayScale(float PlayScale)
{
	m_Info.PlayScale = PlayScale;
}

void CSlider::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);

	/*
	슬라이더가 아닌 다른 곳에서 드래그한 상태에서 슬라이더로 들어올 경우 슬라이더가 활성화 되는 버그를 막기 위한 예외 처리
	*/
	if (!m_MouseHovered)
	{
		if (CInput::GetInst()->GetMouseLButtonClick())
			m_CheckSliderOutClick = true;

		else
			m_CheckSliderOutClick = false;
	}

	else
	{
		if (!m_CheckSliderOutClick && !m_CheckSliderInClick && CInput::GetInst()->GetMouseLButtonClick())
		{
			m_CheckSliderInClick = true;

			m_PrevMousePosX = CInput::GetInst()->GetMousePos().x;
			m_Gap = m_PrevMousePosX - m_Pos.x;
		}
	}

	if (m_CheckSliderInClick)
	{
		if (!CInput::GetInst()->GetMouseLButtonClick())
		{
			m_CheckSliderInClick = false;

			m_PrevMousePosX = m_CurMousePosX = 0.f;
		}

		else
		{
			m_CurMousePosX = CInput::GetInst()->GetMousePos().x;

			m_Value = m_CurMousePosX - m_Gap;

			if (m_Value < m_SliderBarMin)
				m_Value = m_SliderBarMin;

			else if (m_Value > m_SliderBarMax)
				m_Value = m_SliderBarMax;

			m_Pos.x = m_Value;

			if (m_SliderCallback)
				m_SliderCallback(m_Value - m_SliderBarMin);
		}
	}
}

void CSlider::Render()
{
	if (m_Info.Texture)
		m_Info.Texture->SetShader(0, (int)ConstantBuffer_Shader_Type::Pixel, 0);

	m_Tint = m_Info.Tint;

	CWidget::Render();
}

CSlider* CSlider::Clone()
{
	return DBG_NEW CSlider(*this);
}
