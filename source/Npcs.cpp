#include "Npcs.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"


CNpcs::CNpcs(void)
{
	SetType(OBJ_NPC);
	m_bContainsUnits = false;
	m_bIsHostile = false;
	m_nWaypoint = 0;

	CSGD_EventSystem::GetInstance()->RegisterClient("BATTLE_END", this);

}


CNpcs::~CNpcs(void)
{
	for(unsigned int i = 0; i < m_vWaypoints.size(); i++)
	{
		delete m_vWaypoints[i];
	}

	m_vWaypoints.clear();

}

void CNpcs::SetUnits(std::string szName)
{
	m_vUnitList.push_back(szName);
}

void CNpcs::AddConversation(std::string szConvo)
{
	m_szConversation.push_back(szConvo);
}

std::string CNpcs::GetUnit(int nI)
{
	if(nI < int(m_vUnitList.size()))
		return m_vUnitList[nI];
	return "";
}

void CNpcs::Update(float fElapsedTime)
{
	SetVelX(0);
	SetVelY(0);

	if(m_vWaypoints.size() > 0 && GetActive())
	{
		if(GetPosX() <= m_vWaypoints[m_nWaypoint]->locX + 1 && GetPosX() >= m_vWaypoints[m_nWaypoint]->locX - 1)
		{
			if(GetPosY() <= m_vWaypoints[m_nWaypoint]->locY + 1 && GetPosY() >= m_vWaypoints[m_nWaypoint]->locY - 1)
			{
				m_nWaypoint++;
				if(m_nWaypoint >= int(m_vWaypoints.size()))
					m_nWaypoint = 0;
			}
		}

		if(GetPosX() < m_vWaypoints[m_nWaypoint]->locX - 1)
			SetVelX(100);
		else if(GetPosX() > m_vWaypoints[m_nWaypoint]->locX + 1)
			SetVelX(-100);

		if(GetPosY() < m_vWaypoints[m_nWaypoint]->locY - 1)
			SetVelY(100);
		else if(GetPosY() > m_vWaypoints[m_nWaypoint]->locY + 1)
			SetVelY(-100);

		CEntity::Update(fElapsedTime);
	}
}

void CNpcs::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "BATTLE_END" && pEvent->GetDestination() == this)
	{
		if(m_bIsHostile)
		{
			SetActive(false);
			SetRender(false);
		}
	}
}

void CNpcs::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_PLAYER || col->GetType() ==OBJ_UNDEFINE)
	{
		if(m_bIsHostile && GetActive())
			CSGD_EventSystem::GetInstance()->SendEventNow("INIT_BATTLE", &m_vUnitList, nullptr, this);
		RECT rTemp = col->GetCollisionRect();
		int nMid = rTemp.top + (rTemp.bottom - rTemp.top) / 2;
		if(GetCollisionRect().left > rTemp.right - 20 && GetCollisionRect().left < rTemp.right)
		{
			SetPosX(GetPosX() +1);
			SetVelX(0);
		}
		else if(GetCollisionRect().right < rTemp.left + 20 && GetCollisionRect().right > rTemp.left)
		{
			SetPosX(GetPosX() -1);
			SetVelX(0);
		}
		else if(GetCollisionRect().left > rTemp.right && GetCollisionRect().right < rTemp.left)
		{
			if(GetCollisionRect().bottom < rTemp.top + 20 && GetCollisionRect().bottom > rTemp.top)
			{
				if(GetVelY() > 0)
				{
					SetPosY(GetPosY() - 1);
					SetVelY(0);
				}
			}
			else if(GetCollisionRect().top > rTemp.bottom - 20 && GetCollisionRect().top < rTemp.bottom)
			{
				SetPosY(GetPosY() + 1);
				SetVelY(0);
			}
		}
		else if(GetCollisionRect().bottom < rTemp.top + 20 && GetCollisionRect().bottom > rTemp.top)
		{
			if(GetVelY() > 0)
			{
				SetPosY(GetPosY() - 1);
				SetVelY(0);
			}
		}
		else if(GetCollisionRect().top > rTemp.bottom - 20 && GetCollisionRect().top < rTemp.bottom)
		{
			SetPosY(GetPosY() + 1);

			SetVelY(0);
		}

	}

}

void CNpcs::AddWaypoint(float fX, float fY)
{
	SWaypoint* pTemp = new SWaypoint();
	pTemp->locX = fX;
	pTemp->locY = fY;
	m_vWaypoints.push_back(pTemp);
}
