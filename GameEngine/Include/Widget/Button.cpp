
#include "Button.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"

CButton::CButton()	:
	m_State(Button_State::Normal),
	m_MouseOnSound(false),
	m_ClickSound(false)
{
}

CButton::CButton(const CButton& widget)	:
	CWidget(widget),
	m_MouseOnSound(false),
	m_ClickSound(false)
{
	m_State = Button_State::Normal;
}

CButton::~CButton()
{
}

bool CButton::SetTexture(Button_State State, const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	CSceneResource* Resource = m_Owner->GetViewport()->GetScene()->GetResource();

	if (!Resource->LoadTexture(Name, FileName, PathName))
		return false;

	m_Info[(int)State].Texture = Resource->FindTexture(Name);

	SetUseTexture(true);

	return true;
}

bool CButton::SetTextureFullPath(Button_State State, const std::string& Name,  const TCHAR* FullPath)
{
	CSceneResource* Resource = m_Owner->GetViewport()->GetScene()->GetResource();

	if (!Resource->LoadTextureFullPath(Name, FullPath))
		return false;

	m_Info[(int)State].Texture = Resource->FindTexture(Name);

	SetUseTexture(true);

	return true;
}

void CButton::SetTextureTint(Button_State State, const Vector4& Tint)
{
	m_Info[(int)State].Tint = Tint;
}

void CButton::SetTextureTint(Button_State State, unsigned char r, unsigned char g,  unsigned char b, unsigned char a)
{
	m_Info[(int)State].Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CButton::AddFrameData(Button_State State, const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info[(int)State].vecFrameData.push_back(Data);
}

void CButton::SetSound(Button_Sound_State State, const std::string& Name)
{
	m_Sound[(int)State] = m_Owner->GetViewport()->GetScene()->GetResource()->FindSound(Name);
}

void CButton::SetSound(Button_Sound_State State, CSound* Sound)
{
	m_Sound[(int)State] = Sound;
}

void CButton::SetSound(Button_Sound_State State, const std::string& ChannelGroupName,
	const std::string& Name, const char* FileName, const std::string& PathName)
{
	m_Owner->GetViewport()->GetScene()->GetResource()->LoadSound(ChannelGroupName, false,
		Name, FileName, PathName);
	m_Sound[(int)State] = m_Owner->GetViewport()->GetScene()->GetResource()->FindSound(Name);
}

void CButton::Start()
{
	CWidget::Start();
}

bool CButton::Init()
{
	if (!CWidget::Init())
		return false;

	return true;
}

void CButton::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);

	if (m_State != Button_State::Disable)
	{
		if (m_MouseHovered)
		{
			if (!m_MouseOnSound)
			{
				m_MouseOnSound = true;

				if (m_Sound[(int)Button_Sound_State::MouseOn])
					m_Sound[(int)Button_Sound_State::MouseOn]->Play();
			}

			if (CInput::GetInst()->GetMouseLButtonClick())
			{
				m_State = Button_State::Click;

				if (!m_ClickSound)
				{
					m_ClickSound = true;

					if (m_Sound[(int)Button_Sound_State::Click])
						m_Sound[(int)Button_Sound_State::Click]->Play();
				}
			}

			else if (m_State == Button_State::Click)
			{
				if (m_ClickCallback)
					m_ClickCallback();

				m_State = Button_State::MouseOn;
				m_ClickSound = false;
			}

			else
			{
				m_ClickSound = false;
				m_State = Button_State::MouseOn;
			}
		}

		else
		{
			m_ClickSound = false;
			m_MouseOnSound = false;
			m_State = Button_State::Normal;
		}
	}
}

void CButton::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CButton::Render()
{
	if (m_Info[(int)m_State].Texture)
		m_Info[(int)m_State].Texture->SetShader(0, (int)ConstantBuffer_Shader_Type::Pixel, 0);

	m_Tint = m_Info[(int)m_State].Tint;

	CWidget::Render();
}
