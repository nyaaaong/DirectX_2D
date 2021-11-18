#pragma once

#include "Shader.h"

class CGraphicShader :
    public CShader
{
	friend class CShaderManager;

protected:
	CGraphicShader();
	virtual ~CGraphicShader() = 0;

private:
	ID3D11InputLayout* m_pInputLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3D11HullShader* m_pHS;
	ID3D11DomainShader* m_pDS;
	ID3D11GeometryShader* m_pGS;
	ID3DBlob* m_pVSBlob;
	ID3DBlob* m_pPSBlob;
	ID3DBlob* m_pHSBlob;
	ID3DBlob* m_pDSBlob;
	ID3DBlob* m_pGSBlob;
	std::vector<D3D11_INPUT_ELEMENT_DESC>	m_vecInputDesc;
	unsigned int	m_iInputSize;

public:
	void AddInputDesc(const char* cName, unsigned int iIndex, DXGI_FORMAT eFmt, unsigned int iSlot, unsigned int iSize, D3D11_INPUT_CLASSIFICATION eSlotClass, unsigned int iInstanceDataStep);
	bool CreateInputLayout();

public:
	virtual bool Init() = 0;
	virtual void SetShader();

public:
	bool LoadVertexShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName);
	bool LoadPixelShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName);
	bool LoadHullShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName);
	bool LoadDomainShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName);
	bool LoadGeometryShader(const char* cEntryName, const TCHAR* cFileName, const std::string& strPathName);
};

