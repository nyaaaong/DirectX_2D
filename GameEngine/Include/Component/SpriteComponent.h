#pragma once

#include "SceneComponent.h"
#include "../Resource/Mesh/SpriteMesh.h"
#include "../Resource/Material/Material.h"

class CSpriteComponent :
    public CSceneComponent
{
	friend class CGameObject;

protected:
	CSpriteComponent();
	CSpriteComponent(const CSpriteComponent& com);
	virtual ~CSpriteComponent();

protected:
	CSharedPtr<CSpriteMesh>	m_pMesh;
	CSharedPtr<CMaterial>	m_pMaterial;

public:
	void SetMaterial(CMaterial* pMaterial)
	{
		m_pMaterial = pMaterial;
	}

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CSpriteComponent* Clone();
};

