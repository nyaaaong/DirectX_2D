#pragma once
#include "SceneComponent.h"
class CParticleComponent :
    public CSceneComponent
{
	friend class CGameObject;
	friend class CCameraManager;

protected:
	CParticleComponent();
	CParticleComponent(const CParticleComponent& com);
	virtual ~CParticleComponent();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render();
	virtual void PostRender();
	virtual CParticleComponent* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

