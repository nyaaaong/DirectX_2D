
#include "SliderBar.h"
#include "WidgetWindow.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"

CSliderBar::CSliderBar()
{
}

CSliderBar::CSliderBar(const CSliderBar& widget) :
	CWidget(widget)
{
}

CSliderBar::~CSliderBar()
{
}

bool CSliderBar::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
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

bool CSliderBar::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
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

bool CSliderBar::SetTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName, const std::string& PathName)
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

bool CSliderBar::SetTextureFullPath(const std::string& Name, const std::vector<TCHAR*>& vecFullPath)
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

void CSliderBar::SetTextureTint(const Vector4& Tint)
{
	m_Info.Tint = Tint;
}

void CSliderBar::SetTextureTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_Info.Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CSliderBar::AddFrameData(const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info.vecFrameData.push_back(Data);
}

void CSliderBar::SetPlayTime(float PlayTime)
{
	m_Info.PlayTime = PlayTime;
}

void CSliderBar::SetPlayScale(float PlayScale)
{
	m_Info.PlayScale = PlayScale;
}

void CSliderBar::Render()
{
	if (m_Info.Texture)
		m_Info.Texture->SetShader(0, (int)ConstantBuffer_Shader_Type::Pixel, 0);

	m_Tint = m_Info.Tint;

	CWidget::Render();
}

CSliderBar* CSliderBar::Clone()
{
	return DBG_NEW CSliderBar(*this);
}
