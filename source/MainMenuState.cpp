#include "MainMenuState.h"

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

#include "ProfileMenuState.h"
#include "OptionsMenu.h"
#include "CreditState.h"

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
	m_nLogoID = -1;
	m_nSelectionMenuID = -1;
	m_fRotation = 0.0f;
	m_bLeft = false;
}

CMainMenuState::~CMainMenuState(void)
{
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
	m_nMenu1		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Menu3.png"));
	m_nMenu2		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Menu4.png"));
	m_nMenu3		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Menu5.png"));

	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));
	m_fRotation = 0.0f;
	m_fPosX = 360.0f;
}

void CMainMenuState::Sleep(void)
{
	CSGD_XAudio2::GetInstance()->SFXUnloadSound(GetSFXID());
	SetSFXID(-1);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nLogoID);
	m_nLogoID = -1;
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nSelectionMenuID);
	m_nSelectionMenuID = -1;

	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nWarriorID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nRangerID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMageID);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenu1);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenu2);
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nMenu3);

	CSGD_TextureManager::GetInstance()->UnloadTexture(GetCursorIMG());

	SetCursorIMG(-1);
	m_nWarriorID	= -1;
	m_nRangerID		= -1;
	m_nMageID		= -1;
	m_nMenu1		= -1;
	m_nMenu2		= -1;
	m_nMenu3		= -1;


}

void CMainMenuState::Update(float fElapsedTime)
{
	m_fRotation += (1.0f * fElapsedTime);
	if(m_bLeft)
		m_fPosX -= (20 * fElapsedTime);
	else
		m_fPosX += (20 * fElapsedTime);

		if(m_fPosX <= 360)
		m_bLeft = false;
	else if(m_fPosX >= 370)
		m_bLeft = true;
}

void CMainMenuState::Render(void)
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	CBitmapFont* pFont2 = CGame::GetInstance()->GetFont2();

	RECT rtemp = {36, 48, 220, 206};

	CSGD_TextureManager::GetInstance()->Draw(m_nWarriorID,100,300,1.0f,1.0f,&rtemp,92,79,m_fRotation, D3DCOLOR_ARGB(250,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(m_nMageID,325,100,1.0f,1.0f,&rtemp,92,79,-m_fRotation, D3DCOLOR_ARGB(250,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(m_nRangerID,500,300,1.0f,1.0f,&rtemp,92,79,m_fRotation, D3DCOLOR_ARGB(250,255,255,255));

	RECT rLogo = {0,0,512,256};
	CSGD_TextureManager::GetInstance()->Draw(m_nLogoID,144,172,1.0f,1.0f,&rLogo,0.0f,0.0f,0.0f,D3DCOLOR_ARGB(230,255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(m_nSelectionMenuID,336,424);
	CSGD_TextureManager::GetInstance()->Draw(m_nMenu3,336,424);


	RECT rTemp = {336, 408, 464,536};
	pFont2->Draw(_T("Play\nOptions\nCredits\nExit"), 368,440, 0.75f, D3DCOLOR_XRGB(0,0,0));
	rTemp.left = 0;
	rTemp.top = 0;
	rTemp.right = 16;
	rTemp.bottom = 32;
	CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), m_fPosX, 442 + (GetCursorSelection() * 21), 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);
}

bool CMainMenuState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
		return false;

	if(pDI->KeyPressed(DIK_UPARROW) || pDI->JoystickDPadPressed(DIR_UP))
	{
		if(GetCursorSelection() <= 0)
			SetCursorSelection(3);
		else
			SetCursorSelection(GetCursorSelection() - 1);
		if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
			CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
	}
	else if(pDI->KeyPressed(DIK_DOWNARROW) || pDI->JoystickDPadPressed(DIR_DOWN))
	{
		if(GetCursorSelection() >= 3)
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
			CGame::GetInstance()->ChangeState(COptionsMenu::GetInstance());
			break;
		case 2:
			CGame::GetInstance()->ChangeState(CCreditState::GetInstance());
			break;
		case 3:
			return false;
		default:
			break;
		}
	}
	return true;
}
