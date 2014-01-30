#include "BattleState.h"
#include "Units.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "RenderManager.h"
#include "AnimationSystem.h"
#include "Game.h"
#include "Objects.h"
#include "PlayerUnit.h"
#include "EnemyUnit.h"
#include "AIController.h"
#include "BasicAttack.h"
#include "Npcs.h"
#include <algorithm>
using namespace std;

// GetInstance
CBattleState* CBattleState::GetInstance( void )
{
	static CBattleState s_Instance;

	return &s_Instance;
}

CBattleState::CBattleState(void)
{
	m_nTarget = 0;
	m_nTurn = 0;
	m_pSender = nullptr;
	m_bDefeat = false;
	m_bVictory = false;
	m_fEndBatleTimer = 0.0f;
	m_fCancelTimer = 2.0f;
	m_nForestBattleID = -1;
}

CBattleState::~CBattleState(void)
{
	for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		m_vBattleUnits[i]->Release();

}

void CBattleState::Activate(void)
{
	if(GetBackgroundMusic() != -1)
	{
		int nTemp = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_Battle.xwm"));
		SetBackgroundMusic(nTemp);
		CSGD_XAudio2::GetInstance()->MusicPlaySong(nTemp);
		m_nDefeatMusic = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_Defeat.xwm"));
		m_nVictoryMusic = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_Victory.xwm"));
	}

	m_nMenuImage =			CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_BattleMenu.png"));
	m_nMenuSelectionImage = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_SelectionMenu.png"));
	m_nForestBattleID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Backgrounds/Forest_Battle.png"));
	m_pFont = CGame::GetInstance()->GetFont();
	m_bDefeat = false;
	m_bVictory = false;
	m_fEndBatleTimer = 0.0f;
	m_fCancelTimer = 2.0f;

	// TEMP ENEMIES/Player
	m_eCurrentPhase = BP_INIT;
}

void CBattleState::Sleep(void)
{
	m_eCurrentPhase = BP_INIT;

	for(int i = int(m_vBattleUnits.size() - 1); i >= 0; i--)
	{
		m_vBattleUnits[i]->Release();
		m_vBattleUnits.pop_back();
	}
	for(int i = 0; i < int(m_vText.size()); i++)
		delete m_vText[i];

	m_vText.clear();

	SetSender(nullptr);
	SetPlayer(nullptr);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuSelectionImage);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenuImage);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nForestBattleID);


	m_nMenuImage = -1;
	m_nMenuSelectionImage = -1;
	m_nForestBattleID = -1;
}

bool CBattleState::Input(void)
{
	if(m_vBattleUnits.size() > 0)
	{
		if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
		{
			CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(m_vBattleUnits[m_nTurn]);
			if(pTemp != nullptr)
			{
				if(pTemp->GetReady() && pTemp->GetCasting() == false)
				{
					if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_W ) == true )
						GetNextTarget();
					else if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_S ) == true )
						GetPreviousTarget();
				}
			}
		}
	}
	return true;
}

void CBattleState::Update(float fElapsedTime)
{

	for(int i = 0; i < (int)m_vText.size(); )
	{
		m_vText[i]->m_fTimer -= fElapsedTime;
		m_vText[i]->m_fLocY -= (20 * fElapsedTime);
		if(m_vText[i]->m_fTimer <= 0.0f)
		{
			delete m_vText[i];
			m_vText.erase(m_vText.begin() + i);
		}
		else
			i++;
	}

	if(m_bVictory || m_bDefeat)
		m_fEndBatleTimer -= fElapsedTime;


	switch (m_eCurrentPhase)
	{
	case CBattleState::BP_INIT:
		Initialize();
		break;
	case CBattleState::BP_BATTLE:
		Battle(fElapsedTime);
		break;
	case CBattleState::BP_END:
		EndBattle();
		break;
	default:
		break;
	}
}

