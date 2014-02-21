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
#include "VictoryState.h"
#include "GameOverState.h"
#include <algorithm>
#include "Consumable.h"
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
	SetBackgroundImg(-1);
	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Cursor.png")));
	SetSFXID(-1);
	m_bLeveled = false;
	m_fDelayTurn = 0.0f;
	m_bDelayed = false;

	SetBackgroundMusic(CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_MainBattleLoop.xwm")));
	m_nOrcLeader = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_OrcSiegeLeader_Battle.xwm"));
	m_nTigerlily = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_TigerLily_Battle.xwm"));
	m_nDefeatMusic			= CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_Defeat.xwm"));
	m_nVictoryMusic			= CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_Victory.xwm"));
	m_nSelectionChange		= CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_SelectionMove.wav"));

	m_nMenuImage			=	CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_BattleMenu.png"));
	m_nMenuSelectionImage	= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_SelectionMenu.png"));
	m_nForestBattleID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Backgrounds/Forest_Battle.png"));
	m_nHealthBar			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_HealthBar.png"));
	m_nHealthBarPlate		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_HealthBarPlate.png"));
}

CBattleState::~CBattleState(void)
{
	Sleep();
	if(m_vItems.size() > 0)
		ClearItems();
}

void CBattleState::Activate(void)
{
	m_pFont = CGame::GetInstance()->GetFont("Arial");
	m_bDefeat = false;
	m_bVictory = false;
	m_fEndBatleTimer = 0.0f;
	m_fCancelTimer = 2.0f;
	m_nExperienceGained = 0;
	m_bDelayed = false;
	// TEMP ENEMIES/Player
	m_eCurrentPhase = BP_INIT;
	m_fDelayTurn = 0.0f;

}

void CBattleState::Sleep(void)
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

	for(unsigned int i = 0; i < m_vSkills.size();)
	{
		m_vSkills[i]->Release();
		m_vSkills[i] = nullptr;
		m_vSkills.erase(m_vSkills.begin() + i);
	}

	m_vText.clear();

	SetSender(nullptr);
	SetPlayer(nullptr);

	m_bLeveled = false;
	m_nExperienceGained = 0;
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
					if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_W ) || CSGD_DirectInput::GetInstance()->KeyPressed( DIK_UPARROW ) 
						|| CSGD_DirectInput::GetInstance()->JoystickDPadPressed(DIR_UP) || CSGD_DirectInput::GetInstance()->JoystickGetLStickDirPressed(DIR_UP) )
					{
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionChange);
						GetNextTarget();
					}
					else if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_S ) || CSGD_DirectInput::GetInstance()->KeyPressed( DIK_DOWNARROW )
						|| CSGD_DirectInput::GetInstance()->JoystickDPadPressed(DIR_DOWN) || CSGD_DirectInput::GetInstance()->JoystickGetLStickDirPressed(DIR_DOWN))
					{
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionChange);
						GetPreviousTarget();
					}
				}
			}
		}
	}
	return true;
}

