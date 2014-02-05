#include "VictoryState.h"
#include "GamePlayState.h"
#include "Game.h"
#include "BitmapFont.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

#include <sstream>

CVictoryState* CVictoryState::GetInstance( void )
{
	static CVictoryState s_Instance;

	return &s_Instance;
}

CVictoryState::CVictoryState(void)
{
	CVictoryState::GetInstance();
	m_pPlayer = nullptr;
	m_bLeveled = false;

	SetBackgroundMusic(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));
	SetSFXID(-1);
	m_fTimer = 0.1f;
	m_nCurrMaxHP = 0;
	m_nCurrMaxAP = 0;
	m_nCurrAttack = 0;
	m_nHealthMod = 0;
	m_nAPMod = 0;
	m_nAttackMod = 0;
	SetCursorSelection(0);
	m_nMaxStat = 0;
}

CVictoryState::~CVictoryState(void)
{

}

void CVictoryState::Activate( void )				
{ 
	m_bLeveled = false;
	m_pPlayer = reinterpret_cast<CPlayerUnit*>(CGamePlayState::GetInstance()->GetPlayerUnit());
	if(m_pPlayer != nullptr)
	{
		m_nLevel = m_pPlayer->GetLevel();
		m_nCurrentExp = m_pPlayer->GetExperience();
		m_nNeeded = m_nLevel * m_nLevel * 100;
		m_nCurrMaxHP	= m_pPlayer->GetMaxHealth();
		m_nCurrMaxAP	= m_pPlayer->GetMaxAP();
		m_nCurrAttack	= m_pPlayer->GetAttack();
		m_nHealthMod	= 0;
		m_nAPMod		= 0;
		m_nAttackMod	= 0;
	}
	m_fTimer		= 0.1f;

}
void CVictoryState::Sleep( void )					
{ 
	m_nExperienceGained = 0;
	m_pPlayer = nullptr;

	m_nLevel = 0;
	m_nCurrentExp = 0;
}
bool CVictoryState::Input( void )					
{ 
	return true;
}
void CVictoryState::Update( float fElapsedTime )	
{
	m_fTimer -= fElapsedTime;
	if(m_nExperienceGained > 0)
	{
		CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

		if(m_pPlayer != nullptr && m_pPlayer->GetType() == OBJ_PLAYER_UNIT)
		{
			if(pDI->KeyPressed(DIK_RETURN))
			{
				m_pPlayer->GiveExperience(m_nExperienceGained);
				m_nExperienceGained = 0;
			}
			else
			{
				if(m_fTimer <= 0.0f)
				{
					m_pPlayer->GiveExperience(1);
					m_nExperienceGained--;
					m_fTimer = 0.01f;
				}
			}
			if(m_nLevel < m_pPlayer->GetLevel())
				m_bLeveled = true;
			if(m_nExperienceGained <= 0)
			{
				m_nMaxStat = m_pPlayer->GetStats();

			}
		}
	}
	else if(m_bLeveled)
	{
		CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
		if(m_pPlayer->GetStats() < 1)
		{
			if(pDI->KeyPressed(DIK_RETURN) || pDI->KeyPressed(DIK_ESCAPE))
				CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		}

		if(pDI->KeyPressed(DIK_UPARROW))
		{
			SetCursorSelection(GetCursorSelection() - 1);
			if(GetCursorSelection() < 0)
				SetCursorSelection(0);
		}
		else if(pDI->KeyPressed(DIK_DOWNARROW))
		{
			SetCursorSelection(GetCursorSelection() + 1);
			if(GetCursorSelection() > 2)
				SetCursorSelection(2);
		}
		if(pDI->KeyPressed(DIK_LEFTARROW))
		{
			if(m_pPlayer->GetStats() < m_nMaxStat)
			{
				switch (GetCursorSelection())
				{
				case 0:
					if(m_nHealthMod > 0)
					{
						if(m_pPlayer->decrHealth())
							m_nHealthMod--;
					}
					break;
				case 1:
					if(m_nAPMod > 0)
					{
						if(m_pPlayer->decrAbility())
							m_nAPMod--;
					}
					break;
				case 2:
					if(m_nAttackMod > 0)
					{
						if(m_pPlayer->decrAttack())
							m_nAttackMod--;

					}
					break;
				default:
					break;
				}
			}
		}
		else if(pDI->KeyPressed(DIK_RIGHTARROW))
		{
			if(m_pPlayer->GetStats() > 0)
			{
				switch (GetCursorSelection())
				{
				case 0:
					if(m_pPlayer->incrHealth())
						m_nHealthMod++;
					break;
				case 1:
					if(m_pPlayer->incrAbility())
						m_nAPMod++;
					break;
				case 2:
					if(m_pPlayer->incrAttack())
						m_nAttackMod++;
					break;
				default:
					break;
				}
			}
		}


	}
	else
	{
		CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

		if(pDI->KeyPressed(DIK_RETURN) || pDI->KeyPressed(DIK_ESCAPE))
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
	}
}
void CVictoryState::Render( void )					
{ 
	std::wostringstream woss;
	CSGD_Direct3D* pD3d = CSGD_Direct3D::GetInstance();

	CGame::GetInstance()->GetFont2()->Draw(_T("Victory!"), 336, 15, 1.0f, D3DCOLOR_XRGB(0,0,0));

	woss << "Level: " << m_nLevel << "\nExperience: " << m_nCurrentExp;
	CGame::GetInstance()->GetFont2()->Draw(woss.str().c_str(), 128, 64, 0.75f, D3DCOLOR_XRGB(0,0,0));
	woss.str(_T(""));
	woss << "Level: " << m_pPlayer->GetLevel() << "\nExperience: " << m_pPlayer->GetExperience();
	CGame::GetInstance()->GetFont2()->Draw(woss.str().c_str(), 512, 64, 0.75f, D3DCOLOR_XRGB(0,0,0));

	float fPercent = m_nCurrentExp / (m_nNeeded * 1.0f);
	RECT rTemp = {128, 128, 128 + (128 * fPercent),160};
	pD3d->DrawRect(rTemp, D3DCOLOR_XRGB(50,50,255));

	rTemp.right = 256;
	pD3d->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0), 3);

	if(m_bLeveled)
	{
		fPercent = m_pPlayer->GetExperience() /  (m_pPlayer->GetLevel() * m_pPlayer->GetLevel() * 100.0f);

		RECT rCurrent = {512, 128, 640, 160};
		pD3d->DrawRect(rCurrent, D3DCOLOR_XRGB(50,50,255));
		rCurrent.right = 512 + (128 * fPercent);
		pD3d->DrawRect(rCurrent, D3DCOLOR_XRGB(50,255,255));

		rCurrent.right = 640;
		pD3d->DrawHollowRect(rCurrent, D3DCOLOR_XRGB(0,0,0), 3);

		woss.str(_T(""));
		woss << "HP: " << m_nCurrMaxHP << "\nAP: " << m_nCurrMaxAP << "\nAtk: " << m_nCurrAttack;
		CGame::GetInstance()->GetFont2()->Draw(woss.str().c_str(), 128, 172, 0.75f, D3DCOLOR_XRGB(0,0,0));

		woss.str(_T(""));
		woss << "HP: " << m_pPlayer->GetMaxHealth() << "\nAP: " << m_pPlayer->GetMaxAP() << "\nAtk: " << m_pPlayer->GetAttack() << "\nStats: " << m_pPlayer->GetStats();
		CGame::GetInstance()->GetFont2()->Draw(woss.str().c_str(), 512, 172, 0.75f, D3DCOLOR_XRGB(0,0,0));
		woss.str(_T(""));
		woss << "\t" << m_nHealthMod << "\n\t" << m_nAPMod << "\n\t" << m_nAttackMod;
		CGame::GetInstance()->GetFont2()->Draw(woss.str().c_str(), 576, 172, 0.75f, D3DCOLOR_XRGB(0,0,0));
		RECT rTemp = {0,0,16,32};

		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 624, 172 + (GetCursorSelection() * 21), 1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2, D3DCOLOR_XRGB(255,255,255));
	}
	else
	{
		fPercent = m_pPlayer->GetExperience() /  (m_nNeeded * 1.0f);

		RECT rCurrent = {512, 128, 512 + (128 * fPercent), 160};
		pD3d->DrawRect(rCurrent, D3DCOLOR_XRGB(50,50,255));

		rCurrent.right = 640;
		pD3d->DrawHollowRect(rCurrent, D3DCOLOR_XRGB(0,0,0), 3);
	}


}