void CBattleState::Render(void)
{
	CSGD_TextureManager*	pTM	= CSGD_TextureManager::GetInstance();
	CSGD_Direct3D*			pD3D = CSGD_Direct3D::GetInstance();


	//Temp drawing the UI
	pTM->Draw(m_nForestBattleID, 0, 0, 2.0f, 2.0f);
	pTM->Draw(m_nMenuImage, 0,472);
	pTM->Draw(m_nMenuSelectionImage, 272,408);

	// Printing out variables
	std::wostringstream woss;

	m_pFont->Draw(_T("HP:"), 660, 500, 0.8f, D3DCOLOR_XRGB(0, 0, 255));
	m_pFont->Draw(_T("AP:"), 660, 520, 0.8f, D3DCOLOR_XRGB(0, 0, 255));

	if(m_vBattleUnits.size() > 0)
	{
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
			{
				woss << m_vBattleUnits[i]->GetHealth();
				m_pFont->Draw( woss.str().c_str(), 700, 500, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
				woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
				woss << m_vBattleUnits[i]->GetAbilityPoints();
				m_pFont->Draw( woss.str().c_str(), 700, 520, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
				woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			}

			RECT Player = { long(m_vBattleUnits[i]->GetPosX()), long(m_vBattleUnits[i]->GetPosY()), long(m_vBattleUnits[i]->GetPosX()) + 20, long(m_vBattleUnits[i]->GetPosY()) + 20 };
			pD3D->DrawHollowRect(Player, D3DCOLOR_XRGB( 0,0,0 ));

		}

		if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
		{
			m_pFont->Draw(_T("HP:"), 10, 500, 0.8f, D3DCOLOR_XRGB(0, 0, 255));
			m_pFont->Draw(_T("AP:"), 10, 520, 0.8f, D3DCOLOR_XRGB(0, 0, 255));

			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTarget]->GetHealth();
			m_pFont->Draw( woss.str().c_str(), 50, 500, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTarget]->GetAbilityPoints();
			m_pFont->Draw( woss.str().c_str(), 50, 520, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTarget]->GetName().c_str();
			m_pFont->Draw( woss.str().c_str(), 50, 480, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
		}
		else
		{
			m_pFont->Draw(_T("HP:"), 10, 500, 0.8f, D3DCOLOR_XRGB(0, 0, 255));
			m_pFont->Draw(_T("AP:"), 10, 520, 0.8f, D3DCOLOR_XRGB(0, 0, 255));

			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTurn]->GetHealth();
			m_pFont->Draw( woss.str().c_str(), 50, 500, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTurn]->GetAbilityPoints();
			m_pFont->Draw( woss.str().c_str(), 50, 520, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTurn]->GetName().c_str();
			m_pFont->Draw( woss.str().c_str(), 50, 480, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
		}

		RECT temp = { long(m_vBattleUnits[m_nTurn]->GetPosX() + 5),  long(m_vBattleUnits[m_nTurn]->GetPosY() - 10),  long(m_vBattleUnits[m_nTurn]->GetPosX() + 10),  long(m_vBattleUnits[m_nTurn]->GetPosY() - 5) };
		pD3D->DrawHollowRect(temp, D3DCOLOR_XRGB( 0,0,255 ));
		if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
		{
			CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(m_vBattleUnits[m_nTurn]);
			if(pTemp != nullptr)
			{
				if(pTemp->GetReady())
				{
					RECT temp = { long(m_vBattleUnits[m_nTarget]->GetPosX() + 5),  long(m_vBattleUnits[m_nTarget]->GetPosY() - 10),  long(m_vBattleUnits[m_nTarget]->GetPosX() + 10),  long(m_vBattleUnits[m_nTarget]->GetPosY() - 5) };
					pD3D->DrawHollowRect(temp, D3DCOLOR_XRGB( 0,0,0 ));
					if(pTemp->GetCasting())
					{
						if(pTemp->GetInSubMenu())
						{
							pTemp->GetSkill(pTemp->GetMenuID())->GetCommand(pTemp->GetSkillID())->GetMiniGame()->Render();
						}
						else
						{
							pTemp->GetSkill(pTemp->GetMenuID())->GetMiniGame()->Render();

						}
					}
				}

				vector<CCommands*> vTemp;
				if(!pTemp->GetInSubMenu())
					vTemp = *(pTemp->GetCommands());
				else
					vTemp = *(pTemp->GetSkill(pTemp->GetMenuID())->GetCommands());
				for(unsigned int i = 0; i < vTemp.size(); i++)
				{
					woss.str(_T(""));
					woss << vTemp[i]->GetName().c_str();
					m_pFont->Draw(woss.str().c_str(), 360, 480 + (i * 28), 1.0f, D3DCOLOR_XRGB(0,0,0));
				}
				RECT rTemp = {};
				rTemp.top = 490 + (pTemp->GetSkillID() * 28);
				rTemp.bottom = rTemp.top + 10;
				rTemp.left = 348;
				rTemp.right = 358;
				pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB( 0,0,255 ));

			}
		}
		int nImageID = -1;
		CAnimation* pAnim; 
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetRender())
			{
				if (m_vBattleUnits[i]->GetType() != OBJ_UNDEFINE && m_vBattleUnits[i]->GetType() != OBJ_WARP)
				{
					pAnim = CAnimationSystem::GetInstance()->GetAnimation(m_vBattleUnits[i]->GetAnimInfo()->GetCurrentAnimation());
					nImageID = pAnim->GetImageID();
				}
				float PosX = m_vBattleUnits[i]->GetPosX(); 
				float PosY = m_vBattleUnits[i]->GetPosY();
				if (nImageID != -1)
				{
					CAnimationSystem::GetInstance()->Render(m_vBattleUnits[i]->GetAnimInfo(), PosX, PosY, 1.0f, D3DCOLOR_XRGB(255, 255, 255));
				}
				nImageID = -1;
			}
		}

		for(int i = 0; i < (int)m_vText.size(); i++)
			m_pFont->Draw(m_vText[i]->szText.str().c_str(), (int)m_vText[i]->m_fLocX, (int)m_vText[i]->m_fLocY, 1.0f, m_vText[i]->Color);

		if(m_bVictory)
		{
			woss.str(_T(""));
			woss << "Victory!";
			m_pFont->Draw(woss.str().c_str(), 380, 15,1.0f, D3DCOLOR_XRGB(0,0,255));
			// Display what they've won. TODO; come back later and fix.

			RECT temp;
			temp.left = 300;
			temp.right = 500;
			temp.top = 100;
			temp.bottom = 300;
			CSGD_Direct3D::GetInstance()->DrawHollowRect(temp,  D3DCOLOR_XRGB(0,0,0));
			CBitmapFont* pFont = CGame::GetInstance()->GetFont();
			pFont->Draw( _T("Items: 0"), 320, 120, 0.8f, D3DCOLOR_XRGB(0,0,255));
			pFont->Draw( _T("Exp: 0"), 320, 150, 0.8f, D3DCOLOR_XRGB(0,0,255));

		}
		else if(m_bDefeat)
		{
			woss.str(_T(""));
			woss << "Defeated!";
			m_pFont->Draw(woss.str().c_str(), 380, 15,1.0f, D3DCOLOR_XRGB(0,0,255));
		}
	}
}