void CBattleState::Update(float fElapsedTime)
{
	m_fDelayTurn -= fElapsedTime;
	if(m_fDelayTurn <= 0.0f && m_bDelayed)
	{

		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if (m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT && m_eCurrentPhase != BP_END)
			{
				m_vBattleUnits[i]->GetAnimInfo()->SetAnimation("Warrior_Battle_Idle");
			}
			else if(m_vBattleUnits[i]->GetType() != OBJ_PLAYER_UNIT)
			{
				string szTemp = m_vBattleUnits[i]->GetName() + "_Battle_Idle";
				m_vBattleUnits[i]->GetAnimInfo()->SetAnimation(szTemp.c_str());
			}
		}
		if(m_eCurrentPhase != BP_END)
			m_vBattleUnits[m_nTurn]->SetTurn(true);
		m_bDelayed = false;
	}

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

	if(m_eCurrentPhase != BP_INIT)
	{
		for (unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			m_vBattleUnits[i]->Update(fElapsedTime);
		}

		for(unsigned int i = 0; i < m_vSkills.size();)
		{
			m_vSkills[i]->Update(fElapsedTime);
			if(m_vSkills[i]->GetCollided())
			{
				m_vSkills[i]->Release();
				m_vSkills[i] = nullptr;
				m_vSkills.erase(m_vSkills.begin() + i);
			}
			else
				i++;

		}
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
	RECT rCursor = {0,0,16,32};

	//Temp drawing the UI
	pTM->Draw(m_nForestBattleID, 0, 0, 2.0f, 2.0f);
	pTM->Draw(m_nMenuImage, 0,472);
	pTM->Draw(m_nMenuSelectionImage, 272,408);

	// Printing out variables
	std::wostringstream woss;

	if(m_vBattleUnits.size() > 0)
	{
		float hPercent = m_pPlayerUnit->GetHealth() / float(m_pPlayerUnit->GetMaxHealth());
		RECT rHealth = {0,0,256, 32};
		pTM->Draw(m_nHealthBar, 500,500,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(0,0,0));
		rHealth.right = long(256 * hPercent);
		pTM->Draw(m_nHealthBar, 500,500,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(255,255,255));
		rHealth.right = 256;
		pTM->Draw(m_nHealthBarPlate, 500,500,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(255,255,255));
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
			{
				woss << m_vBattleUnits[i]->GetHealth();
				m_pFont->Draw( woss.str().c_str(), 524, 500, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
				woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
				woss << "AP: " << m_vBattleUnits[i]->GetAbilityPoints();
				m_pFont->Draw( woss.str().c_str(), 700, 520, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
				woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			}
		}

		if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT && m_nTarget < int(m_vBattleUnits.size()) && m_vBattleUnits[m_nTarget]->GetType() != OBJ_PLAYER_UNIT)
		{
			hPercent = m_vBattleUnits[m_nTarget]->GetHealth() / float(m_vBattleUnits[m_nTarget]->GetMaxHealth());
			pTM->Draw(m_nHealthBar, 64,516,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(0,0,0));
			rHealth.right = long(256 * hPercent);
			pTM->Draw(m_nHealthBar, 64,516,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(255,255,255));
			rHealth.right = 256;
			pTM->Draw(m_nHealthBarPlate, 64,516,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(255,255,255));

			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTarget]->GetHealth();
			m_pFont->Draw( woss.str().c_str(), 96, 516, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTarget]->GetName().c_str();
			m_pFont->Draw( woss.str().c_str(), 64, 492, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
		}
		else if(m_vBattleUnits[m_nTurn]->GetType() != OBJ_PLAYER_UNIT)
		{
			hPercent = m_vBattleUnits[m_nTurn]->GetHealth() / float(m_vBattleUnits[m_nTurn]->GetMaxHealth());
			pTM->Draw(m_nHealthBar, 64,516,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(0,0,0));
			rHealth.right = long(256 * hPercent);
			pTM->Draw(m_nHealthBar, 64,516,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(255,255,255));
			rHealth.right = 256;
			pTM->Draw(m_nHealthBarPlate, 64,516,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(255,255,255));

			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTurn]->GetHealth();
			m_pFont->Draw( woss.str().c_str(), 96, 516, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
			woss.str(_T("")); // <- This is used to clear the woss so it can take new variables.
			woss << m_vBattleUnits[m_nTurn]->GetName().c_str();
			m_pFont->Draw( woss.str().c_str(), 64, 492, 0.8f, D3DCOLOR_ARGB(255, 0, 0, 0) );
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
					if (m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT || m_vBattleUnits[i]->GetName() == "Pathetic_Orc" || m_vBattleUnits[i]->GetName() == "Orc" || m_vBattleUnits[i]->GetName() == "Orc_Shaman" || m_vBattleUnits[i]->GetName() == "Orc_Leader" || m_vBattleUnits[i]->GetName() == "Ogre" || m_vBattleUnits[i]->GetName() == "Cave_Spider" || m_vBattleUnits[i]->GetName() == "Cultist")
						CAnimationSystem::GetInstance()->Render(m_vBattleUnits[i]->GetAnimInfo(), PosX, PosY, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255));
					else
						CAnimationSystem::GetInstance()->Render(m_vBattleUnits[i]->GetAnimInfo(), PosX, PosY, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255));

				}
				nImageID = -1;
			}
		}


		for(unsigned int i = 0; i < m_vSkills.size(); i++)
		{
			CAnimationSystem::GetInstance()->Render(m_vSkills[i]->GetAnimInfo(), m_vSkills[i]->GetPosX(), m_vSkills[i]->GetPosY(), 1.0f, 1.0f, D3DCOLOR_XRGB(255,255,255));
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
					{
						RECT rTarget = m_vBattleUnits[m_nTarget]->GetCollisionRectNoCam();
						CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), int(rTarget.right + 8), int((rTarget.top + rTarget.bottom) / 2), 1.0f,1.0f,&rCursor, 16.0f,8.0f,1.5*D3DX_PI,D3DCOLOR_XRGB(255,0,0));
					}
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


		for(int i = 0; i < (int)m_vText.size(); i++)
			m_pFont->Draw(m_vText[i]->szText.str().c_str(), (int)m_vText[i]->m_fLocX, (int)m_vText[i]->m_fLocY, 1.0f, m_vText[i]->Color);




		if(m_bVictory)
		{
			woss.str(_T(""));
			woss << "Victory!";
			m_pFont->Draw(woss.str().c_str(), 380, 15,1.0f, D3DCOLOR_XRGB(0,0,255));
		}
		else if(m_bDefeat)
		{
			woss.str(_T(""));
			woss << "Defeated!";
			m_pFont->Draw(woss.str().c_str(), 380, 15,1.0f, D3DCOLOR_XRGB(0,0,255));
		}

		RECT rPTemp = m_vBattleUnits[m_nTurn]->GetCollisionRectNoCam();

		if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_ENEMY_UNIT)
		{
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), int(rPTemp.right + 8), int((rPTemp.top + rPTemp.bottom) / 2), 1.0f,1.0f,&rCursor, 16.0f,8.0f,1.5*D3DX_PI,D3DCOLOR_XRGB(255,255,255));
		}
		else
		{
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), int(rPTemp.left - 32), int((rPTemp.top + rPTemp.bottom) / 2), 1.0f,1.0f,&rCursor, 16.0f,8.0f,D3DX_PI / 2,D3DCOLOR_XRGB(255,255,255));
		}
	}
}

