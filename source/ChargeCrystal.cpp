#include "ChargeCrystal.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"

CChargeCrystal::CChargeCrystal(void)
{
	m_fMoveSpeed = 100.0f;
	m_fTimer = 3.0f;
	m_nSuccess = 0;
	m_fRadius = 75.0f;
	m_nChargeImgID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/MiniGames/PoA_ChargeCrystal.png"));
	m_fRotation = 0.0f;
}


CChargeCrystal::~CChargeCrystal(void)
{

}

void CChargeCrystal::Render()
{

}

void CChargeCrystal::Update(float fElpasedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	m_fTimer -= fElpasedTime;





	if(m_fTimer < 0.0f)
	{

	}
}

void CChargeCrystal::ResetSkill()
{
	m_fRotation = 0.0f;
	m_fMoveSpeed = 100.0f;
	m_fTimer = 3.0f;
	m_nSuccess = 0;
	m_fRadius = 75.0f;
}
