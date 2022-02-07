#pragma once

#include "GameObject\GameObject.h"

class CSparkParticle :
	public CGameObject
{
	friend class CScene;

protected:
	CSparkParticle();
	CSparkParticle(const CSparkParticle& obj);
	virtual ~CSparkParticle();

private:
	CSharedPtr<class CParticleComponent>    m_Particle;
	float		m_LifeTime;
	float		m_LifeTimeMax;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CSparkParticle* Clone();
};

