
#include "Material.h"
#include "../ResourceManager.h"

CMaterial::CMaterial()
{
	SetTypeID<CMaterial>();
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetShader(const std::string& strName)
{
	m_pShader = (CGraphicShader*)CResourceManager::GetInst()->FindShader(strName);
}

void CMaterial::Render()
{
	if (m_pShader)
		m_pShader->SetShader();
}
