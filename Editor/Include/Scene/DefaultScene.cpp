#include "DefaultScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/Material/Material.h"

CDefaultScene::CDefaultScene()
{
	SetTypeID<CDefaultScene>();
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

	//Material->AddTexture(0, (int)Buffer_Shader_Type::Pixel, "DiabloTile", TEXT("Diablos_Lair_Floor_TRS/Diablos_Lair_Floor.png"));

	Material->SetShader("TileMapShader");
	Material->SetRenderState("AlphaBlend");

	return true;
}
