#include "GameOverState.h"
#include "MainMenuState.h"
#include "Game.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

CGameOverState::CGameOverState(void)
{
	m_music = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("Assets/Audio/Music/POA_DEATH.xwm"));
	m_background = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_GameOver.png"));
	m_cursor = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png"));
	timer = 10.0f;
	SetBackgroundMusic(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(-1);
	SetSFXID(-1);
	selection = 0;
	m_bMainMenu = false;
	m_fFadeScreen = 0.0f;
	m_fFadeText = 0.0f;
}

CGameOverState::~CGameOverState(void)
{
	Sleep();
}

CGameOverState* CGameOverState::GetInstance( void )
{
	static CGameOverState s_Instance;

	return &s_Instance;
}

void CGameOverState::Activate(void)
{
	CSGD_XAudio2::GetInstance()->MusicPlaySong(m_music, true);
	CGamePlayState::GetInstance()->Sleep();
	CProfileMenuState::GetInstance()->Activate();
}

void CGameOverState::Sleep(void)
{
	m_bShowMenu = false;
	m_bMainMenu = false;
	m_fFadeScreen = 0.0f;
	m_fFadeText = 0.0f;

	CProfileMenuState::GetInstance()->Sleep();
	m_szGameOverMsg ="";
}

void CGameOverState::Update(float fElapsedTime)
{
	if(!m_bMainMenu && !m_bShowMenu)
	{
		if(m_fFadeScreen < 1.0f)
		{
			m_fFadeScreen += 0.5f * fElapsedTime;
			if(m_fFadeScreen >= 1.0f)
			{
				m_fFadeScreen = 1.0f;
				m_bShowMenu = true;
			}
		}
	}
	else if(!m_bMainMenu && m_bShowMenu)
	{
		if(m_fFadeText < 1.0f)
		{
			m_fFadeText += 0.5f * fElapsedTime;
			if(m_fFadeText >= 1.0f)
				m_fFadeText = 1.0f;
		}

	}
	else if(m_bMainMenu)
	{
		m_fFadeScreen -= 0.5f * fElapsedTime;
		m_fFadeText -= 0.5f * fElapsedTime;
		if(m_fFadeScreen <= 0.0f)
		{
			m_fFadeScreen = 0.0f;
			m_bMainMenu = false;
			CGamePlayState::GetInstance()->SetGameState(GP_END);
			CGamePlayState::GetInstance()->Sleep();
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(m_music))
				CSGD_XAudio2::GetInstance()->MusicStopSong(m_music);
		}
	}

}

void CGameOverState::Render(void)
{
	RECT rBackground = {0,0,800,600};
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
	CSGD_Direct3D::GetInstance()->DrawRect(rBackground, D3DCOLOR_XRGB(0,0,0));
	pTM->Draw(m_background,0,0, 1.0f,1.0f,&rBackground,0,0,0,D3DCOLOR_ARGB((char)(255 * (m_fFadeScreen)),255,255,255));
	if(m_bShowMenu)
	{
		wostringstream woss;
		woss << m_szGameOverMsg.c_str();
		CBitmapFont* temp = CGame::GetInstance()->GetFont("Arial");
		temp->Draw(_T("Game Over"), 300, 300, 1.0f, D3DCOLOR_ARGB(char(255 * m_fFadeText),255,255,255));
		temp->Draw(woss.str().c_str(), 400 - int(m_szGameOverMsg.size() * 16 / 2 * 0.75f), 272, 0.75, D3DCOLOR_ARGB(char(255 * m_fFadeText),255,255,255));
		RECT tempR = { 250, 300, 500, 400 };
		CSGD_Direct3D::GetInstance()->DrawHollowRect(tempR, D3DCOLOR_ARGB(char(255 * m_fFadeText),255,255,255));
		temp->Draw(_T("Continue?"), 280, 320, 0.8f, D3DCOLOR_ARGB(char(255 * m_fFadeText),255,255,255));
		temp->Draw(_T("Exit?"), 280, 340, 0.8f, D3DCOLOR_ARGB(char(255 * m_fFadeText),255,255,255));

		RECT rCursor = {0,0,16,32};
		if(selection == 0)
		{
			pTM->Draw(m_cursor, 260,325,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2, D3DCOLOR_ARGB((char)(255 * m_fFadeText),255,255,255));
		}
		else if( selection == 1)
		{
			pTM->Draw(m_cursor, 260,345,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2, D3DCOLOR_ARGB((char)(255 * m_fFadeText),255,255,255));
		}
	}
}

bool CGameOverState::Input(void)
{
	if(m_bShowMenu && m_fFadeText >= 1.0f && !m_bMainMenu)
	{
		CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

		if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(1))
		{
			switch(selection)
			{
			case 0:
				{
					CProfileMenuState::GetInstance()->ContinueGame(CProfileMenuState::GetInstance()->GetCursorSelection());
					if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(m_music))
						CSGD_XAudio2::GetInstance()->MusicStopSong(m_music);
					break;
				}
			case 1:
				{
					m_bMainMenu = true;
					break;
				}
			}
		}


		if(pDI->KeyPressed(DIK_UP) || pDI->KeyPressed(DIK_W) || pDI->JoystickDPadPressed(DIR_UP) || pDI->JoystickGetLStickDirPressed(DIR_UP))
		{
			selection += 1;

			if(selection > 1)
				selection = 0;
		}
		else if(pDI->KeyPressed(DIK_DOWN) || pDI->KeyPressed(DIK_S) || pDI->JoystickDPadPressed(DIR_DOWN) || pDI->JoystickGetLStickDirPressed(DIR_DOWN))
		{
			selection -= 1;

			if(selection < 0)
				selection = 1;
		}

	}
	return true;
}

