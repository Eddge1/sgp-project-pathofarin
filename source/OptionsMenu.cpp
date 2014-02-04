#include "OptionsMenu.h"
#include "MainMenuState.h"
#include "Game.h"
#include <sstream>

COptionsMenu::COptionsMenu(void)
{
	m_bSubMenu = false;
	m_bIsWindow = false;
	m_bIsMemory = false;

	m_nMusicVolume = -1;
	m_nSFXVolume = -1;
	m_nSubCursor = 0;
	SetBackgroundImg(-1);
	SetBackgroundMusic(-1);
	SetSFXID(-1);
	SetCursorIMG(-1);
	SetSFXID(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/SFX/POA_CursorSFX.wav")));
}

COptionsMenu::~COptionsMenu(void)
{
	Sleep();
}

COptionsMenu* COptionsMenu::GetInstance( void )
{
	static COptionsMenu s_Instance;
	return &s_Instance;
}

void COptionsMenu::Activate( void )
{
	m_bSubMenu = false;
	CGame* pGame = CGame::GetInstance();
	m_bIsMemory = pGame->GetMemory();
	m_bIsWindow = pGame->GetIsWindow();

	m_nMusicVolume = int(CSGD_XAudio2::GetInstance()->MusicGetMasterVolume() * 100);
	m_nSFXVolume = int(CSGD_XAudio2::GetInstance()->SFXGetMasterVolume() * 100);

}

void COptionsMenu::Sleep( void )
{

}

void COptionsMenu::Update( float fElapsedTime ){}

void COptionsMenu::Render( void )
{
	//CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(),0,0);

	std::wostringstream woss;
	woss << "\n\t\t" <<  m_nMusicVolume << "\n\t\t" << m_nSFXVolume;
	CBitmapFont* pFont2 = CGame::GetInstance()->GetFont2();

	pFont2->Draw(_T("Options"), 10,10, 3.0f, D3DCOLOR_XRGB(0, 0, 255));
	pFont2->Draw(_T("Sound\n\tMusic:\n\tSFX:"), 20,120,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	pFont2->Draw(woss.str().c_str(), 20,120,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	pFont2->Draw(_T("Graphics\n\tWindow\t\tFullscreen"), 20,240,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	pFont2->Draw(_T("Save Cursor Location\n\tNo\t\tYes"), 20,300,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	pFont2->Draw(_T("Return"), 20,540,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	switch(GetCursorSelection())
	{
	case 0:
		pFont2->Draw(_T("-"), 10,120,1.0f, D3DCOLOR_XRGB(0, 0, 0));
		break;
	case 1:
		pFont2->Draw(_T("-"), 10,240,1.0f, D3DCOLOR_XRGB(0, 0, 0));
		break;
	case 2:
		pFont2->Draw(_T("-"), 10,300,1.0f, D3DCOLOR_XRGB(0, 0, 0));
		break;
	case 3:
		pFont2->Draw(_T("-"), 10,540,1.0f, D3DCOLOR_XRGB(0, 0, 0));
		break;
	default:
		break;
	}

	pFont2->Draw(_T("\t-"), 10,150 + (m_nSubCursor * 28),1.0f, D3DCOLOR_XRGB(0, 0, 0));

	if(m_bIsWindow)
		pFont2->Draw(_T("\n\t-"), 10, 240,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	else
		pFont2->Draw(_T("\n\t\t\t-"), 10, 240,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	if(!m_bIsMemory)
		pFont2->Draw(_T("\n\t-"), 10, 300,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	else
		pFont2->Draw(_T("\n\t\t\t-"), 10, 300,1.0f, D3DCOLOR_XRGB(0, 0, 0));
}

bool COptionsMenu::Input( void )	
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(!m_bSubMenu)
	{
		if(pDI->KeyPressed(DIK_ESCAPE) || pDI->JoystickButtonPressed(2))
		{
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			CGame::GetInstance()->CreateConfig(m_nMusicVolume, m_nSFXVolume, m_bIsWindow, m_bIsMemory);

		}
		else if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(1))
		{
			if(GetCursorSelection() ==3)
			{
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
				CGame::GetInstance()->CreateConfig(m_nMusicVolume, m_nSFXVolume, m_bIsWindow, m_bIsMemory);
			}
			else
				m_bSubMenu = true;

		}
		else if(pDI->KeyPressed(DIK_W) || pDI->JoystickDPadPressed(DIR_UP))
		{
			if(GetCursorSelection() == 0)
				SetCursorSelection(3);
			else
				SetCursorSelection(GetCursorSelection()  - 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_S) || pDI->JoystickDPadPressed(DIR_DOWN))
		{
			if(GetCursorSelection() == 3)
				SetCursorSelection(0);
			else
				SetCursorSelection(GetCursorSelection()  + 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
	}
	else
	{
		if(pDI->KeyPressed(DIK_ESCAPE) || pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(1) || pDI->JoystickButtonPressed(1) || pDI->JoystickButtonPressed(2))
		{
			m_bSubMenu = false;
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_A)|| pDI->JoystickDPadPressed(DIR_LEFT))
		{
			switch(GetCursorSelection())
			{
			case 0:
				if(m_nSubCursor == 0)
				{
					m_nMusicVolume -= 5;
					if(m_nMusicVolume < 0)
						m_nMusicVolume = 100;
					CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(m_nMusicVolume /100.0f);

				}
				else
				{
					m_nSFXVolume -= 5;
					if(m_nSFXVolume < 0)
						m_nSFXVolume = 100;
					CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(m_nSFXVolume /100.0f);

				}
				break;
			case 1:
				m_bIsWindow = true;
				CGame::GetInstance()->SetWindow(m_bIsWindow);
				CSGD_Direct3D::GetInstance()->Resize(CGame::GetInstance()->GetScreenWidth(),CGame::GetInstance()->GetScreenHeight(),CGame::GetInstance()->GetIsWindow());
				break;
			case 2:
				m_bIsMemory = false;
				CGame::GetInstance()->SetMemory(m_bIsMemory);

				break;
			default:
				break;
			}
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_D) || pDI->JoystickDPadPressed(DIR_RIGHT))
		{
			switch(GetCursorSelection())
			{
			case 0:
				if(m_nSubCursor == 0)
				{
					m_nMusicVolume += 5;
					if(m_nMusicVolume > 100)
						m_nMusicVolume = 0;
					CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(m_nMusicVolume /100.0f);
					if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
						CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
				}
				else
				{
					m_nSFXVolume += 5;
					if(m_nSFXVolume > 100)
						m_nSFXVolume = 0;
					CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(m_nSFXVolume /100.0f);
					if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
						CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
				}
				break;
			case 1:
				m_bIsWindow = false;
				CGame::GetInstance()->SetWindow(m_bIsWindow);
				CSGD_Direct3D::GetInstance()->Resize(CGame::GetInstance()->GetScreenWidth(),CGame::GetInstance()->GetScreenHeight(),CGame::GetInstance()->GetIsWindow());

				break;
			case 2:
				m_bIsMemory = true;
				CGame::GetInstance()->SetMemory(m_bIsMemory);

				break;
			default:
				break;
			}
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(GetCursorSelection() == 0)
		{
			if(pDI->KeyPressed(DIK_W) || pDI->JoystickDPadPressed(DIR_UP))
				m_nSubCursor = 0;
			else if(pDI->KeyPressed(DIK_S) || pDI->JoystickDPadPressed(DIR_DOWN))
				m_nSubCursor = 1;
		}
	}

	return true;
}
