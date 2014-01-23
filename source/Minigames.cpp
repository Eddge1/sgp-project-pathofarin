#include "Minigames.h"
#include "Units.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"

CMiniGames::CMiniGames(void)
{
	m_pMaster = nullptr;
	m_bRight = true;
	m_szAbilityName = "Undefined";
	RECT rTemp = {200,20,615,120};
	m_rCollisionZones.push_back(rTemp);
	rTemp.right = rTemp.left + 30;
	m_rCollisionZones.push_back(rTemp);
	rTemp.left = 285;
	rTemp.right = 315;
	m_rCollisionZones.push_back(rTemp);
	rTemp.left = 400;
	rTemp.right = 430;
	m_rCollisionZones.push_back(rTemp);
	rTemp.left = 515;
	rTemp.right = 545;
	m_rCollisionZones.push_back(rTemp);
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

	if(!m_bFailed)
	{
		if(m_rCollisionZones[1].right >=615)
			m_bRight = false;
		else if(m_rCollisionZones[1].left <=200)
			m_bRight = true;

		if(m_bRight)
			m_rCollisionZones[1].left += long(100 * fElapsedTime);
		else
			m_rCollisionZones[1].left -= long(100 * fElapsedTime);

		m_rCollisionZones[1].right = m_rCollisionZones[1].left + 30;
	}

	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

}

void CMiniGames::Render()
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	for(unsigned int i = 0; i < m_rCollisionZones.size(); i++)
	{
		pD3D->DrawHollowRect(m_rCollisionZones[i], D3DCOLOR_XRGB(0,0,0));
	}
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