
#include "RenderState.h"

CRenderState::CRenderState()	:
	m_State(nullptr),
	m_PrevState(nullptr),
	m_Type((RenderState_Type)0)
{
}

CRenderState::~CRenderState()
{
	SAFE_RELEASE(m_State);
	SAFE_RELEASE(m_PrevState);
}
