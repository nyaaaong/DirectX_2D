
#include "ComputeShader.h"
#include "../../PathManager.h"
#include "../../Device.h"

CComputeShader::CComputeShader() :
	m_CS(nullptr),
	m_CSBlob(nullptr)
{
	m_Type = Shader_Type::Compute;
}

CComputeShader::~CComputeShader()
{
	SAFE_RELEASE(m_CS);
	SAFE_RELEASE(m_CSBlob);
}

void CComputeShader::SetShader()
{
	CDevice::GetInst()->GetContext()->CSSetShader(m_CS, nullptr, 0);
}

bool CComputeShader::LoadComputeShader(const char* EntryName, const TCHAR* FileName, const std::string& PathName)
{
	SAFE_RELEASE(m_CS);
	SAFE_RELEASE(m_CSBlob);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	TCHAR   FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	if (Info)
		lstrcpy(FullPath, Info->Path);

	lstrcat(FullPath, FileName);

	ID3DBlob* Error = nullptr;

	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryName, "cs_5_0", Flag, 0, &m_CSBlob, &Error)))
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		OutputDebugStringA("\n");

		return false;
	}

	// �����ϵ� �ڵ带 �̿��ؼ� Shader�� �����.
	if (FAILED(CDevice::GetInst()->GetDevice()->CreateComputeShader(m_CSBlob->GetBufferPointer(),
		m_CSBlob->GetBufferSize(), nullptr, &m_CS)))
		return false;


	return true;
}

void CComputeShader::Excute(unsigned int x, unsigned int y, unsigned int z)
{
	// ComputeShader�� ��������ش�.
	SetShader();
	CDevice::GetInst()->GetContext()->Dispatch(x, y, z);
	//CDevice::GetInst()->GetContext()->CSSetShader(nullptr, nullptr, 0);
}
