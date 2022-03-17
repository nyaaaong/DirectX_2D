#include "DefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/SceneManager.h"
#include "Resource/Material/Material.h"

CDefaultScene::CDefaultScene()
{
	SetTypeID<CDefaultScene>();

	CSceneManager::GetInst()->Editor(true);
}

CDefaultScene::~CDefaultScene()
{
}

bool CDefaultScene::Init()
{
	CreateMaterial();

	return true;
}

bool CDefaultScene::CreateMaterial()
{
	m_Scene->GetResource()->CreateMaterial<CMaterial>("TileMap");
	CMaterial* Material = m_Scene->GetResource()->FindMaterial("TileMap");

	Material->SetShader("TileMapShader");
	Material->SetRenderState("AlphaBlend");

	return true;
}
