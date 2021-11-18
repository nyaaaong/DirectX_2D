#pragma once

#include "../Ref.h"

class CSceneMode :
    public CRef
{
	friend class CScene;

protected:
	CSceneMode();
	virtual ~CSceneMode();

public:
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
};

