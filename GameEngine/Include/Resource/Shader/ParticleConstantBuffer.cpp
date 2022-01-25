
#include "ParticleConstantBuffer.h"
#include "ConstantBuffer.h"

CParticleConstantBuffer::CParticleConstantBuffer() :
	m_BufferData{}
{
}

CParticleConstantBuffer::CParticleConstantBuffer(const CParticleConstantBuffer& Buffer) :
	CConstantBufferBase(Buffer)
{
	m_BufferData = Buffer.m_BufferData;
}

CParticleConstantBuffer::~CParticleConstantBuffer()
{
}

bool CParticleConstantBuffer::Init()
{
	SetConstantBuffer("ParticleCBuffer");

	return true;
}

void CParticleConstantBuffer::UpdateCBuffer()
{
	m_Buffer->UpdateBuffer(&m_BufferData);
}

CParticleConstantBuffer* CParticleConstantBuffer::Clone()
{
	return new CParticleConstantBuffer(*this);
}
