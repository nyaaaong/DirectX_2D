#pragma once

#include "Scene/SceneMode.h"
#include "../Widget/MainWidget.h"

class CMainScene :
    public CSceneMode
{
public:
    CMainScene();
    ~CMainScene();

private:
	CSharedPtr<CMainWidget> m_MainWidget;
	std::function<void(bool, float)> m_LoadingFunction;
	class CBubbleParticle* m_BubbleParticle;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
	void CreateMaterial();
	void CreateAnimationSequence();
	void CreateParticle();

public:
	template <typename T>
	void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
	{
		m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};

