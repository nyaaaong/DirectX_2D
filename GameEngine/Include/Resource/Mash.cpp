
#include "Mash.h"
#include "../Device.h"

CMash::CMash()
{
}

CMash::~CMash()
{
}

bool CMash::Init()
{
	return true;
}

void CMash::Render()
{
	size_t	iSize = m_vecContainer.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		unsigned int	iStride = m_vecContainer[i].tVB.iSize;
		unsigned int	iOffset = 0;

		CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(m_vecContainer[i].ePrimitive);
		CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1, &m_vecContainer[i].tVB.pBuffer, &iStride, &iOffset);

		size_t	iIndexCount = m_vecContainer[i].vecIB.size();

		if (iIndexCount > 0)
		{
			for (size_t j = 0; j < iIndexCount; ++j)
			{
				CDevice::GetInst()->GetContext()->IASetIndexBuffer(m_vecContainer[i].vecIB[j].pBuffer, m_vecContainer[i].vecIB[j].eFmt, 0);
				CDevice::GetInst()->GetContext()->DrawIndexed(m_vecContainer[i].vecIB[j].iCount, 0, 0);
			}
		}

		else
		{
			CDevice::GetInst()->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
			CDevice::GetInst()->GetContext()->Draw(m_vecContainer[i].tVB.iCount, 0);
		}
	}
}

bool CMash::CreateBuffer(Buffer_Type eType, void* pData, int iSize, int iCount, D3D11_USAGE eUsage, ID3D11Buffer** pBuffer)
{
	D3D11_BUFFER_DESC	eDesc = {};

	eDesc.ByteWidth = iSize * iCount;
	eDesc.Usage = eUsage;

	if (eType == Buffer_Type::Vertex)
		eDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	else
		eDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	if (eUsage == D3D11_USAGE_DYNAMIC)
		eDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	else if (eUsage == D3D11_USAGE_STAGING)
		eDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA	tBufferData = {};

	tBufferData.pSysMem = pData;

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&eDesc, &tBufferData, pBuffer)))
		return false;

	if (eType == Buffer_Type::Vertex)
	{
		char* pVertexData = static_cast<char*>(pData);

		for (int i = 0; i < iCount; ++i)
		{
			Vector3* tPos = (Vector3*)pVertexData;
			pVertexData += iSize;

			if (m_tMin.x > tPos->x)
				m_tMin.x = tPos->x;

			if (m_tMin.y > tPos->y)
				m_tMin.y = tPos->y;

			if (m_tMin.z > tPos->z)
				m_tMin.z = tPos->z;

			if (m_tMax.x < tPos->x)
				m_tMax.x = tPos->x;

			if (m_tMax.y < tPos->y)
				m_tMax.y = tPos->y;

			if (m_tMax.z < tPos->z)
				m_tMax.z = tPos->z;
		}
	}

	return true;
}
