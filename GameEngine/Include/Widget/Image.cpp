
#include "Image.h"
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CImage::CImage()	:
	m_ClickCallback(nullptr)
{
}

CImage::CImage(const CImage& widget) :
	CWidget(widget)
{
	m_ClickCallback = nullptr;
}

CImage::~CImage()
{
}

bool CImage::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	CSceneResource* Resource = m_Owner->GetViewport()->GetScene()->GetResource();

	if (!Resource->LoadTexture(Name, FileName, PathName))
		return false;

	m_Info.Texture = Resource->FindTexture(Name);

	SetUseTexture(true);

	return true;
}

bool CImage::SetTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	CSceneResource* Resource = m_Owner->GetViewport()->GetScene()->GetResource();

	if (!Resource->LoadTextureFullPath(Name, FullPath))
		return false;

	m_Info.Texture = Resource->FindTexture(Name);

	SetUseTexture(true);

	return true;
}

void CImage::SetTextureTint(const Vector4& Tint)
{
	m_Info.Tint = Tint;
}

void CImage::SetTextureTint(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a)
{
	m_Info.Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CImage::AddFrameData(const Vector2& Start, const Vector2& Size)
{
	AnimationFrameData	Data;
	Data.Start = Start;
	Data.Size = Size;

	m_Info.vecFrameData.push_back(Data);
}

void CImage::Start()
{
	CWidget::Start();
}

bool CImage::Init()
{
	if (!CWidget::Init())
		return false;

	return true;
}

void CImage::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);
}

void CImage::PostUpdate(float DeltaTime)
{
	CWidget::PostUpdate(DeltaTime);
}

void CImage::Render()
{
	if (m_Info.Texture)
		m_Info.Texture->SetShader(0, (int)ConstantBuffer_Shader_Type::Pixel, 0);

	m_Tint = m_Info.Tint;

	CWidget::Render();
}

CImage* CImage::Clone()
{
	return DBG_NEW CImage(*this);
}
