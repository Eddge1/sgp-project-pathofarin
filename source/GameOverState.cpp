#include "GameOverState.h"
#include "MainMenuState.h"
#include "Game.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"

CGameOverState::CGameOverState(void)
{
	m_music = CSGD_XAudio2::GetInstance()->MusicLoadSong(_T("Assets/Audio/Music/POA_DEATH.xwm"));
	timer = 10.0f;
	SetBackgroundMusic(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(-1);
	SetSFXID(-1);
	selection = 0;
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


	CProfileMenuState::GetInstance()->Sleep();
	m_szGameOverMsg ="";
}

void CGameOverState::Update(float fElapsedTime)
{

}

void CGameOverState::Render(void)
{
	RECT clearscreenson = {0, 0, 800, 600};
	CSGD_Direct3D::GetInstance()->DrawRect(clearscreenson, D3DCOLOR_XRGB(255,255,255));
	wostringstream woss;
	woss << m_szGameOverMsg.c_str();
	CBitmapFont* temp = CGame::GetInstance()->GetFont("Arial");
	temp->Draw(_T("Game Over"), 300, 300, 1.0f, D3DCOLOR_XRGB(0,0,0));
	temp->Draw(woss.str().c_str(), 400 - int(m_szGameOverMsg.size() * 16 / 2 * 0.75f), 272, 0.75, D3DCOLOR_XRGB(255,0,0));
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
				CGamePlayState::GetInstance()->SetGameState(GP_END);
				CGamePlayState::GetInstance()->Sleep();
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
				if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(m_music))
					CSGD_XAudio2::GetInstance()->MusicStopSong(m_music);
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


	return true;
}