bool CBattleState::SortSpeed(CUnits *l, CUnits *r)
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

	for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
	{

		if(m_vBattleUnits[i]->GetName() == "Orc_Leader")
		{
			SetBackgroundMusic(m_nOrcLeader);
			CSGD_XAudio2::GetInstance()->MusicPlaySong(GetBackgroundMusic(), true);
		}
		else if(m_vBattleUnits[i]->GetName() == "TigerLily")
		{
			SetBackgroundMusic(m_nTigerlily);
			CSGD_XAudio2::GetInstance()->MusicPlaySong(GetBackgroundMusic(), true);
		}
		else if(m_vBattleUnits[i]->GetName() == "Valrion")
		{
			SetBackgroundMusic(m_nValrion);
			CSGD_XAudio2::GetInstance()->MusicPlaySong(GetBackgroundMusic(), true);
			break;
		}

	}

	if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(m_nOrcLeader))
	{
	}
	else if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(m_nTigerlily))
	{

	}
	else if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(m_nValrion))
	{
	}
	else
	{
		SetBackgroundMusic(CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("assets/Audio/Music/POA_MainBattleLoop.xwm")));
		CSGD_XAudio2::GetInstance()->MusicPlaySong(GetBackgroundMusic(), true);
	}




	sort(m_vBattleUnits.begin(), m_vBattleUnits.end(), SortSpeed); 
	GetNextTarget();
	m_eCurrentPhase = BP_BATTLE;
}

