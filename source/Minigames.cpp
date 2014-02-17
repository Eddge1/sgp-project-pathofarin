#include "Minigames.h"
#include "Projectile.h"
#include "Units.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"


CMiniGames::CMiniGames(void)
{
	m_pMaster = nullptr;
	m_nCost = 0;
	m_bTutorial = false;
	m_pSkill = nullptr;
	m_bAOE = false;
	m_nSFXID			= CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/MiniGame/POA_SuccessCharge.wav"));
	m_nCriticalSFXID	= CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/MiniGame/POA_CritBar.wav"));
	m_nFailSFXID		= CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/MiniGame/POA_Fail.wav"));
	m_eType = MG_OFFENSIVE;
	m_bDamage = true;
}

CMiniGames::~CMiniGames(void)
{
	CSGD_EventSystem::GetInstance()->UnregisterClientAll(this);
	SetOwner(nullptr);
	if(m_pSkill != nullptr)
		m_pSkill->Release();
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


// fx1 and fy1 are the current targets, fx2 and fy2 is for the other.
float CMiniGames::ScalarDistance(float fx1, float fy1, float fx2, float fy2)
{
	float dx = fx2 - fx1;
	dx *= dx;
	float dy =  fy2 - fy1;
	dy *= dy;
	return float(abs(sqrtf(dx + dy)));
}