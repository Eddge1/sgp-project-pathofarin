#include "Npcs.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"


CNpcs::CNpcs(void)
{
	SetType(OBJ_NPC);
	m_bContainsUnits = false;
	m_bIsHostile = false;

	CSGD_EventSystem::GetInstance()->RegisterClient("VICTORY", this);
}


CNpcs::~CNpcs(void)
{
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

	CEntity::Update(fElapsedTime);
}

void CNpcs::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "VICTORY" && pEvent->GetDestination() == this)
	{
		if(m_bIsHostile)
			SetActive(false);
	}
}

void CNpcs::HandleCollision(CObjects* col)
{
	if(col->GetType() == OBJ_PLAYER)
	{
		if(m_bIsHostile && GetActive())
			CSGD_EventSystem::GetInstance()->SendEventNow("INIT_BATTLE", &m_vUnitList, nullptr, this);
	}

}