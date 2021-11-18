#pragma once

#include "../Ref.h"

class CGameObject :
    public CRef
{
	friend class CScene;

protected:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void Collision(float fTime);
	virtual void Render();
};

