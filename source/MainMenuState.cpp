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
#include "EquipmentState.h"
#include "Game.h"

CMainMenuState* CMainMenuState::GetInstance( void )
{
	static CMainMenuState s_Instance;

	return &s_Instance;
}

CMainMenuState::CMainMenuState(void)
{
	SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_background.png")));
	SetSFXID(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/SFX/POA_CursorSFX.wav")));
	m_nLogoID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_logo.png"));
	m_nSelectionMenuID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_SelectionMenu.png"));
	m_nWarriorID	= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Warrior.png"));
	m_nRangerID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Ranger.png"));
	m_nMageID		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Mage.png"));
	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));
	SetBackgroundMusic(CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("Assets/Audio/Music/POA_MainMenu_Background.xwm")));
	m_fRotation = 0.0f;
	m_fPosY = 0.0f;
	m_bLeft = false;
	m_bLeftMenuState = false;
	m_fRune1Scale = 0.0f;
	m_fRune2Scale = 0.0f;
	m_fRunes3Scale = 0.0f;
	m_fRune1ReactTimer  = 0.0f;
	m_fRune2ReactTimer  = 0.0f;
	m_fRunes3ReactTimer = 0.0f;
}

CMainMenuState::~CMainMenuState(void)
{
	Sleep();
}


void CMainMenuState::Activate(void)
{

	if(m_bLeftMenuState)
	{
		if(!CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(GetBackgroundMusic()))
			m_bLeftMenuState = false;
	}

	m_fRotation = 0.0f;
	m_fPosX = 360.0f;
	m_fPosY = 0.0f;

	m_fRune1Scale =  (rand() % 100) * 0.01f;
	m_fRune2Scale =  (rand() % 100) * 0.01f;
	m_fRunes3Scale = (rand() % 100) * 0.01f;
	m_fRune1ReactTimer  = 0.0f;
	m_fRune2ReactTimer  = 0.0f;
	m_fRunes3ReactTimer = 0.0f;
}

void CMainMenuState::Sleep(void)
{
	m_fRune1Scale = 0.0f;
	m_fRune2Scale = 0.0f;
	m_fRunes3Scale = 0.0f;
	m_fRune1ReactTimer  = 0.0f;
	m_fRune2ReactTimer  = 0.0f;
	m_fRunes3ReactTimer = 0.0f;
}

