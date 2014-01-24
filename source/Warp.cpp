#include "Warp.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"

CWarp::CWarp(void)
{
	SetType(OBJ_WARP);
	m_nX = 0;
	m_nY = 0;
	m_szMapName = "";
}


CWarp::~CWarp(void)
{
}

void CWarp::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_PLAYER)
		CSGD_EventSystem::GetInstance()->SendEventNow("WARP", nullptr, nullptr, this);

}

