#include "VictoryState.h"
#include "BattleState.h"
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
	m_pItemDistro = nullptr;
	m_bDoOnce = false;
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
	Sleep();
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
	m_pItemDistro = CBattleState::GetInstance()->GetItems();

}
void CVictoryState::Sleep( void )					
{ 
	m_nExperienceGained = 0;
	m_pPlayer = nullptr;

	m_nLevel = 0;
	m_nCurrentExp = 0;
	m_pItemDistro = nullptr;
	m_bDoOnce = false;
	m_nHealthMod	= 0;
	m_nAPMod		= 0;
	m_nAttackMod	= 0;

	CBattleState::GetInstance()->ClearItems();
}
bool CVictoryState::Input( void )					
{ 
	return true;
}
void CVictoryState::Update( float fElapsedTime )	
{
	m_fTimer -= fElapsedTime;
	if(m_bDoOnce == false && m_pItemDistro != nullptr)
	{
		for(auto i = m_pItemDistro->begin(); i != m_pItemDistro->end(); i++)
		{
			if(i->second.Item != nullptr)
			{
				if(i->second.Item->GetItemType() == IT_CONSUMABLE)
				{
					CConsumable* pTemp = reinterpret_cast<CConsumable*>(i->second.Item);
					if(pTemp != nullptr)
					{
						m_pPlayer->AddConsumableItem(pTemp, i->second.Owned);
					}
				}
			}
		}
		m_bDoOnce = true;
	}
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

	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Victory!"), 336, 15, 1.0f, D3DCOLOR_XRGB(0,0,0));
	woss << "Level: " << m_pPlayer->GetLevel() << "\nExperience: " << m_pPlayer->GetExperience();
	CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 272, 64, 0.75f, D3DCOLOR_XRGB(0,0,0));

	float fPercent = m_nCurrentExp / (m_nNeeded * 1.0f);

	if(m_bLeveled)
	{
		fPercent = m_pPlayer->GetExperience() /  (m_pPlayer->GetLevel() * m_pPlayer->GetLevel() * 100.0f);
		RECT rCurrent = {272, 128, 528, 141};
		pD3d->DrawRect(rCurrent, D3DCOLOR_XRGB(50,50,255));
		rCurrent.right = 272 + long(256 * fPercent);
		pD3d->DrawRect(rCurrent, D3DCOLOR_XRGB(50,255,255));

		rCurrent.right = 528;
		pD3d->DrawHollowRect(rCurrent, D3DCOLOR_XRGB(0,0,0), 3);

		woss.str(_T(""));
		woss << "HP: " << m_nCurrMaxHP << "  +" << m_pPlayer->GetMaxHealth() - m_nCurrMaxHP << "\nAP: " << m_nCurrMaxAP  << "  +" << m_pPlayer->GetMaxAP() - m_nCurrMaxAP << "\nAtk: " << m_nCurrAttack  << "  +" << m_pPlayer->GetAttack() - m_nCurrAttack << "\nStats: " << m_pPlayer->GetStats();
		CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 272, 172, 0.75f, D3DCOLOR_XRGB(0,0,0));
		woss.str(_T(""));
		woss << "\t" << m_nHealthMod << "\n\t" << m_nAPMod << "\n\t" << m_nAttackMod;
		CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 352, 172, 0.75f, D3DCOLOR_XRGB(0,0,0));
		RECT rTemp = {0,0,16,32};

		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 432, 172 + (GetCursorSelection() * 23), 1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2, D3DCOLOR_XRGB(255,255,255));
	}
	else
	{
		fPercent = m_pPlayer->GetExperience() /  (m_nNeeded * 1.0f);

		RECT rCurrent = {272, 128, 272 + long(256 * fPercent), 141};
		pD3d->DrawRect(rCurrent, D3DCOLOR_XRGB(50,50,255));

		rCurrent.right = 528;
		pD3d->DrawHollowRect(rCurrent, D3DCOLOR_XRGB(0,0,0), 3);
	}

	///////////////////// ITEMS OBTAINED SECTION //////////////////////////

	if(m_pItemDistro != nullptr)
	{
		CGame::GetInstance()->GetFont("Arial")->Draw(_T("Items Obtained:"), 272, 300, 0.75f, D3DCOLOR_XRGB(0,0,0));
		if(m_pItemDistro->size() > 0)
		{
			int nCount = 0;
			for(auto i = m_pItemDistro->begin(); i != m_pItemDistro->end(); i++)
			{
				if(i->second.Item != nullptr)
				{
					if(i->second.Item->GetItemType() == IT_CONSUMABLE)
					{
						CConsumable* pTemp = reinterpret_cast<CConsumable*>(i->second.Item);
						if(pTemp != nullptr)
						{
							woss.str(_T(""));
							woss << pTemp->GetName().c_str() << "  x" << i->second.Owned;
							CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 272, 317 + (nCount * 17), 0.75f, D3DCOLOR_XRGB(0,0,0));
						}
					}
				}
				nCount++;
			}
		}
		else
			CGame::GetInstance()->GetFont("Arial")->Draw(_T("Nothing"), 272, 317, 0.75f, D3DCOLOR_XRGB(0,0,0));
	}
}