
#include "GameObject.h"
#include "../Scene/SceneManager.h"
#include "../PathManager.h"
#include "../Component/NavAgent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/ColliderBox2D.h"
#include "../Component/ColliderCircle.h"
#include "../Component/ColliderPixel.h"
#include "../Component/CameraComponent.h"
#include "../Component/WidgetComponent.h"
#include "../Component/ParticleComponent.h"
#include "../Component/TileMapComponent.h"

CGameObject::CGameObject()	:
	m_Scene(nullptr),
	m_Parent(nullptr),
	m_LifeSpan(0.f),
	m_AnimationInstance(nullptr)
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& obj)
{
	*this = obj;

	m_AnimationInstance = nullptr;

	m_RefCount = 0;

	if (obj.m_RootComponent)
	{
		m_RootComponent = obj.m_RootComponent->Clone();

		m_RootComponent->SetGameObject(this);

		m_RootComponent->SetSceneComponent(this);
	}

	m_vecObjectComponent.clear();

	size_t	Size = obj.m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent.push_back(obj.m_vecObjectComponent[i]->Clone());

		m_vecObjectComponent[i]->SetGameObject(this);
	}
}

CGameObject::~CGameObject()
{
}

void CGameObject::SetScene(CScene* Scene)
{
	m_Scene = Scene;
}

void CGameObject::Destroy()
{
	CRef::Destroy();

	m_RootComponent->Destroy();

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Destroy();
	}
}
CComponent* CGameObject::FindComponent(const std::string& Name)
{
	{
		auto	iter = m_SceneComponentList.begin();
		auto	iterEnd = m_SceneComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
				return *iter;
		}
	}

	{
		auto	iter = m_vecObjectComponent.begin();
		auto	iterEnd = m_vecObjectComponent.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
				return *iter;
		}
	}

	return nullptr;
}

void CGameObject::GetAllSceneComponentsName(std::vector<FindComponentName>& vecNames)
{
	if (!m_RootComponent)
		return;

	m_RootComponent->GetAllSceneComponentsName(vecNames);
}

int CGameObject::GetAllComponentFlag()
{
	int Ret = 0;

	auto	iter = m_SceneComponentList.begin();
	auto	iterEnd = m_SceneComponentList.end();

	for (; iter != iterEnd; ++iter)
	{
		size_t TypeID = (*iter)->GetTypeID();

		if (TypeID == GetTypeID<CSpriteComponent>())
			Ret |= (int)Component_Flag::Sprite;

		else if (TypeID == GetTypeID<CStaticMeshComponent>())
			Ret |= (int)Component_Flag::StaticMesh;

		else if (TypeID == GetTypeID<CColliderBox2D>())
			Ret |= (int)Component_Flag::Box2D;

		else if (TypeID == GetTypeID<CColliderCircle>())
			Ret |= (int)Component_Flag::Circle;

		else if (TypeID == GetTypeID<CColliderPixel>())
			Ret |= (int)Component_Flag::Pixel;

		else if (TypeID == GetTypeID<CCameraComponent>())
			Ret |= (int)Component_Flag::Camera;

		else if (TypeID == GetTypeID<CWidgetComponent>())
			Ret |= (int)Component_Flag::Widget;

		else if (TypeID == GetTypeID<CParticleComponent>())
			Ret |= (int)Component_Flag::Particle;

		else if (TypeID == GetTypeID<CTileMapComponent>())
			Ret |= (int)Component_Flag::TileMap;
	}

    return Ret;
}

void CGameObject::GetSceneComponentName(std::vector<std::string>& vecName)
{
	size_t Size = m_SceneComponentList.size();

	vecName.resize(Size);

	int Index = 0;

	auto	iter = m_SceneComponentList.begin();
	auto	iterEnd = m_SceneComponentList.end();

	for (; iter != iterEnd; ++iter)
	{
		vecName[Index] = (*iter)->GetName();

		++Index;
	}
}

Vector2 CGameObject::GetAnimationSize2D() const
{
	if (m_Sprite)
	{
		CAnimationSequence2DInstance* AnimInstance = m_Sprite->GetAnimationInstance();

		if (AnimInstance)
			return AnimInstance->GetCurrentAnimation()->GetAnimationSequence()->GetFrameData(0).Size;
	}

    return Vector2();
}

Vector3 CGameObject::GetAnimationSize() const
{
	Vector2	Size2D = GetAnimationSize2D();

	return Vector3(Size2D.x, Size2D.y, 0.f);
}

void CGameObject::Start()
{
	if (m_RootComponent)
		m_RootComponent->Start();

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Start();
	}
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
	if (m_LifeSpan > 0.f)
	{
		m_LifeSpan -= DeltaTime;

		if (m_LifeSpan <= 0.f)
		{
			Destroy();
			return;
		}
	}

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Update(DeltaTime);
	}

	if (m_RootComponent)
		m_RootComponent->Update(DeltaTime);

	//m_AnimationSize
	if (m_Sprite)
	{
		m_AnimationInstance = m_Sprite->GetAnimationInstance();

		if (m_AnimationInstance)
		{
			m_AnimationSize = m_AnimationInstance->GetCurrentAnimation()->GetAnimationSequence()->GetFrameData(0).Size;

			m_Sprite->SetRelativeScale(m_AnimationSize.x, m_AnimationSize.y, 1.f);
		}
	}
}

