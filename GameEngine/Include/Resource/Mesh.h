#pragma once

#include "../Ref.h"

class CMesh :
    public CRef
{
	friend class CResourceManager;

protected:
	CMesh();
	virtual ~CMesh() = 0;

protected:
	std::vector<MeshContainer>	m_vecContainer;
	Vector3	m_tMin;
	Vector3	m_tMax;

public:
	virtual bool Init();

protected:
	virtual void Render();

protected:
	bool CreateBuffer(Buffer_Type eType, void* pData, int iSize, int iCount, D3D11_USAGE eUsage, ID3D11Buffer** pBuffer);

};

