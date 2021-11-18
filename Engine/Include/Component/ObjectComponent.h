#pragma once

#include "Component.h"

class CObjectComponent :
    public CComponent
{
	friend class CGameObject;
	
protected:
	CObjectComponent();
	CObjectComponent(const CObjectComponent& com);
	virtual ~CObjectComponent();

public:
	virtual bool Init() = 0;
	virtual void Update(float fTime) = 0;
	virtual void PostUpdate(float fTime) = 0;
	virtual void PrevRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual CComponent* Clone() = 0;
};

