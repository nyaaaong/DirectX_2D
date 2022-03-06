#include "MouseCursor.h"
#include "Input.h"
#include "Device.h"
#include "../Object/Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/Tile.h"
#include "Scene/SceneManager.h"
#include "../Scene/MainScene.h"

CMouseCursor::CMouseCursor()	:
	m_CheckTileInfo(false)
{
}

CMouseCursor::CMouseCursor(const CMouseCursor& window) :
	CWidgetWindow(window)
{
	m_Image = FindWidget<CImage>("Image");

	m_CheckTileInfo = false;
}

CMouseCursor::~CMouseCursor()
{
}

void CMouseCursor::Start()
{
	CWidgetWindow::Start();
}

bool CMouseCursor::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(32.f, 31.f);

	m_Image = CreateWidget<CImage>("Image");
	m_Image->SetTexture("Cursor", TEXT("Mouse/Cursor.png"), TEXTURE_PATH);
	m_Image->SetSize(33.f, 33.f);

	return true;
}

void CMouseCursor::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	CameraUpdater(DeltaTime);
}

void CMouseCursor::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CMouseCursor::Render()
{
	CWidgetWindow::Render();
}

CMouseCursor* CMouseCursor::Clone()
{
	return DBG_NEW CMouseCursor(*this);
}

void CMouseCursor::CameraUpdater(float DeltaTime)
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CGameObject* Player = Scene->GetSceneMode()->GetPlayerObject();

	if (Scene->GetSceneMode()->IsUseCamera())
	{
		if (!Player)
			return;

		else if (CEngine::GetInst()->IsMouseWindowOut())
			return;

		// ���콺�� ������ �Ÿ��� ī�޶� ��ġ�� �����ؾ� �Ѵ�.

		CCameraComponent* Camera = ((CPlayer2D*)Scene->GetPlayerObject())->GetCameraComponent();

		Resolution	RS = CDevice::GetInst()->GetResolution();
		
		Vector2		MouseUIPos = CInput::GetInst()->GetMousePos();
		const Vector3	Center = Vector3(RS.Width * 0.5f, RS.Height * 0.5f, 0.f);
		
		Vector3	MousePos = Vector3(MouseUIPos.x, MouseUIPos.y, 0.f);
		Vector3	Distance = MousePos - Center;
		
		Vector3	Dir = Distance;
		Dir.Normalize();

		float	CamSpeed = Camera->GetCameraSpeed();

		Vector3 NextPos = Distance - Center - Dir * CamSpeed * DeltaTime;

		Camera->SetRelativePos(NextPos);
	}
}