#include "Minigames.h"
#include "Units.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"

CMiniGames::CMiniGames(void)
{
	m_pMaster = nullptr;
	m_nCost = 0;
}

CMiniGames::~CMiniGames(void)
{
	SetOwner(nullptr);
}

void CMiniGames::Update(float fElapsedTime)
{

}

void CMiniGames::Render()
{
}

void CMiniGames::SetOwner(CUnits* pOwner)
{
	m_pMaster = pOwner;
}