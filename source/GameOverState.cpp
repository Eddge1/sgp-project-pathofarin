#include "GameOverState.h"
#include "MainMenuState.h"
#include "Game.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"

CGameOverState::CGameOverState(void)
{
	m_music = -1;
	timer = 10.0f;
	SetBackgroundMusic(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(-1);
	SetSFXID(-1);
	selection = 0;
}

CGameOverState::~CGameOverState(void)
{
	CGame::GetInstance()->ChangeState(nullptr);
}

CGameOverState* CGameOverState::GetInstance( void )
{
	static CGameOverState s_Instance;

	return &s_Instance;
}

void CGameOverState::Activate(void)
{
	m_music = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("Assets/Audio/Music/POA_DEATH.xwm"));
	CSGD_XAudio2::GetInstance()->MusicPlaySong(m_music, true);
	CGamePlayState::GetInstance()->Sleep();
	CProfileMenuState::GetInstance()->Activate();
}

void CGameOverState::Sleep(void)
{
	CSGD_XAudio2::GetInstance()->MusicUnloadSong(m_music);
	CProfileMenuState::GetInstance()->Sleep();

}

void CGameOverState::Update(float fElapsedTime)
{

}

void CGameOverState::Render(void)
{
	CBitmapFont* temp = CGame::GetInstance()->GetFont();
	temp->Draw(_T("Game Over"), 300, 300, 1.0f, D3DCOLOR_XRGB(0,0,0));


	RECT tempR = { 250, 300, 500, 400 };
	CSGD_Direct3D::GetInstance()->DrawHollowRect(tempR, D3DCOLOR_XRGB(0,0,0));
	temp->Draw(_T("Continue?"), 280, 320, 0.8f, D3DCOLOR_XRGB(0,0,0));
	temp->Draw(_T("Exit?"), 280, 340, 0.8f, D3DCOLOR_XRGB(0,0,0));

	if(selection == 0)
	{
		RECT temp = { 260, 325, 265, 335 };
		CSGD_Direct3D::GetInstance()->DrawHollowRect(temp, D3DCOLOR_XRGB(0,0,0));
	}
	else if( selection == 1)
	{
		RECT temp = { 260, 345, 265, 355 };
		CSGD_Direct3D::GetInstance()->DrawHollowRect(temp, D3DCOLOR_XRGB(0,0,0));
	}





}

bool CGameOverState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_RETURN))
	{
		switch(selection)
		{
		case 0:
			{
				CProfileMenuState::GetInstance()->ContinueGame(CProfileMenuState::GetInstance()->GetCursorSelection());
				break;
			}
		case 1:
			{
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
				break;
			}
		}
	}


	if(pDI->KeyPressed(DIK_UP) || pDI->KeyPressed(DIK_W))
	{
		selection += 1;

		if(selection > 1)
			selection = 0;
	}
	else if(pDI->KeyPressed(DIK_DOWN) || pDI->KeyPressed(DIK_S))
	{
		selection -= 1;

		if(selection < 0)
			selection = 1;
	}


	return true;
}

