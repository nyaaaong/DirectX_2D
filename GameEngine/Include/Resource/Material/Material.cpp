
#include "Material.h"
#include "../ResourceManager.h"

CMaterial::CMaterial()
{
	SetTypeID<CMaterial>();
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetShader(const std::string& Name)
{
	m_Shader = (CGraphicShader*)CResourceManager::GetInst()->FindShader(Name);
}

void CMaterial::Render()
{
	if (m_Shader)
		m_Shader->SetShader();
}
