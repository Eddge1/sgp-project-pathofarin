#include "Warp.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "Player.h"
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
	{
		CPlayer* pTemp = reinterpret_cast<CPlayer*>(col);
		if(pTemp != nullptr)
		{
			if(!pTemp->GetIsWarping())
			{
				pTemp->SetIsWarping(true);
				CSGD_EventSystem::GetInstance()->SendEventNow("WARP", nullptr, nullptr, this);
				pTemp->SetPosX(float(m_nX));
				pTemp->SetPosY(float(m_nY));
				pTemp->SetLastPositionX(float(m_nX));
				pTemp->SetLastPositionY(float(m_nY));
			}

		}
	}
}

