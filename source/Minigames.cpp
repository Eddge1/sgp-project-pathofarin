#include "Minigames.h"
#include "Units.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"

CMiniGames::CMiniGames(void)
{
	m_pMaster = nullptr;
	m_bRight = true;
	m_szAbilityName = "Undefined";
}


CMiniGames::~CMiniGames(void)
{
	SetOwner(nullptr);
}

CMiniGames* CMiniGames::GetSubMenu(int nID)
{
	return m_vSubSkills[nID];
}

void CMiniGames::Update(float fElapsedTime)
{

}

void CMiniGames::Render()
{
}

void CMiniGames::SetOwner(CUnits* pOwner)
{
	if(m_pMaster)
	{
		m_pMaster->Release();
		m_pMaster = nullptr;
	}

	m_pMaster = pOwner;
	if(m_pMaster)
		m_pMaster->AddRef();
}