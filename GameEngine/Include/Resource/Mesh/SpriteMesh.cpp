
#include "SpriteMesh.h"

CSpriteMesh::CSpriteMesh()
{
}

CSpriteMesh::~CSpriteMesh()
{
}

bool CSpriteMesh::Init()
{
	MeshContainer* tContainer = new MeshContainer;

	tContainer->tVB.iSize = sizeof(VertexColor);
	tContainer->tVB.iCount = 4;
	tContainer->ePrimitive = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	VertexColor	tVertex[4] =
	{
		VertexColor(Vector3(-0.5f, 0.5f, 0.f), Vector4::Red),
		VertexColor(Vector3(0.5f, 0.5f, 0.f), Vector4::Green),
		VertexColor(Vector3(-0.5f, -0.5f, 0.f), Vector4::Blue),
		VertexColor(Vector3(0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f))
	};

	if (!CreateBuffer(Buffer_Type::Vertex, tVertex, sizeof(VertexColor), 4, D3D11_USAGE_IMMUTABLE, &tContainer->tVB.pBuffer))
		return false;

	tContainer->vecIB.resize(1);

	tContainer->vecIB[0].iSize = 2;
	tContainer->vecIB[0].iCount = 6;
	tContainer->vecIB[0].eFmt = DXGI_FORMAT_R16_UINT;

	unsigned short arrIndex[6] = { 0, 1, 3, 0, 3, 2 };

	if (!CreateBuffer(Buffer_Type::Index, arrIndex, sizeof(unsigned short), 6, D3D11_USAGE_IMMUTABLE, &tContainer->vecIB[0].pBuffer))
		return false;

	m_vecContainer.push_back(tContainer);

	return true;
}
