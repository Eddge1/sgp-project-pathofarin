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
	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));
	m_nLogoID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_logo.png"));
	m_fPosY = 0;
	m_fOffSetX = 0;
	m_bLeft = false;
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
	m_bLeft = false;
	m_fOffSetX = 0.0f;
	m_fPosY = 172.0f;

	m_bSubMenu = false;
	CGame* pGame = CGame::GetInstance();
	m_bIsMemory = pGame->GetMemory();
	m_bIsWindow = pGame->GetIsWindow();

	m_nMusicVolume = int(CSGD_XAudio2::GetInstance()->MusicGetMasterVolume() * 100);
	m_nSFXVolume = int(CSGD_XAudio2::GetInstance()->SFXGetMasterVolume() * 100);

	SetSFXID(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/SFX/POA_CursorSFX.wav")));

}

void COptionsMenu::Sleep( void )
{

}

void COptionsMenu::Update( float fElapsedTime )
{
	if(m_fPosY > 0)
	{
		m_fPosY -= 200 * fElapsedTime;
		return;
	}
	else
	{
		if(m_bLeft)
			m_fOffSetX -= (20 * fElapsedTime);
		else
			m_fOffSetX += (20 * fElapsedTime);

		if(m_fOffSetX >= 10.0f)
			m_bLeft = true;
		else if(m_fOffSetX <= 0.0f)
			m_bLeft = false;
	}
}

void COptionsMenu::Render( void )
{
	RECT rLogo = {0,0,512,256};
	CSGD_TextureManager::GetInstance()->Draw(m_nLogoID,144,(int)m_fPosY,1.0f,1.0f,&rLogo,0.0f,0.0f,0.0f,D3DCOLOR_ARGB(230,255,255,255));

	std::wostringstream woss;
	RECT rCursor = {0,0,16,32};
	CGame::GetInstance()->GetFont()->Draw(_T("Sound:\n\n\nGraphics:\n\nSave Cursor Location:\n\nReturn"), 136,250,0.75f,D3DCOLOR_XRGB(0,0,0));
	CGame::GetInstance()->GetFont()->Draw(_T("Music:\nSfx:"), 196,270,0.75f,D3DCOLOR_XRGB(0,0,0));
	CGame::GetInstance()->GetFont()->Draw(_T("Windowed\t\tFullscreen"), 196,338,0.75f,D3DCOLOR_XRGB(0,0,0));
	CGame::GetInstance()->GetFont()->Draw(_T("No\t\t\tYes"), 196,380,0.75f,D3DCOLOR_XRGB(0,0,0));

	switch (GetCursorSelection())
	{
	case 0:
		if(!m_bSubMenu)
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),128,254,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),128,254,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));

		break;
	case 1:
		if(!m_bSubMenu)
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),128,320,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),128,320,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));

		break;
	case 2:
		if(!m_bSubMenu)
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),128,364,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),128,364,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));

		break;
	case 3:
		if(!m_bSubMenu)
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),128,408,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),128,364,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));

		break;
	default:
		break;
	}

	switch(m_nSubCursor)
	{
	case 0:
		if(m_bSubMenu)
		{
			if(GetCursorSelection() == 0)
			{
				CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),187,274,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
			}
		}
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),187,274,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
		break;
	case 1:
		if(m_bSubMenu)
		{
			if(GetCursorSelection() == 0)
			{
				CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),187,296,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
			}
		}
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),187,296,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
		break;
	default:
		break;
	}

	if(m_bSubMenu)
	{
		if(!m_bIsWindow)
		{
			if(GetCursorSelection() == 1)

				CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),468,342,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		}
		else
		{
			if(GetCursorSelection() == 1)

				CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),187,342,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		}

		if(m_bIsMemory)
		{
			if(GetCursorSelection() == 2)

				CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),468,383,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		}
		else
		{
			if(GetCursorSelection() == 2)

				CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),187,383,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		}
	}
	else
	{
		if(!m_bIsWindow)
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),468,342,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),187,342,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));

		if(m_bIsMemory)
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),468,383,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),187,383,1.0f,1.0f,&rCursor,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
	}

	RECT rMusic = {273, 275, 273 + (213 * (m_nMusicVolume / 100.0f)), 288};
	CSGD_Direct3D::GetInstance()->DrawRect(rMusic, D3DCOLOR_XRGB(0,255,255));
	rMusic.top += 4;
	rMusic.bottom -= 4;
	CSGD_Direct3D::GetInstance()->DrawRect(rMusic, D3DCOLOR_XRGB(255,255,255));
	rMusic.top -= 4;
	rMusic.bottom += 4;
	rMusic.right = 485;
	CSGD_Direct3D::GetInstance()->DrawHollowRect(rMusic, D3DCOLOR_XRGB(0,0,0),3);
	woss.str(_T(""));
	woss << m_nMusicVolume;
	CGame::GetInstance()->GetFont()->Draw(woss.str().c_str(), 487,268,0.75f,D3DCOLOR_ARGB(255,0,0,0));

	RECT rSFX = {273,297,273 + (213 * (m_nSFXVolume / 100.0f)),310};
	CSGD_Direct3D::GetInstance()->DrawRect(rSFX, D3DCOLOR_XRGB(0,255,255));
	rSFX.top += 4;
	rSFX.bottom -= 4;
	CSGD_Direct3D::GetInstance()->DrawRect(rSFX, D3DCOLOR_XRGB(255,255,255));
	rSFX.top -= 4;
	rSFX.bottom += 4;
	rSFX.right = 485;
	CSGD_Direct3D::GetInstance()->DrawHollowRect(rSFX, D3DCOLOR_XRGB(0,0,0),3);
	woss.str(_T(""));
	woss << m_nSFXVolume;
	CGame::GetInstance()->GetFont()->Draw(woss.str().c_str(), 487,290,0.75f,D3DCOLOR_ARGB(255,0,0,0));
}

bool COptionsMenu::Input( void )	
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(m_fPosY <= 0.0f)
	{
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
	}
	return true;
}
