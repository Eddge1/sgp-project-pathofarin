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
}



COptionsMenu::~COptionsMenu(void)
{

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
	if(m_bIsWindow != CGame::GetInstance()->GetIsWindow())
	{
		CGame::GetInstance()->SetWindow(m_bIsWindow);
		CSGD_Direct3D::GetInstance()->Resize(CGame::GetInstance()->GetScreenWidth(),CGame::GetInstance()->GetScreenHeight(),CGame::GetInstance()->GetIsWindow());
	}
	if(m_bIsMemory != CGame::GetInstance()->GetMemory())
		CGame::GetInstance()->SetMemory(m_bIsMemory);
	CGame::GetInstance()->CreateConfig(m_nMusicVolume, m_nSFXVolume, m_bIsWindow, m_bIsMemory);

}

void COptionsMenu::Update( float fElapsedTime )
{

}

void COptionsMenu::Render( void )
{
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
		if(pDI->KeyPressed(DIK_ESCAPE))
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		else if(pDI->KeyPressed(DIK_RETURN))
		{
			if(GetCursorSelection() ==3)
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			else
				m_bSubMenu = true;
		}
		else if(pDI->KeyPressed(DIK_UPARROW))
		{
			if(GetCursorSelection() == 0)
				SetCursorSelection(3);
			else
				SetCursorSelection(GetCursorSelection()  - 1);
		}
		else if(pDI->KeyPressed(DIK_DOWNARROW))
		{
			if(GetCursorSelection() == 3)
				SetCursorSelection(0);
			else
				SetCursorSelection(GetCursorSelection()  + 1);
		}
	}
	else
	{
		if(pDI->KeyPressed(DIK_ESCAPE) || pDI->KeyPressed(DIK_RETURN))
		{
			m_bSubMenu = false;
		}
		else if(pDI->KeyPressed(DIK_LEFTARROW))
		{
			switch(GetCursorSelection())
			{
			case 0:
				if(m_nSubCursor == 0)
				{
					m_nMusicVolume -= 5;
					if(m_nMusicVolume < 0)
						m_nMusicVolume = 100;

					CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(m_nMusicVolume * 0.01f);
				}
				else
				{
					m_nSFXVolume -= 5;
					if(m_nSFXVolume < 0)
						m_nSFXVolume = 100;
					CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(m_nSFXVolume * 0.01f);
				}
				break;

			case 1:
				m_bIsWindow = true;
				break;


			case 2:
				m_bIsMemory = false;
				break;

			default:
				break;

			}
		}
		else if(pDI->KeyPressed(DIK_RIGHTARROW))
		{
			switch(GetCursorSelection())
			{
			case 0:
				if(m_nSubCursor == 0)
				{
					m_nMusicVolume += 5;
					if(m_nMusicVolume > 100)
						m_nMusicVolume = 0;
					CSGD_XAudio2::GetInstance()->MusicSetMasterVolume(m_nMusicVolume * 0.01f);
				}
				else
				{
					m_nSFXVolume += 5;
					if(m_nSFXVolume > 100)
						m_nSFXVolume = 0;

					CSGD_XAudio2::GetInstance()->SFXSetMasterVolume(m_nSFXVolume * 0.01f);
				}
				break;

			case 1:
				m_bIsWindow = false;
				break;


			case 2:
				m_bIsMemory = true;
				break;

			default:
				break;

			}
		}
		else if(GetCursorSelection() == 0)
		{
			if(pDI->KeyPressed(DIK_UPARROW))
				m_nSubCursor = 0;
			else if(pDI->KeyPressed(DIK_DOWNARROW))
				m_nSubCursor = 1;
		}
	}

	return true;
}