void CBattleState::Battle(float fElapsedTime)
{

	if(m_fDelayTurn <= 0.0f && m_bDelayed == false)
	{
		if(m_eCurrentPhase == BP_BATTLE)
		{
			if(m_vBattleUnits[m_nTurn]->GetTurn() == false)
			{

				m_nTurn++;
				m_fDelayTurn = 0.6f;
				m_bDelayed = true;
				for(unsigned int i = 0; i < m_vBattleUnits.size();)
				{
					if(m_vBattleUnits[i]->GetHealth() < 1)
					{
						if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
						{
							string szName = m_vBattleUnits[m_nTurn - 1]->GetName();
							szName += " defeated you by bashing your face in.";
							CGameOverState::GetInstance()->SetMessage(szName);
							m_vBattleUnits[i]->GetAnimInfo()->SetAnimation("Warrior_Battle_Dead");
							m_eCurrentPhase = BP_END;
							break;
						}
						else
						{
							m_nExperienceGained += m_vBattleUnits[i]->GetExperience();
							SetItems(m_vBattleUnits[i]);
							m_vBattleUnits[i]->Release();
							m_vBattleUnits.erase(m_vBattleUnits.begin() + i);
							GetNextTarget();
						}
					}
					else
						i++;

				}

				if(m_vBattleUnits.size() == 1)
				{
					if(m_vBattleUnits[m_nTurn]->GetType() == OBJ_PLAYER_UNIT)
						m_eCurrentPhase = BP_END;
				}

				if(m_nTurn >= (int)m_vBattleUnits.size())
					m_nTurn = 0;

			}
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
				if (m_vBattleUnits[i]->GetHealth() > 0)
				{
					m_bVictory = true;
					CSGD_XAudio2::GetInstance()->MusicStopSong(GetBackgroundMusic());
					CSGD_XAudio2::GetInstance()->MusicPlaySong(m_nVictoryMusic);
				}
				else
				{
					m_fEndBatleTimer = 5.0f;
					m_bDefeat = true;
					CSGD_XAudio2::GetInstance()->MusicStopSong(GetBackgroundMusic());
					CSGD_XAudio2::GetInstance()->MusicPlaySong(m_nDefeatMusic);
					return;
				}
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
		if(m_bVictory)
		{
			CSGD_EventSystem::GetInstance()->SendEventNow("BATTLE_END", nullptr, m_pSender, nullptr);
			CVictoryState::GetInstance()->SetExperience(m_nExperienceGained);
			CGame::GetInstance()->ChangeState(CVictoryState::GetInstance());
		}
		else
		{
			CGame::GetInstance()->ChangeState(CGameOverState::GetInstance());
		}
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

void CBattleState::SetPlayer(CPlayerUnit* pPlayer)
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

void CBattleState::AddFloatingText(float posX, float posY, DWORD dColor, std::wostringstream &szText, float fTimer)
{
		FloatingText* ftTemp = new FloatingText;

		ftTemp->m_fLocX = posX;
		ftTemp->m_fLocY = posY;
		ftTemp->Color = dColor;
		ftTemp->szText << szText.str();
		ftTemp->m_fTimer = fTimer;
		m_vText.push_back(ftTemp);
}

void CBattleState::SetItems(CUnits* pDead)
{
	map<string, InventoryItems>* vTemp = pDead->GetInv();

	for(auto i = vTemp->begin(); i != vTemp->end(); i++)
	{
		if(i->second.Item != nullptr)
		{
			if(i->second.Item->GetItemType() == IT_CONSUMABLE)
			{
				CConsumable* pTemp = reinterpret_cast<CConsumable*>(i->second.Item);
				if(pTemp != nullptr)
				{
					if(rand() % 100 + 1 < int(i->second.DropChance * 100))
					{
						if(m_vItems[pTemp->GetName()].Item == nullptr)
						{
							m_vItems[pTemp->GetName()].Item = pTemp;
							m_vItems[pTemp->GetName()].Owned = 1;
							i->second.Item = nullptr;
						}
						else
						{
							m_vItems[pTemp->GetName()].Owned++;
							i->second.Item = nullptr;
						}
					}
				}
			}
		}
	}
}

void CBattleState::ClearItems()
{
	m_vItems.clear();
}

CUnits* CBattleState::GetCurrentTurn()
{
	return m_vBattleUnits[m_nTurn];

}