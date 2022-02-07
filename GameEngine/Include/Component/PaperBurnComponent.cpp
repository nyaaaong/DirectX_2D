
#include "PaperBurnComponent.h"

CPaperBurnComponent::CPaperBurnComponent()
{
	m_CBuffer = new CPaperBurnConstantBuffer;

	m_CBuffer->Init();
}

CPaperBurnComponent::CPaperBurnComponent(const CPaperBurnComponent& com)	:
	CObjectComponent(com)
{
	m_CBuffer = new CPaperBurnConstantBuffer;

	m_CBuffer->Init();
}

CPaperBurnComponent::~CPaperBurnComponent()
{
}

void CPaperBurnComponent::Start()
{
	CObjectComponent::Start();
}

bool CPaperBurnComponent::Init()
{
	return true;
}

void CPaperBurnComponent::Update(float DeltaTime)
{
}

void CPaperBurnComponent::PostUpdate(float DeltaTime)
{
}

void CPaperBurnComponent::PrevRender()
{
}

void CPaperBurnComponent::Render()
{
}

void CPaperBurnComponent::PostRender()
{
}

CPaperBurnComponent* CPaperBurnComponent::Clone()
{
	return new CPaperBurnComponent(*this);
}
