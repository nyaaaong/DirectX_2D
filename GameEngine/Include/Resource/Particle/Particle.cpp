
#include "Particle.h"
#include "../Shader/StructuredBuffer.h"
#include "../Shader/ShaderManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
#include "../ResourceManager.h"

CParticle::CParticle()	:
	m_CBuffer(nullptr),
	m_SpawnTime(0.001f),
	m_2D(true)
{
}

CParticle::CParticle(const CParticle& particle)
{
	m_CBuffer = particle.m_CBuffer->Clone();
	m_UpdateShader = particle.m_UpdateShader;
}

CParticle::~CParticle()
{
	SAFE_DELETE(m_CBuffer);
}

bool CParticle::Init()
{
	m_CBuffer = DBG_NEW CParticleConstantBuffer;

	if (!m_CBuffer->Init())
		return false;

	if (m_Scene)
		m_UpdateShader = (CParticleUpdateShader*)m_Scene->GetResource()->FindShader("ParticleUpdateShader");

	else
		m_UpdateShader = (CParticleUpdateShader*)CResourceManager::GetInst()->FindShader("ParticleUpdateShader");

	return true;
}

void CParticle::AddStructuredBuffer(const std::string& Name, unsigned int Size, unsigned int Count, 
	int Register, bool Dynamic, int StructuredBufferShaderType)
{
	CStructuredBuffer* Buffer = DBG_NEW CStructuredBuffer;

	if (!Buffer->Init(Name, Size, Count, Register, Dynamic, StructuredBufferShaderType))
	{
		SAFE_DELETE(Buffer);
		return;
	}

	m_vecStructuredBuffer.push_back(Buffer);

}