bool SortSpeed(CUnits *l, CUnits *r)
{
	return l->GetSpeed() > r->GetSpeed();
}


void CBattleState::Initialize(void)
{
	SetPlayer(CGamePlayState::GetInstance()->GetPlayerUnit());
	m_vBattleUnits.push_back(m_pPlayerUnit);
	m_pPlayerUnit->AddRef();

	CNpcs* temp = reinterpret_cast<CNpcs*>(m_pSender);
	if(temp != nullptr)
	{
		for (unsigned int i = 0; i < temp->GetUnits().size(); i++)
		{
			m_vBattleUnits.push_back(temp->GetUnit(i));
			temp->GetUnit(i)->AddRef();
		}
	}


	//m_vBattleUnits.push_back(CreateTempEnemy("Enemy 1", 100.0f, 100.0f, 12, 5, 20));
	//m_vBattleUnits.push_back(CreateTempEnemy("Enemy 2", 200.0f, 200.0f, 5, 90, 15));
	//m_vBattleUnits.push_back(CreateTempEnemy("Enemy 3", 100.0f, 300.0f, 9, 200, 150));

	sort(m_vBattleUnits.begin(), m_vBattleUnits.end(), SortSpeed); 

	GetNextTarget();

	m_eCurrentPhase = BP_BATTLE;
}

void CBattleState::Battle(float fElapsedTime)
{
	if(m_eCurrentPhase == BP_BATTLE)
	{
		for (unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			m_vBattleUnits[i]->Update(fElapsedTime);

		}
		CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(m_vBattleUnits[m_nTurn]);
		if(pTemp != nullptr)
		{
			if(pTemp->GetReady())
			{

			}
		}
		if(m_vBattleUnits[m_nTurn]->GetTurn() == false)
		{
			if(m_vBattleUnits.size() == 1)
			{
				if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
					m_eCurrentPhase = BP_END;
			}

			m_nTurn++;
			for(unsigned int i = 0; i < m_vBattleUnits.size();)
			{
				if(m_vBattleUnits[i]->GetHealth() < 1)
				{
					if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
						m_eCurrentPhase = BP_END;
					m_vBattleUnits[i]->Release();
					m_vBattleUnits.erase(m_vBattleUnits.begin() + i);
					GetNextTarget();
				}
				else
					i++;
			}
			if(m_nTurn >= (int)m_vBattleUnits.size())
				m_nTurn = 0;
			if(m_eCurrentPhase != BP_END)
				m_vBattleUnits[m_nTurn]->SetTurn(true);
		}
	}
}

