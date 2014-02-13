#include "TutorialBattle.h"
#include "EnemyUnit.h"
#include "PlayerUnit.h"
#include "AIController.h"
#include "Game.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "Units.h"
#include "BattleState.h"
#include <algorithm>
#include "AnimationSystem.h"

CTutorialBattle::CTutorialBattle(void)
{
	m_pFont = CGame::GetInstance()->GetFont("Arial");
	m_vBattleUnits.clear();
	m_vText.clear();

	m_pPlayerUnit = nullptr;
	m_eCurrentPhase = BP_INIT;

	SetBackgroundMusic(CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_Battle.xwm")));
	m_nForestBattleID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Backgrounds/Forest_Battle.png"));
	m_nMenuImage			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_BattleMenu.png"));
	m_nMenuSelectionImage	= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_SelectionMenu.png"));
	m_nVictoryMusic			= CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_Victory.xwm"));
	m_nDefeatMusic			= CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_Defeat.xwm"));
	m_nSelectionChange  	= CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_SelectionMove.wav"));
	m_nCombArrowImgID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/MiniGames/PoA_MoveArrow.png"));
	m_nHealthBar = -1;
	m_nAPBar = -1;

	m_bVictory = false;
	m_bDelayed = false;
	m_bMenu = false;
	m_bPlayerTurn = false;

	m_nTarget = 0;
	m_nTurn = 0;
	m_fEndBatleTimer = 0.0f;
	m_fCancelTimer = 0.0f;
	m_fDelayTurn = 0.0f;

	m_nTopMenuSelection = 0;
	m_bSubMenuSelection = false;
	m_bPlayerUnitSelection = false;
	m_nSubMenuSelect = 0;
	m_bPlayerConduct = false;

	m_pTrigger		= nullptr;
	m_pCombo		= nullptr;
	m_pAttack		= nullptr;
	m_bExplainOnceTurn = true;
}
CTutorialBattle::~CTutorialBattle(void)
{
	Sleep();
}
CTutorialBattle* CTutorialBattle::GetInstance( void )
{
	static CTutorialBattle s_Instance;

	return &s_Instance;

}
void CTutorialBattle::Activate( void )	
{
	m_pTrigger		= new CTriggerSpree();
	m_pTrigger->SetCost(5000);
	m_pTrigger->SetTutorial(true);
	m_pCombo		= new CComboGame();
	m_pCombo->SetTutorial(true);
	m_pCombo->SetCost(5000);

	m_pAttack		= new CBasicAttack();
	m_pAttack->SetTutorial(true);
	m_pAttack->SetCost(0);
	m_bExplainOnceTurn = true;

	CSGD_XAudio2::GetInstance()->MusicPlaySong(GetBackgroundMusic());
	m_bVictory = false;
	m_fEndBatleTimer = 0.0f;
	m_fCancelTimer = 2.0f;
	m_bDelayed = false;
	m_eCurrentPhase = BP_INIT;
	m_fDelayTurn = 0.0f;
	m_bPlayerTurn = false;
	if(m_bMenu)
		CAnimationSystem::GetInstance()->LoadAnimations();

	m_nTopMenuSelection = 0;
	m_bSubMenuSelection = false;
	m_bPlayerUnitSelection = false;
	m_nSubMenuSelect = 0;
	m_bPlayerConduct = false;
	m_bExplanation = false;
	timer = 0.0f;
	m_bSendOncePerTurn = false;
	m_fEnemyDelay = 1.0f;

	m_bExplainDodge = true;
	m_bExplainAttack = true;
	m_bExplainTrigger = true;
	m_bExplainCombo = true;


}				
void CTutorialBattle::Sleep( void )	
{
	m_eCurrentPhase = BP_INIT;
	m_fDelayTurn = 0.0f;
	m_bDelayed = false;
	for(int i = int(m_vBattleUnits.size() - 1); i >= 0; i--)
	{
		m_vBattleUnits[i]->Release();
		m_vBattleUnits.pop_back();
	}
	for(int i = 0; i < int(m_vText.size()); i++)
		delete m_vText[i];

	m_vText.clear();

	if(m_bMenu)
		CAnimationSystem::GetInstance()->DeleteInstance();

	if(m_pPlayerUnit != nullptr)
		m_pPlayerUnit->Release();
	m_pPlayerUnit = nullptr;
	m_bMenu = false;
	m_nTopMenuSelection = 0;
	m_bSubMenuSelection = false;
	m_bPlayerUnitSelection = false;
	m_nSubMenuSelect = 0;
	m_bPlayerConduct = false;
	m_bExplanation = false;
	timer = 0.0f;
	m_bSendOncePerTurn = false;
	m_bExplainOnceTurn = true;

	m_fEnemyDelay = 1.0f;

	m_pTrigger		= nullptr;
	m_pCombo		= nullptr;
	m_pAttack		= nullptr;
}				
bool CTutorialBattle::Input( void )	
{
	if(m_vBattleUnits.size() > 0)
	{
		if(m_bExplanation == false)
		{
			if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
			{
				CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(m_vBattleUnits[m_nTurn]);
				if(pTemp != nullptr)
				{
					if(pTemp->GetReady() && pTemp->GetCasting() == false)
					{
						if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_W ) == true )
						{
							CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionChange);
							GetNextTarget();
						}
						else if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_S ) == true )
						{
							CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionChange);
							GetPreviousTarget();
						}
					}
				}
			}
		}
		else
		{
			if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_RETURN ) == true )
			{
				m_bExplanation = false;
				if(m_bExplainDodge)
					m_bExplainDodge = false;
			}

		}
	}
	return true;
}					
void CTutorialBattle::Update( float fElapsedTime )	
{
	if(!m_bExplanation)
	{
		m_fDelayTurn -= fElapsedTime;
		timer -= fElapsedTime;
		m_fEnemyDelay -= fElapsedTime;
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

		if(m_bVictory)
			m_fEndBatleTimer -= fElapsedTime;

		switch (m_eCurrentPhase)
		{
		case CTutorialBattle::BP_INIT:
			Initialize();
			break;
		case CTutorialBattle::BP_BATTLE:
			Battle(fElapsedTime);
			break;
		case CTutorialBattle::BP_END:
			EndBattle();
			break;
		default:
			break;
		}
	}

}	
void CTutorialBattle::Render( void )	
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
		}

		if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT && m_vBattleUnits[m_nTarget]->GetType() != OBJ_PLAYER_UNIT)
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
		else if(m_vBattleUnits[m_nTurn]->GetType() != OBJ_PLAYER_UNIT)
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

		if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_ENEMY_UNIT)
		{
			RECT temp = { long(m_vBattleUnits[m_nTurn]->GetPosX() -30),  long(m_vBattleUnits[m_nTurn]->GetPosY() - 25),  long(m_vBattleUnits[m_nTurn]->GetPosX() -25),  long(m_vBattleUnits[m_nTurn]->GetPosY() - 20) };
			pD3D->DrawHollowRect(temp, D3DCOLOR_XRGB( 0,0,255 ));
		}
		else
		{
			RECT temp = { long(m_vBattleUnits[m_nTurn]->GetPosX() -20),  long(m_vBattleUnits[m_nTurn]->GetPosY() + 25),  long(m_vBattleUnits[m_nTurn]->GetPosX() -15),  long(m_vBattleUnits[m_nTurn]->GetPosY() + 30) };
			pD3D->DrawHollowRect(temp, D3DCOLOR_XRGB( 0,0,255 ));
		}
		if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
		{
			CPlayerUnit* pTemp = reinterpret_cast<CPlayerUnit*>(m_vBattleUnits[m_nTurn]);
			if(pTemp != nullptr)
			{
				if(pTemp->GetReady())
				{
					RECT temp = {  long(m_vBattleUnits[m_nTarget]->GetPosX() +60),  long(m_vBattleUnits[m_nTarget]->GetPosY() - 25),  long(m_vBattleUnits[m_nTarget]->GetPosX() + 65),  long(m_vBattleUnits[m_nTarget]->GetPosY() - 20) };
					if(pTemp->GetCasting() == false)
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
				if(!pTemp->GetReady())
				{
					for(unsigned int i = 0; i < vTemp.size(); i++)
					{
						woss.str(_T(""));
						woss << vTemp[i]->GetName().c_str();
						if(vTemp[i]->GetMiniGame() != nullptr && vTemp[i]->GetMiniGame()->GetCost() <= pTemp->GetAbilityPoints() && vTemp[i]->GetIsGame())
							m_pFont->Draw(woss.str().c_str(), 364, 490 + (i * 16), 0.75f, D3DCOLOR_XRGB(255,255,255));
						else if(vTemp[i]->GetMiniGame() == nullptr)
							m_pFont->Draw(woss.str().c_str(), 364, 490 + (i * 16), 0.75f, D3DCOLOR_XRGB(255,255,255));
						else
							m_pFont->Draw(woss.str().c_str(), 364, 490 + (i * 16), 0.75f, D3DCOLOR_XRGB(155,155,155));


					}
				}
				RECT rTemp = {};

				rTemp.top = 498 + (pTemp->GetSkillID() * 16);
				rTemp.bottom = rTemp.top + 10;
				rTemp.left = 348;
				rTemp.right = 358;
				if(!pTemp->GetReady())
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
					if (m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT || m_vBattleUnits[i]->GetName() == "Pathetic_Orc" || m_vBattleUnits[i]->GetName() == "Orc" || m_vBattleUnits[i]->GetName() == "Orc_Shaman" || m_vBattleUnits[i]->GetName() == "Orc_Leader" || m_vBattleUnits[i]->GetName() == "Ogre" || m_vBattleUnits[i]->GetName() == "Cave_Spider")
						CAnimationSystem::GetInstance()->Render(m_vBattleUnits[i]->GetAnimInfo(), PosX, PosY, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255));
					else
						CAnimationSystem::GetInstance()->Render(m_vBattleUnits[i]->GetAnimInfo(), PosX, PosY, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255));
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
		}

		if(m_bExplanation)
		{
			////////////////////////// EXPLAIN DODGE
			if(m_bExplainDodge)
			{
				woss.str(_T(""));
				woss << "Action Key - Press when you see Attempt to dodge\n\nPress the Action key to continue";
				RECT rCover = {0,0,800,600};
				pD3D->DrawRect(rCover, D3DCOLOR_ARGB(127,0,0,0));

				m_pFont->Draw(woss.str().c_str(), 15, 15,0.75f, D3DCOLOR_XRGB(255,255,255));
				woss.str(_T(""));
				woss << "\"Attempt\"";
				m_pFont->Draw(woss.str().c_str(), int(m_pPlayerUnit->GetPosX()),int(m_pPlayerUnit->GetPosY()),1.0f, D3DCOLOR_XRGB(0,255,255));
			}
			//////////////////////// EXPLAIN ATTACK
			else if(m_bExplainAttack)
			{
				woss.str(_T(""));
				woss << "Arrow Keys - Navigate Menu / Navigate Enemy\nAction Key - Select Skill/Enemy\nPlease use the attack ability now\nCancel Key - To back out of a selection\n\nPress the Action key to continue";
				RECT rCover = {0,0,800,600};
				pD3D->DrawRect(rCover, D3DCOLOR_ARGB(127,0,0,0));

				m_pFont->Draw(woss.str().c_str(), 15, 15,0.75f, D3DCOLOR_XRGB(255,255,255));
			}
			/////////////////////// EXPLAIN TRIGGER
			else if(m_bExplainTrigger)
			{
				RECT rCover = {0,0,800,600};
				pD3D->DrawRect(rCover, D3DCOLOR_ARGB(127,0,0,0));

				CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
				RECT rTemp = {200,64,600,96};
				pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(120, 255, 0, 0 ));
				pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0));

				RECT temp1 = {264,64,296,96};
				pD3D->DrawRect(temp1, D3DCOLOR_ARGB(120, 0, 200, 0));
				pD3D->DrawHollowRect(temp1, D3DCOLOR_XRGB(0,0,0));


				RECT temp2 = {302,64,318,96};
				pD3D->DrawRect(temp2, D3DCOLOR_ARGB(255, 0, 0, 255 ));
				pD3D->DrawHollowRect(temp2, D3DCOLOR_XRGB(0,0,0));
				woss.str(_T(""));
				woss << "This is the Trigger Event! these mini games only take AP Once!";
				m_pFont->Draw(woss.str().c_str(), 15, 15,0.75f, D3DCOLOR_XRGB(255,255,255));
				woss.str(_T(""));
				woss << "You have 10 chances to line the blue and green triggers up.\nMissing one ends the game.";
				m_pFont->Draw(woss.str().c_str(), 15, 102,0.75f, D3DCOLOR_XRGB(255,255,255));
				woss.str(_T(""));
				woss << "Action Key - Press when lined up to attack.\nPlease Use the SwordSlash in Spells!\n\nPress the Action key to continue";
				m_pFont->Draw(woss.str().c_str(), 15, 148,0.75f, D3DCOLOR_XRGB(255,255,255));
			}
			//////////////////////// EXPLAIN COMBO
			else if(m_bExplainCombo)
			{
				RECT rCover = {0,0,800,600};
				pD3D->DrawRect(rCover, D3DCOLOR_ARGB(127,0,0,0));

				CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
				CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
				RECT rTemp = {200,64,600, 96};

				pD3D->DrawRect(rTemp, D3DCOLOR_XRGB(0,255,255));
				pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,0,0),1);

				rTemp.left = 0;
				rTemp.right = 16;
				rTemp.top = 0;
				rTemp.bottom = 16;

				pTM->Draw(m_nCombArrowImgID,352,97,1.0f,1.0f);
				pTM->Draw(m_nCombArrowImgID,368,97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI/2);
				pTM->Draw(m_nCombArrowImgID,384,97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI/2);
				pTM->Draw(m_nCombArrowImgID,400,97,1.0f,1.0f,&rTemp,8.0f,8.0f,3*D3DX_PI/2);
				pTM->Draw(m_nCombArrowImgID,416,97,1.0f,1.0f,&rTemp,8.0f,8.0f,D3DX_PI);
				pTM->Draw(m_nCombArrowImgID,432,97,1.0f,1.0f,&rTemp,8.0f,8.0f,3*D3DX_PI/2);

				woss.str(_T(""));
				woss << "This is the Combo Event!";
				m_pFont->Draw(woss.str().c_str(), 15, 15,0.75f, D3DCOLOR_XRGB(255,255,255));
				woss.str(_T(""));
				woss << "You must complete as many combos as you can in 10 seconds! \nEvery success gives you 1 more second. Missing an arrow will set you back 1 move.";
				m_pFont->Draw(woss.str().c_str(), 15, 108,0.75f, D3DCOLOR_XRGB(255,255,255));
				woss.str(_T(""));
				woss << "Arrow Key - Press them in the order shown.\nPlease Use the Blitz Ability in Spells!\n\nPress the Action key to continue";
				m_pFont->Draw(woss.str().c_str(), 15, 164,0.75f, D3DCOLOR_XRGB(255,255,255));
			}
		}
	}

}	
void CTutorialBattle::Initialize(void)
{
	//Add player unit here.
	m_pPlayerUnit = CreateTempPlayer();
	m_pPlayerUnit->AddRef();

	m_vBattleUnits.push_back(m_pPlayerUnit);
	// Add Enemy units here.

	CEnemyUnit* pTemp = CreateTempEnemy("Thornbiter", 100.0f, 250.0f, 12, 30, 20);
	m_vBattleUnits.push_back(pTemp);
	pTemp = CreateTempEnemy("Thornbiter", 200.0f, 350.0f, 5,  30, 20);
	m_vBattleUnits.push_back(pTemp);
	pTemp = CreateTempEnemy("Thornbiter", 100.0f, 400.0f, 9,  30, 20);
	m_vBattleUnits.push_back(pTemp);

	sort(m_vBattleUnits.begin(), m_vBattleUnits.end(), CBattleState::SortSpeed); 
	GetNextTarget();

	m_vBattleUnits[m_nTurn]->SetTurn(true);
	m_eCurrentPhase = BP_BATTLE;
}
void CTutorialBattle::Battle(float fElapsedTime)
{
	if(m_eCurrentPhase == BP_BATTLE)
	{
		if(m_bExplanation == false)
		{
			for (unsigned int i = 0; i < m_vBattleUnits.size(); i++)
			{
				m_vBattleUnits[i]->Update(fElapsedTime);
			}
		}
	}
	if(m_bExplainDodge)
		m_bExplanation = true;

	if(m_fDelayTurn <= 0.0f && m_bDelayed == false)
	{
		if(m_eCurrentPhase == BP_BATTLE)
		{
			if(m_vBattleUnits[m_nTurn]->GetTurn() == false)
			{
				if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
				{
					if(m_bPlayerTurn == false)
					{
						m_bExplainOnceTurn = true;
						if(m_bExplainAttack && !m_bExplainDodge)
							m_bExplainAttack = false;

						else if(m_bExplainTrigger && !m_bExplainAttack)
							m_bExplainTrigger = false;
						else if(m_bExplainCombo && !m_bExplainTrigger)
							m_bExplainCombo = false;
					}
				}
				if(m_vBattleUnits.size() == 1)
				{
					if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
						m_eCurrentPhase = BP_END;
				}
				m_nTurn++;
				m_fDelayTurn = 0.6f;
				m_bDelayed = true;
				for(unsigned int i = 0; i < m_vBattleUnits.size();)
				{
					if(m_vBattleUnits[i]->GetHealth() < 1)
					{
						m_vBattleUnits[i]->Release();
						m_vBattleUnits.erase(m_vBattleUnits.begin() + i);
						GetNextTarget();
					}
					else
						i++;

				}
				if(m_nTurn >= (int)m_vBattleUnits.size())
					m_nTurn = 0;
			}
		}
	}
	else if(m_fDelayTurn <= 0.0f && m_bDelayed)
	{
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if (m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
			{
				m_vBattleUnits[i]->GetAnimInfo()->SetAnimation("Warrior_Battle_Idle");
			}
			else if (m_vBattleUnits[i]->GetName() == "Thornbiter")
			{
				string szTemp = m_vBattleUnits[i]->GetName() + "_Idle";
				m_vBattleUnits[i]->GetAnimInfo()->SetAnimation(szTemp.c_str());
			}
		}
		if(m_eCurrentPhase != BP_END)
		{

			m_vBattleUnits[m_nTurn]->SetTurn(true);
			if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
			{
				m_bPlayerTurn = true;
				if(m_bExplainAttack && !m_bExplainDodge)
				{
					m_bExplanation = true;
					m_bExplainOnceTurn = false;
				}
				else if(m_bExplainTrigger && !m_bExplainAttack)
				{
					m_pAttack->SetCost(5000);
					m_pTrigger->SetCost(10);

					m_bExplanation = true;
					m_bExplainOnceTurn = false;
				}
				else if(m_bExplainCombo && !m_bExplainTrigger)
				{
					m_pTrigger->SetCost(5000);
					m_pCombo->SetCost(10);

					m_bExplanation = true;
					m_bExplainOnceTurn = false;
				}
			}

		}
		m_bDelayed = false;
	}


}
void CTutorialBattle::EndBattle(void)
{
	if(!m_bVictory)
	{
		if(m_vBattleUnits[0]->GetType() == OBJ_PLAYER_UNIT)
		{
			m_fEndBatleTimer = 5.0f;
			m_bVictory = true;
			CSGD_XAudio2::GetInstance()->MusicStopSong(GetBackgroundMusic());
			CSGD_XAudio2::GetInstance()->MusicPlaySong(m_nVictoryMusic);
		}
	}
	if(m_fEndBatleTimer <= 0.0f)
	{
		CSGD_XAudio2::GetInstance()->MusicStopSong(m_nVictoryMusic);
		if(m_bMenu)
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		else
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
	}

}
CEnemyUnit* CTutorialBattle::CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp)
{
	CEnemyUnit* temp = new CEnemyUnit;
	CAIController* tempAI = new CAIController;
	CBasicAttack* tempAtk = new CBasicAttack;
	CAnimationTimeStamp* pTemp;
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Thornbiter_Idle");
	pTemp->SetCurrentFrame(0);
	temp->SetType(OBJ_ENEMY_UNIT);
	tempAtk->SetTutorial(true);
	tempAI->AddMinigame(tempAtk);
	tempAI->MakeOwner(temp);
	temp->SetAIController(tempAI);
	temp->SetMaxHealth(hp);
	temp->SetMaxAP(mp);
	temp->SetPosX(X);
	temp->SetPosY(Y);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetAttack(1);
	temp->SetSpeed(speed);
	temp->SetTurn(false);
	temp->SetName(input);
	temp->GiveExperience(90);

	temp->SetTutorial(true);
	return temp;
}
CPlayerUnit* CTutorialBattle::CreateTempPlayer()
{
	CPlayerUnit* temp = new CPlayerUnit;
	CCommands* tempC = new CCommands;
	CAnimationTimeStamp* pTemp;
	temp->SetAttack(50);
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Warrior_Battle_Idle");
	pTemp->SetCurrentFrame(0);
	tempC->SetName("Attack");
	tempC->SetMiniGame(m_pAttack);
	temp->AddSkill(tempC);

	tempC = new CCommands;
	tempC->SetName("Spells");
	tempC->SetIsGame(false);
	CCommands* pTest = new CCommands;
	pTest->SetName("SwordSlash");
	pTest->SetMiniGame(m_pTrigger);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	pTest->SetName("Blitz");
	pTest->SetMiniGame(m_pCombo);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	temp->AddSkill(tempC);
	temp->SetMaxHealth(350);
	temp->SetMaxAP(100);
	temp->SetPosX(600);
	temp->SetPosY(250);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(1);
	temp->SetType(OBJ_PLAYER_UNIT);
	temp->SetName("Arin");

	temp->SetTutorial(true);
	return temp;
}
void CTutorialBattle::GetNextTarget(void)
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
void CTutorialBattle::GetPreviousTarget(void)
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
CUnits* CTutorialBattle::GetCurrentTarget(void)
{
	return m_vBattleUnits[m_nTarget];
}
void CTutorialBattle::AddFloatingText(float posX, float posY, DWORD dColor, std::wostringstream &szText)
{
	FloatingText* ftTemp = new FloatingText;

	ftTemp->m_fLocX = posX;
	ftTemp->m_fLocY = posY;
	ftTemp->Color = dColor;
	ftTemp->szText << szText.str();
	ftTemp->m_fTimer = 1.5f;
	m_vText.push_back(ftTemp);
}