void CMainMenuState::Update(float fElapsedTime)
{
	if(	m_fRune1ReactTimer >= 0)
		m_fRune1ReactTimer -= fElapsedTime;
	else
	{
		m_fRune1Scale += 0.33f * fElapsedTime;
		if(m_fRune1Scale >= 1.0f)
		{
			m_fRune1ReactTimer =(rand() % 100) * 0.01f;
			m_fRune1Scale = 0;
		}
	}
	if(	m_fRune2ReactTimer >= 0)
		m_fRune2ReactTimer -= fElapsedTime;
	else
	{
		m_fRune2Scale += 0.33f * fElapsedTime;
		if(m_fRune2Scale >= 1.0f)
		{
			m_fRune2ReactTimer =(rand() % 100) * 0.01f;
			m_fRune2Scale = 0;
		}
	}
	if(	m_fRunes3ReactTimer >= 0)
		m_fRunes3ReactTimer -= fElapsedTime;
	else
	{
		m_fRunes3Scale += 0.33f * fElapsedTime;
		if(m_fRunes3Scale >= 1.0f)
		{
			m_fRunes3ReactTimer =(rand() % 100) * 0.01f;
			m_fRunes3Scale = 0;
		}
	}

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
	CBitmapFont* pFont = CGame::GetInstance()->GetFont("Big Caslon");
	RECT clearscreenson = {0, 0, 800, 600};
	CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(),0,0);

	RECT rtemp = {36, 48, 220, 206};
	if(m_fRune1Scale <0.5f)
		CSGD_TextureManager::GetInstance()->Draw(m_nWarriorID,100,300,m_fRune1Scale,m_fRune1Scale,&rtemp,92 * m_fRune1Scale,79*m_fRune1Scale,m_fRotation *2, D3DCOLOR_ARGB(250,255,255,255));
	else
		CSGD_TextureManager::GetInstance()->Draw(m_nWarriorID,100,300,m_fRune1Scale,m_fRune1Scale,&rtemp,92 * m_fRune1Scale,79*m_fRune1Scale,m_fRotation *2, D3DCOLOR_ARGB(char(250 * (1.0f - (m_fRune1Scale * 2))),255,255,255));

	if(m_fRune2Scale <0.5f)
		CSGD_TextureManager::GetInstance()->Draw(m_nMageID,325,100,m_fRune2Scale,m_fRune2Scale,&rtemp,92 * m_fRune2Scale,79 *m_fRune2Scale,-m_fRotation *2, D3DCOLOR_ARGB(250,255,255,255));
	else
		CSGD_TextureManager::GetInstance()->Draw(m_nMageID,325,100,m_fRune2Scale,m_fRune2Scale,&rtemp,92 * m_fRune2Scale,79 *m_fRune2Scale,-m_fRotation *2, D3DCOLOR_ARGB(char(250 * (1.0f - (m_fRune2Scale * 2))),255,255,255));

	if(m_fRunes3Scale <0.5f)
		CSGD_TextureManager::GetInstance()->Draw(m_nRangerID,500,300,m_fRunes3Scale,m_fRunes3Scale,&rtemp,92*m_fRunes3Scale,79*m_fRunes3Scale,m_fRotation *2, D3DCOLOR_ARGB(250,255,255,255));
	else
		CSGD_TextureManager::GetInstance()->Draw(m_nRangerID,500,300,m_fRunes3Scale,m_fRunes3Scale,&rtemp,92*m_fRunes3Scale,79*m_fRunes3Scale,m_fRotation *2, D3DCOLOR_ARGB(char(250 * (1.0f - (m_fRunes3Scale * 2))),255,255,255));

	RECT rLogo = {0,0,512,256};
	CSGD_TextureManager::GetInstance()->Draw(m_nLogoID,144,(int)m_fPosY,1.0f,1.0f,&rLogo,0.0f,0.0f,0.0f,D3DCOLOR_ARGB(230,255,255,255));


	if(m_fPosY >= 172.0f)
	{
		RECT rTemp = {316, 416, 490,536};
		CSGD_Direct3D::GetInstance()->DrawRect(rTemp, D3DCOLOR_ARGB(200,0,0,0));
		CSGD_TextureManager::GetInstance()->Draw(m_nSelectionMenuID,272,360);
		pFont->Draw(_T("Play\nTutorial\nOptions\nCredits\nExit"), 384,440, 0.66f, D3DCOLOR_XRGB(255,255,255));
		rTemp.left = 0;
		rTemp.top = 0;
		rTemp.right = 16;
		rTemp.bottom = 32;
		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), (int)m_fPosX, 442 + (GetCursorSelection() * 18), 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);
	}
}

bool CMainMenuState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(m_fPosY >= 172.0f)
	{
		if(pDI->KeyPressed(DIK_ESCAPE)|| pDI->JoystickButtonPressed(2))
			return false;

		if(pDI->KeyPressed(DIK_W) || pDI->KeyPressed(DIK_UPARROW) || pDI->JoystickDPadPressed(DIR_UP) || pDI->JoystickGetLStickDirPressed(DIR_UP))
		{
			if(GetCursorSelection() <= 0)
				SetCursorSelection(4);
			else
				SetCursorSelection(GetCursorSelection() - 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_S) || pDI->KeyPressed(DIK_DOWNARROW) || pDI->JoystickDPadPressed(DIR_DOWN) || pDI->JoystickGetLStickDirPressed(DIR_DOWN))
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
					m_bLeftMenuState = true;
					if(m_bLeftMenuState)
					{
						if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(GetBackgroundMusic()))
							CSGD_XAudio2::GetInstance()->MusicStopSong(GetBackgroundMusic());
					}
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
