#include "MainMenuState.h"

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

#include "ProfileMenuState.h"
#include "OptionsMenu.h"
#include "CreditState.h"
#include "TutorialBattle.h"

#include "GamePlayState.h"
#include "ProfileMenuState.h"
#include "BattleState.h" // <- TEMP needs to be deleted after testing.
#include "Game.h"

CMainMenuState* CMainMenuState::GetInstance( void )
{
	static CMainMenuState s_Instance;

	return &s_Instance;
}

CMainMenuState::CMainMenuState(void)
{
	SetBackgroundImg(-1);
	SetBackgroundMusic(-1);
	SetSFXID(-1);
	SetCursorIMG(-1);
	m_nLogoID = -1;
	m_nSelectionMenuID = -1;
	m_fRotation = 0.0f;
	m_fPosY = 0.0f;
	m_bLeft = false;
}

CMainMenuState::~CMainMenuState(void)
{
	Sleep();
}


void CMainMenuState::Activate(void)
{
	if(GetBackgroundMusic() == -1)
	{
		SetBackgroundMusic(CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("Assets/Audio/Music/POA_Test.xwm")));
		CSGD_XAudio2::GetInstance()->MusicPlaySong(GetBackgroundMusic(), true);
	}

	SetSFXID(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/SFX/POA_CursorSFX.wav")));
	m_nLogoID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_logo.png"));
	m_nSelectionMenuID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_SelectionMenu.png"));
	m_nWarriorID	= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Warrior.png"));
	m_nRangerID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Ranger.png"));
	m_nMageID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Mage.png"));

	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));
	m_fRotation = 0.0f;
	m_fPosX = 360.0f;
	m_fPosY = 0.0f;
}

void CMainMenuState::Sleep(void)
{
	if(GetSFXID() != -1)
		CSGD_XAudio2::GetInstance()->SFXUnloadSound(GetSFXID());
	SetSFXID(-1);
	if(m_nLogoID != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nLogoID);
	m_nLogoID = -1;
	if(m_nSelectionMenuID != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSelectionMenuID);
	m_nSelectionMenuID = -1;
	if(m_nWarriorID != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nWarriorID);
	if(m_nRangerID != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nRangerID);
	if(m_nMageID != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMageID);
	if(GetCursorIMG() != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(GetCursorIMG());

	SetCursorIMG(-1);
	m_nWarriorID	= -1;
	m_nRangerID		= -1;
	m_nMageID		= -1;
}

void CMainMenuState::Update(float fElapsedTime)
{
	m_fRotation += (1.0f * fElapsedTime);

	if(m_fPosY >= 172.0f)
	{
		if(m_bLeft)
			m_fPosX -= (20 * fElapsedTime);
		else
			m_fPosX += (20 * fElapsedTime);

		if(m_fPosX <= 360)
			m_bLeft = false;
		else if(m_fPosX >= 370)
			m_bLeft = true;
	}
	else{
		m_fPosY += 200 * fElapsedTime;
	}
}

void CMainMenuState::Render(void)
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	CBitmapFont* pFont = CGame::GetInstance()->GetFont("Comic Sans MS");

	RECT rtemp = {36, 48, 220, 206};
	CSGD_TextureManager::GetInstance()->Draw(m_nWarriorID,100,300,1.0f,1.0f,&rtemp,92,79,m_fRotation, D3DCOLOR_ARGB(250,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(m_nMageID,325,100,1.0f,1.0f,&rtemp,92,79,-m_fRotation, D3DCOLOR_ARGB(250,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(m_nRangerID,500,300,1.0f,1.0f,&rtemp,92,79,m_fRotation, D3DCOLOR_ARGB(250,255,255,255));
	RECT rLogo = {0,0,512,256};
	CSGD_TextureManager::GetInstance()->Draw(m_nLogoID,144,(int)m_fPosY,1.0f,1.0f,&rLogo,0.0f,0.0f,0.0f,D3DCOLOR_ARGB(230,255,255,255));
	if(m_fPosY >= 172.0f)
	{
		CSGD_TextureManager::GetInstance()->Draw(m_nSelectionMenuID,272,360);

		RECT rTemp = {336, 408, 464,536};
		pFont->Draw(_T("Play\nTutorial\nOptions\nCredits\nExit"), 368,440, 0.75f, D3DCOLOR_XRGB(0,0,0));
		rTemp.left = 0;
		rTemp.top = 0;
		rTemp.right = 16;
		rTemp.bottom = 32;
		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), (int)m_fPosX, 442 + (GetCursorSelection() * 21), 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);
	}
}

bool CMainMenuState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(m_fPosY >= 172.0f)
	{
		if(pDI->KeyPressed(DIK_ESCAPE))
			return false;

		if(pDI->KeyPressed(DIK_W) || pDI->JoystickDPadPressed(DIR_UP))
		{
			if(GetCursorSelection() <= 0)
				SetCursorSelection(4);
			else
				SetCursorSelection(GetCursorSelection() - 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_S) || pDI->JoystickDPadPressed(DIR_DOWN))
		{
			if(GetCursorSelection() >= 4)
				SetCursorSelection(0);
			else
				SetCursorSelection(GetCursorSelection() + 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(1))
		{
			switch (GetCursorSelection())
			{
			case 0:
				CGame::GetInstance()->ChangeState(CProfileMenuState::GetInstance()); // <-Should be going to profile state.
				break;
			case 1:
				{
					CTutorialBattle::GetInstance()->FromMenu(true);
					CGame::GetInstance()->ChangeState(CTutorialBattle::GetInstance()); // <-Should be going to profile state.
					break;
				}
			case 2:
				CGame::GetInstance()->ChangeState(COptionsMenu::GetInstance());
				break;
			case 3:
				CGame::GetInstance()->ChangeState(CCreditState::GetInstance());
				break;
			case 4:
				return false;
			default:
				break;
			}
		}
	}
	return true;
}
