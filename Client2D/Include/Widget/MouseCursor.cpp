#include "MouseCursor.h"
#include "Input.h"
#include "Device.h"
#include "../Object/Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/Tile.h"
#include "../Scene/MainScene.h"
#include "Scene/SceneManager.h"

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
	if (!CEngine::GetInst()->IsFocusClient())
		return;

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

	CGameObject* PlayerObj = Scene->GetSceneMode()->GetPlayerObject();

	if (Scene->GetSceneMode()->IsUseCamera())
	{
		if (!PlayerObj)
			return;

		// 마우스와 센터의 거리로 카메라 위치를 조절해야 한다.

		CPlayer2D* Player = dynamic_cast<CPlayer2D*>(PlayerObj);

		CCameraComponent* Camera = Player->GetCameraComponent();

		Resolution	RS = CDevice::GetInst()->GetResolution();
		
		Vector2		MouseUIPos = CInput::GetInst()->GetMousePos();

		// 플레이어는 카메라 중앙에 위치하므로 센터를 구해준다.
		const Vector3	Center = Vector3(RS.Width * 0.5f, RS.Height * 0.5f, 0.f);
		
		Vector3	MousePos = Vector3(MouseUIPos.x, MouseUIPos.y, 0.f);
		Vector3	Distance = MousePos - Center;
		
		Vector3	Dir = Distance;
		Dir.Normalize();

		float	CamSpeed = Camera->GetCameraSpeed();

		Vector3 NextPos = Distance - Center - Dir * CamSpeed * DeltaTime;
		NextPos.x = NextPos.x;
		NextPos.y = NextPos.y;

		Camera->SetRelativePos(NextPos);
	}
}