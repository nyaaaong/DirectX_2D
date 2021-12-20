
#include "AnimationSequence2D.h"
#include "../ResourceManager.h"
#include "../../IMGUIListBox.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"

CAnimationSequence2D::CAnimationSequence2D()	:
	m_Scene(nullptr)
{
}

CAnimationSequence2D::~CAnimationSequence2D()
{
}

bool CAnimationSequence2D::Init(CTexture* Texture)
{
	m_Texture = Texture;

	return true;
}

bool CAnimationSequence2D::Init(const std::string& Name,
	const TCHAR* FileName, const std::string& PathName)
{
	if (m_Scene)
	{
		if (!m_Scene->GetResource()->LoadTexture(Name, FileName, PathName))
			return false;

		m_Texture = m_Scene->GetResource()->FindTexture(Name);
	}

	else
	{
		if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
			return false;

		m_Texture = CResourceManager::GetInst()->FindTexture(Name);
	}

	return true;
}

void CAnimationSequence2D::AddFrame(const Vector2& StartPos, const Vector2& Size)
{
	AnimationFrameData	Data = {};

	Data.Start = StartPos;
	Data.Size = Size;

	m_vecFrameData.push_back(Data);
}

void CAnimationSequence2D::AddFrame(float StartX, float StartY, float Width, float Height)
{
	AnimationFrameData	Data = {};

	Data.Start = Vector2(StartX, StartY);
	Data.Size = Vector2(Width, Height);

	m_vecFrameData.push_back(Data);
}

void CAnimationSequence2D::DeleteFrame(int Index)
{
	auto	iter = m_vecFrameData.begin() + Index;

	m_vecFrameData.erase(iter);
}

void CAnimationSequence2D::ClearFrame()
{
	m_vecFrameData.clear();
}


bool CAnimationSequence2D::Save(FILE* File, const char* FullPath)
{
	int	Length = (int)m_Name.length();
	fwrite(&Length, sizeof(int), 1, File);
	fwrite(m_Name.c_str(), sizeof(char), Length, File);

	if (m_Name == "")
		ASSERT("if (m_Name == "")");


	bool	TexEnable = false;

	if (m_Texture)
		TexEnable = true;

	fwrite(&TexEnable, sizeof(bool), 1, File);

	if (m_Texture)
		m_Texture->Save(File);

	int	FrameCount = (int)m_vecFrameData.size();

	fwrite(&FrameCount, sizeof(int), 1, File);

	fwrite(&m_vecFrameData[0], sizeof(AnimationFrameData), FrameCount, File);

	return true;
}

bool CAnimationSequence2D::Load(FILE* File, CIMGUIListBox* AnimFrameList, const char* FullPath)
{
	int	Length = 0;
	fread(&Length, sizeof(int), 1, File);

	char	Name[256] = {};
	fread(Name, sizeof(char), Length, File);
	m_Name = Name;

	if (m_Name == "")
		ASSERT("if (m_Name == "")");

	bool	TexEnable = false;

	fread(&TexEnable, sizeof(bool), 1, File);

	if (TexEnable)
	{
		int	TexNameLength = 0;
		fread(&TexNameLength, sizeof(int), 1, File);
		char	TexName[256] = {};
		fread(TexName, sizeof(char), TexNameLength, File);

		Image_Type	ImageType;
		fread(&ImageType, sizeof(Image_Type), 1, File);

		int	InfoCount = 0;

		fread(&InfoCount, sizeof(int), 1, File);

		std::vector<std::wstring>	vecFullPath;
		std::vector<std::wstring>	vecFileName;
		std::string	PathName;

		for (int i = 0; i < InfoCount; ++i)
		{
			int	PathSize = 0;

			fread(&PathSize, sizeof(int), 1, File);

			TCHAR	FullPath[MAX_PATH] = {};
			fread(FullPath, sizeof(TCHAR), PathSize, File);
			vecFullPath.push_back(FullPath);

			fread(&PathSize, sizeof(int), 1, File);

			TCHAR	TexFileName[MAX_PATH] = {};
			fread(TexFileName, sizeof(TCHAR), PathSize, File);
			vecFileName.push_back(TexFileName);

			fread(&PathSize, sizeof(int), 1, File);

			char	TexPathName[MAX_PATH] = {};
			fread(TexPathName, sizeof(char), PathSize, File);

			PathName = TexPathName;
		}

		switch (ImageType)
		{
		case Image_Type::Atlas:
			if (vecFileName.size() == 1)
			{
				if (m_Scene)
				{
					m_Scene->GetResource()->LoadTexture(TexName, vecFileName[0].c_str(), PathName);
				}

				else
				{
					CResourceManager::GetInst()->LoadTexture(TexName, vecFileName[0].c_str(), PathName);
				}
			}

			else
			{
			}
			break;
		case Image_Type::Frame:
			if (vecFileName.size() == 1)
			{
			}

			else
			{
			}
			break;
		case Image_Type::Array:
			if (vecFileName.size() == 1)
			{
			}

			else
			{
			}
			break;
		}

		m_Texture = nullptr;

		if (m_Scene)
			m_Texture = m_Scene->GetResource()->FindTexture(TexName);

		else
			m_Texture = CResourceManager::GetInst()->FindTexture(TexName);
	}

	int	FrameCount = 0;

	fread(&FrameCount, sizeof(int), 1, File);

	/*if (!m_vecFrameData.empty())
		m_vecFrameData.clear();*/

	m_vecFrameData.resize((const size_t)FrameCount);

	fread(&m_vecFrameData[0], sizeof(AnimationFrameData), FrameCount, File);

	char    FrameName[32] = {};

	for (int i = 0; i < FrameCount; ++i)
	{
		memset(FrameName, 0, sizeof(char) * 32);

		sprintf_s(FrameName, "%d", i);

		if (AnimFrameList->CheckItem(FrameName))
			return false;

		AnimFrameList->AddItem(FrameName);
	}

	return true;
}
