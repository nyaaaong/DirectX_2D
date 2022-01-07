
#include "Button.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CButton::CButton()	:
	m_State(Button_State::Normal)
{
}

CButton::CButton(const CButton& widget)	:
	CWidget(widget)
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

	return true;
}

bool CButton::SetTextureFullPath(Button_State State, const std::string& Name,  const TCHAR* FullPath)
{
	CSceneResource* Resource = m_Owner->GetViewport()->GetScene()->GetResource();

	if (!Resource->LoadTextureFullPath(Name, FullPath))
		return false;

	m_Info[(int)State].Texture = Resource->FindTexture(Name);

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
}

void CButton::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CButton::Render()
{
	CWidget::Render();
}