void CBattleState::EndBattle(void)
{
	if(!m_bVictory && !m_bDefeat)
	{
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
			{
				m_fEndBatleTimer = 5.0f;
				m_bVictory = true;
				CSGD_XAudio2::GetInstance()->MusicStopSong(GetBackgroundMusic());
				CSGD_XAudio2::GetInstance()->MusicPlaySong(m_nVictoryMusic);

				return;
			}
			else if(i == m_vBattleUnits.size() - 1)
			{
				m_fEndBatleTimer = 5.0f;
				m_bDefeat = true;
				CSGD_XAudio2::GetInstance()->MusicStopSong(GetBackgroundMusic());
				CSGD_XAudio2::GetInstance()->MusicPlaySong(m_nDefeatMusic);
				return;
			}
		}
	}
	if(m_fEndBatleTimer <= 0.0f)
	{
		if(m_bDefeat)
		{
			CSGD_XAudio2::GetInstance()->MusicStopSong(m_nDefeatMusic);
			CSGD_EventSystem::GetInstance()->SendEventNow("GAME_OVER", nullptr, m_pSender, nullptr);
		}
		else
		{
			CSGD_XAudio2::GetInstance()->MusicStopSong(m_nVictoryMusic);
		}
		CSGD_EventSystem::GetInstance()->SendEventNow("BATTLE_END", nullptr, m_pSender, nullptr);
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
	}

}

CEnemyUnit* CBattleState::CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp)
{
	CEnemyUnit* temp = new CEnemyUnit;
	CAIController* tempAI = new CAIController;
	CBasicAttack* tempAtk = new CBasicAttack;
	tempAI->AddMinigame(tempAtk);
	tempAI->MakeOwner(temp);
	temp->SetAIController(tempAI);
	temp->SetMaxHealth(hp);
	temp->SetMaxAP(mp);
	temp->SetPosX(X);
	temp->SetPosY(Y);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(speed);
	temp->SetTurn(false);
	temp->SetName(input);

	return temp;
}

void CBattleState::GetNextTarget(void)
{
	if(m_vBattleUnits.size() < 2)
	{
		if(m_eCurrentPhase != BP_INIT)
			m_eCurrentPhase = BP_END;
		return;
	}

	do 
	{
		m_nTarget++;
		if(unsigned int(m_nTarget) >= m_vBattleUnits.size())
			m_nTarget = 0;
	}
	while(m_vBattleUnits[m_nTarget]->GetType() == OBJ_PLAYER_UNIT);

}

void CBattleState::GetPreviousTarget(void)
{
	if(m_vBattleUnits.size() < 2)
	{
		if(m_eCurrentPhase != BP_INIT)
			m_eCurrentPhase = BP_END;
		return;
	}
	do 
	{
		m_nTarget--;
		if(m_nTarget < 0)
			m_nTarget = m_vBattleUnits.size() - 1;
	}
	while(m_vBattleUnits[m_nTarget]->GetType() == OBJ_PLAYER_UNIT);

}

void CBattleState::SetSender(CObjects* pSender)
{
	if(m_pSender != nullptr)
		m_pSender->Release();

	m_pSender = pSender;

	if(m_pSender != nullptr)
		m_pSender->AddRef();
}

void CBattleState::SetPlayer(CUnits* pPlayer)
{
	if(m_pPlayerUnit != nullptr)
		m_pPlayerUnit->Release();

	m_pPlayerUnit = pPlayer;

	if(m_pPlayerUnit != nullptr)
		m_pPlayerUnit->AddRef();
}

CUnits* CBattleState::GetCurrentTarget(void)
{
	return m_vBattleUnits[m_nTarget];
}

void CBattleState::AddFloatingText(float posX, float posY, DWORD dColor, std::wostringstream &szText)
{
	FloatingText* ftTemp = new FloatingText;

	ftTemp->m_fLocX = posX;
	ftTemp->m_fLocY = posY;
	ftTemp->Color = dColor;
	ftTemp->szText << szText.str();
	ftTemp->m_fTimer = 1.5f;
	m_vText.push_back(ftTemp);
}
