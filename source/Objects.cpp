#include "Objects.h"
#include "../SGD Wrappers/IListener.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

CObjects::CObjects(void)
{
	m_eType = OBJ_UNDEFINE;
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
	m_bActive = false;
	m_bRender = false;
	m_unRef = 1;
	m_aAnimationTimeInfo = new CAnimationTimeStamp;
}

CObjects::~CObjects(void)
{
	CSGD_EventSystem::GetInstance()->UnregisterClientAll(this);
	delete m_aAnimationTimeInfo;
}

void CObjects::Update(float fElapsedTime)
{
}

void CObjects::Release()
{
	if(m_unRef > 0)
		m_unRef--;

	if(m_unRef == 0)
		delete this;
}

void CObjects::HandleCollision(CObjects* col)
{


}

void CObjects::HandleEvent( const CEvent* pEvent )
{


}

