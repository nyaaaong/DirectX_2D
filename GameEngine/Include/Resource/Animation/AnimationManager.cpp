
#include "AnimationManager.h"
#include "../Shader/Animation2DConstantBuffer.h"
#include "../../IMGUIListBox.h"

CAnimationManager::CAnimationManager() :
	m_Animation2DCBuffer(nullptr)
{
}

CAnimationManager::~CAnimationManager()
{
	SAFE_DELETE(m_Animation2DCBuffer);
}

bool CAnimationManager::Init()
{
	m_Animation2DCBuffer = DBG_NEW CAnimation2DConstantBuffer;

	m_Animation2DCBuffer->Init();

	return true;
}

bool CAnimationManager::CreateAnimationSequence2D(const std::string& Name, 
	const std::string& TextureName, const TCHAR* FileName, const std::string& PathName)
{
	CAnimationSequence2D* Sequence = FindSequence(Name);

	if (Sequence)
		return true;

	Sequence = DBG_NEW CAnimationSequence2D;

	Sequence->SetName(Name);

	if (!Sequence->Init(TextureName, FileName, PathName))
	{
		SAFE_DELETE(Sequence);
		return false;
	}

	m_mapSequence2D.insert(std::make_pair(Name, Sequence));

	return true;
}

bool CAnimationManager::CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const Vector2& Start, const Vector2& Size, 
	int CountX, int InterX, int CountY, int InterY, const std::string& PathName)
{
	return CreateAnimationSequence2D(Name, TextureName, FileName, Start.x, Start.y, Size.x, Size.y, CountX, InterX, CountY, InterY, PathName);
}

bool CAnimationManager::CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, float StartX, float StartY, float Width, float Height, int CountX, int InterX, 
	int CountY,	int InterY, const std::string& PathName)
{
	if (!CreateAnimationSequence2D(Name, TextureName, FileName, PathName))
		return false;

	if (CountY <= 1)
	{
		for (int i = 0; i < CountX; ++i)
		{
			if (i > 0 && InterX)
				AddFrame(Name, StartX + (Width * i + InterX * i), StartY, Width, Height);

			else
				AddFrame(Name, StartX + (Width * i), StartY, Width, Height);
		}
	}

	else
	{
		for (int i = 0; i < CountY; ++i)
		{
			for (int j = 0; j < CountX; ++j)
			{
				if (j > 0 && (InterX || InterY))
					AddFrame(Name, StartX + (Width * j + InterX * j), StartY + (Height * i + InterY), Width, Height);

				else
					AddFrame(Name, StartX + (Width * j), StartY + (Height * i), Width, Height);
			}
		}
	}

	return true;
}

void CAnimationManager::AddFrame(const std::string& Name, const Vector2& Start, const Vector2& Size)
{
	CAnimationSequence2D* Sequence = FindSequence(Name);

	if (!Sequence)
		return;

	Sequence->AddFrame(Start, Size);
}

void CAnimationManager::AddFrame(const std::string& Name, float StartX, float StartY, 
	float Width, float Height)
{
	CAnimationSequence2D* Sequence = FindSequence(Name);

	if (!Sequence)
		return;

	Sequence->AddFrame(StartX, StartY, Width, Height);
}

bool CAnimationManager::CreateAnimationSequence2D(const std::string& Name,
	CTexture* Texture)
{
	CAnimationSequence2D* Sequence = FindSequence(Name);

	if (Sequence)
		return true;

	Sequence = DBG_NEW CAnimationSequence2D;

	Sequence->SetName(Name);

	if (!Sequence->Init(Texture))
	{
		SAFE_DELETE(Sequence);
		return false;
	}

	m_mapSequence2D.insert(std::make_pair(Name, Sequence));

	return true;
}

CAnimationSequence2D* CAnimationManager::FindSequence(const std::string& Name)
{
	auto	iter = m_mapSequence2D.find(Name);

	if (iter == m_mapSequence2D.end())
		return nullptr;

	return iter->second;
}

void CAnimationManager::ReleaseSequence(const std::string& Name)
{
	auto	iter = m_mapSequence2D.find(Name);

	if (iter != m_mapSequence2D.end())
	{
		//int RefCount = iter->second->GetRefCount();
		//
		//if (RefCount == 1)
			m_mapSequence2D.erase(iter);
	}
}

bool CAnimationManager::SaveSequence(FILE* File, const std::string& Name, const char* FullPath)
{
	CAnimationSequence2D* Sequence = FindSequence(Name);

	if (!Sequence)
		return false;

	Sequence->Save(File, FullPath);

	return true;
}

bool CAnimationManager::LoadSequence(FILE* File, CIMGUIListBox* AnimFrameList, std::string& resultName, const char* FullPath, class CScene* Scene)
{
	int PrevFrameCount = AnimFrameList->GetItemCount();

	CAnimationSequence2D* Sequence = DBG_NEW CAnimationSequence2D;

	Sequence->SetScene(Scene);

	if (!Sequence->Load(File, AnimFrameList, FullPath))
	{
		SAFE_DELETE(Sequence);
		return false;
	}

	resultName = Sequence->GetName();

	auto	iter = m_mapSequence2D.find(resultName);

	if (iter != m_mapSequence2D.end())
	{
		int CurFrameCount = AnimFrameList->GetItemCount();
		int resultCount = CurFrameCount - PrevFrameCount;

		for (int i = 0; i < resultCount; ++i)
		{
			// 추가했던 마지막 프레임을 제거한다
			AnimFrameList->DeleteLastItem();
		}

		SAFE_DELETE(Sequence);
		m_mapSequence2D.erase(iter);

		return false;
	}

	m_mapSequence2D.insert(std::make_pair(resultName, Sequence));

	return true;
}