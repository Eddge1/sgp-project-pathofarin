#include "MainMenuState.h"

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

#include "ProfileMenuState.h"
#include "OptionsMenu.h"
#include "CreditState.h"

#include "GamePlayState.h"
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
}



CMainMenuState::~CMainMenuState(void)
{

}


void CMainMenuState::Activate(void)
{
	if(GetBackgroundMusic() == -1)
	{
		SetBackgroundMusic(CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("Assets/Audio/Music/JB_Test.xwm")));
		CSGD_XAudio2::GetInstance()->MusicPlaySong(GetBackgroundMusic(), true);
	}
	SetSFXID(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/SFX/JB_CursorSFX.wav")));
	SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/DNAS_MainMenu.png")));
	m_nLogoID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_logo.png"));
}

void CMainMenuState::Sleep(void)
{
	CSGD_XAudio2::GetInstance()->SFXUnloadSound(GetSFXID());
	SetSFXID(-1);
	CSGD_TextureManager::GetInstance()->UnloadTexture(GetBackgroundImg());
	CSGD_TextureManager::GetInstance()->UnloadTexture(m_nLogoID);
	SetBackgroundImg(-1);
	m_nLogoID = -1;
}

void CMainMenuState::Update(float fElapsedTime)
{

}

void CMainMenuState::Render(void)
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	CBitmapFont* pFont2 = CGame::GetInstance()->GetFont2();

	CSGD_TextureManager::GetInstance()->Draw(m_nLogoID,144,172);
	CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(),0,0);

	RECT rTemp = {336, 408, 464,536};
	pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(200,0,0,0));
	pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,127,255));
	pFont2->Draw(_T("Play\nOptions\nCredits\nExit"), 352,416, 1.0f, D3DCOLOR_XRGB(0, 255, 255));
	pFont2->Draw(_T("-"), 344,416 + (GetCursorSelection() * 28), 1.0f, D3DCOLOR_XRGB(0, 255, 255));

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
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance()); // <-Should be going to profile state.
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
