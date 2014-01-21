#include "MainMenuState.h"

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

#include "ProfileMenuState.h"
#include "GamePlayState.h"
#include "Game.h"

CMainMenuState* CMainMenuState::GetInstance( void )
{
	static CMainMenuState s_Instance;

	return &s_Instance;
}


CMainMenuState::CMainMenuState(void)
{

}



CMainMenuState::~CMainMenuState(void)
{

}


void CMainMenuState::Activate(void)
{

}

void CMainMenuState::Sleep(void)
{

}

void CMainMenuState::Update(float fElapsedTime)
{

}

void CMainMenuState::Render(void)
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	CBitmapFont* pFont = CGame::GetInstance()->GetFont();
	CBitmapFont* pFont2 = CGame::GetInstance()->GetFont2();

	//pD3D->DrawText(_T("This is the Main Menu"), 15,15, D3DCOLOR_XRGB(0,0,0));
	//pD3D->DrawText(_T("Hit 1 to change to a new State"), 15,35, D3DCOLOR_XRGB(0,0,0));
	pFont->Draw(_T("This is the Main Menu\nHit 1 to change to a new State"), 15, 15, 1.0f, D3DCOLOR_XRGB(0, 0, 255));
	pFont2->Draw(_T("A quick brown fox jumps over the lazy Dog!?"), 15, 100, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
}

bool CMainMenuState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
		return false;

	if(pDI->KeyPressed(DIK_1))
		CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
	return true;
}