void CGameObject::PostUpdate(float DeltaTime)
{
	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->PostUpdate(DeltaTime);
	}

	if (m_RootComponent)
		m_RootComponent->PostUpdate(DeltaTime);
}

void CGameObject::AddCollision()
{
	if (m_RootComponent)
		m_RootComponent->CheckCollision();
}

void CGameObject::PrevRender()
{
	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->PrevRender();
	}

	if (m_RootComponent)
		m_RootComponent->PrevRender();
}

void CGameObject::Render()
{
	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Render();
	}

	if (m_RootComponent)
		m_RootComponent->Render();
}

void CGameObject::PostRender()
{
	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->PostRender();
	}

	if (m_RootComponent)
		m_RootComponent->PostRender();
}

CGameObject* CGameObject::Clone()
{
	return DBG_NEW CGameObject(*this);
}

void CGameObject::Save(FILE* File)
{
	CRef::Save(File);

	if (m_RootComponent)
	{
		bool	Root = true;
		fwrite(&Root, sizeof(bool), 1, File);

		size_t	TypeID = m_RootComponent->GetTypeID();
		fwrite(&TypeID, sizeof(size_t), 1, File);

		m_RootComponent->Save(File);
	}

	else
	{
		bool	Root = false;
		fwrite(&Root, sizeof(bool), 1, File);
	}

	int	ObjComponentCount = (int)m_vecObjectComponent.size();

	fwrite(&ObjComponentCount, sizeof(int), 1, File);

	for (int i = 0; i < ObjComponentCount; ++i)
	{
		size_t	TypeID = m_vecObjectComponent[i]->GetTypeID();
		fwrite(&TypeID, sizeof(size_t), 1, File);

		m_vecObjectComponent[i]->Save(File);
	}
}

void CGameObject::Load(FILE* File)
{
	CRef::Load(File);

	bool	Root = false;
	fread(&Root, sizeof(bool), 1, File);

	if (Root)
	{
		size_t	TypeID = 0;
		fread(&TypeID, sizeof(size_t), 1, File);

		CSceneManager::GetInst()->CallCreateComponent(this, TypeID);

		m_RootComponent->Load(File);
	}

	int	ObjComponentCount = 0;

	fread(&ObjComponentCount, sizeof(int), 1, File);

	for (int i = 0; i < ObjComponentCount; ++i)
	{
		size_t	TypeID = 0;
		fread(&TypeID, sizeof(size_t), 1, File);

		CComponent* Component = CSceneManager::GetInst()->CallCreateComponent(this, TypeID);

		Component->Load(File);

		m_vecObjectComponent.push_back((CObjectComponent*)Component);
	}
}

void CGameObject::Save(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "wb");

	if (!File)
		return;

	Save(File);

	fclose(File);
}

void CGameObject::Load(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	Load(File);

	fclose(File);
}

void CGameObject::Save(const char* FileName, const std::string& PathName)
{
	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	Save(FullPath);
}

void CGameObject::Load(const char* FileName, const std::string& PathName)
{
	char	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	Load(FullPath);
}

bool CGameObject::FindCompoentType(SceneComponent_Type Type)
{
	size_t ID = 0;

	switch (Type)
	{
	case SceneComponent_Type::Sprite:
		ID = GetTypeID<CSpriteComponent>();
		break;
	case SceneComponent_Type::StaticMesh:
		ID = GetTypeID<CStaticMeshComponent>();
		break;
	case SceneComponent_Type::Box2D:
		ID = GetTypeID<CColliderBox2D>();
		break;
	case SceneComponent_Type::Circle:
		ID = GetTypeID<CColliderCircle>();
		break;
	case SceneComponent_Type::Pixel:
		ID = GetTypeID<CColliderPixel>();
		break;
	case SceneComponent_Type::Camera:
		ID = GetTypeID<CCameraComponent>();
		break;
	case SceneComponent_Type::Widget:
		ID = GetTypeID<CWidgetComponent>();
		break;
	case SceneComponent_Type::Particle:
		ID = GetTypeID<CParticleComponent>();
		break;
	case SceneComponent_Type::TileMap:
		ID = GetTypeID<CTileMapComponent>();
		break;
	}

	if (!ID)
		return false;

	auto	iter = m_SceneComponentList.begin();
	auto	iterEnd = m_SceneComponentList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->CheckTypeID(ID))
			return true;
	}

	return false;
}

void CGameObject::Move(const Vector3& EndPos)
{
	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecObjectComponent[i]->CheckTypeID<CNavAgent>())
		{
			((CNavAgent*)m_vecObjectComponent[i].Get())->Move(EndPos);
			break;
		}
	}
}