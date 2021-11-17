
#include "GraphicShader.h"
#include "../../PathManager.h"
#include "../../Device.h"

CGraphicShader::CGraphicShader()	:
	m_pInputLayout(nullptr),
	m_pVS(nullptr),
	m_pPS(nullptr),
	m_pHS(nullptr),
	m_pDS(nullptr),
	m_pGS(nullptr),
	m_pVSBlob(nullptr),
	m_pPSBlob(nullptr),
	m_pHSBlob(nullptr),
	m_pDSBlob(nullptr),
	m_pGSBlob(nullptr),
	m_iInputSize(0)
{
	m_eType = Shader_Type::Graphic;
}

CGraphicShader::~CGraphicShader()
{
	SAFE_RELEASE(m_pInputLayout);

	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pPS);
	SAFE_RELEASE(m_pHS);
	SAFE_RELEASE(m_pDS);
	SAFE_RELEASE(m_pGS);

	SAFE_RELEASE(m_pVSBlob);
	SAFE_RELEASE(m_pPSBlob);
	SAFE_RELEASE(m_pHSBlob);
	SAFE_RELEASE(m_pDSBlob);
	SAFE_RELEASE(m_pGSBlob);
}

void CGraphicShader::AddInputDesc(const char* cName, unsigned int iIndex, DXGI_FORMAT eFmt, unsigned int iSlot, unsigned int iSize, D3D11_INPUT_CLASSIFICATION eSlotClass, unsigned int iInstanceDataStep)
{
	D3D11_INPUT_ELEMENT_DESC    tDesc = {};

	tDesc.SemanticName = cName;
	tDesc.SemanticIndex = iIndex;
	tDesc.Format = eFmt;
	tDesc.InputSlot = iSlot;
	tDesc.InputSlotClass = eSlotClass;
	tDesc.InstanceDataStepRate = iInstanceDataStep;

	tDesc.AlignedByteOffset = m_iInputSize;

	m_iInputSize += iSize;

	m_vecInputDesc.push_back(tDesc);
}

bool CGraphicShader::CreateInputLayout()
{
	return false;
}

void CGraphicShader::SetShader()
{
}

bool CGraphicShader::LoadVertexShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName)
{
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pVSBlob);

	unsigned int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	TCHAR   cFullPath[MAX_PATH] = {};

	const PathInfo* pInfo = CPathManager::GetInst()->FindPath(strPathName);

	if (pInfo)
		lstrcpy(cFullPath, pInfo->cPath);

	lstrcat(cFullPath, cFileName);

	ID3DBlob* pError = nullptr;

	if (FAILED(D3DCompileFromFile(cFullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, cEntryName, "vs_5_0", iFlag, 0, &m_pVSBlob, &pError)))
	{
		OutputDebugStringA((char*)pError->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}

	// 컴파일된 코드를 이용해서 Shader를 만든다.
	if (FAILED(CDevice::GetInst()->GetDevice()->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize(), nullptr, &m_pVS)))
		return false;


	return true;
}

bool CGraphicShader::LoadPixelShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName)
{
	return false;
}

bool CGraphicShader::LoadHullShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName)
{
	return false;
}

bool CGraphicShader::LoadDomainShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName)
{
	return false;
}

bool CGraphicShader::LoadGeometryShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName)
{
	return false;
}
