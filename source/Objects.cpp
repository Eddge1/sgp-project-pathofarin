#include "Objects.h"

CObjects::CObjects(void)
{
	m_eType = OBJ_UNDEFINE;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_bActive = false;
	m_bRender = false;
	m_unRef = 1;
}

CObjects::~CObjects(void)
{
}

void CObjects::Update(float fElapsedTime)
{
}

void CObjects::Release()
{
	if(m_unRef > 0)
		m_unRef--;

	if(m_unRef < 1)
		delete this;
}
