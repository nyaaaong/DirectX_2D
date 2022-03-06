
#include "CameraManager.h"

CCameraManager::CCameraManager()	:
	m_Scene(nullptr)
{
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::Start()
{
	if (m_CurrentCamera)
		m_CurrentCamera->Start();

	if (m_UICamera)
		m_UICamera->Start();
}

void CCameraManager::Init()
{
	m_CurrentCamera = DBG_NEW CCameraComponent;

	m_CurrentCamera->Init();

	m_CurrentCamera->SetName("DefaultCamera");
	m_CurrentCamera->m_Scene = m_Scene;
	m_CurrentCamera->SetCameraType(Camera_Type::Camera2D);


	m_UICamera = DBG_NEW CCameraComponent;

	m_UICamera->Init();

	m_UICamera->SetName("UICamera");
	m_UICamera->m_Scene = m_Scene;
	m_UICamera->SetCameraType(Camera_Type::CameraUI);

}

void CCameraManager::Update(float DeltaTime)
{
	if (m_CurrentCamera)
		m_CurrentCamera->Update(DeltaTime);
}

void CCameraManager::PostUpdate(float DeltaTime)
{
	if (m_CurrentCamera)
		m_CurrentCamera->PostUpdate(DeltaTime);
}
