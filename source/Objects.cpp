#include "Objects.h"


CObjects::CObjects(void)
{
	m_eType = OBJ_UNDEFINE;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_bActive = false;
	m_bRender = false;
}

CObjects::~CObjects(void)
{
}

void CObjects::Update(float fElapsedTime)
{

}