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
	CBitmapFont* pFont2 = CGame::GetInstance()->GetFont2();

	pFont2->Draw(_T("Path of Arin"), 200,100, 3.0f, D3DCOLOR_XRGB(0, 0, 255));
	RECT rTemp = {336, 408, 464,536};
	pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,127,255));
	pFont2->Draw(_T("Play\nOptions\nCredits\nExit"), 352,416, 1.0f, D3DCOLOR_XRGB(0, 0, 255));
	pFont2->Draw(_T("-"), 344,416 + (GetCursorSelection() * 28), 1.0f, D3DCOLOR_XRGB(0, 0, 255));

}

bool CMainMenuState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
		return false;

	if(pDI->KeyPressed(DIK_UPARROW))
	{
		if(GetCursorSelection() <= 0)
			SetCursorSelection(3);
		else
			SetCursorSelection(GetCursorSelection() - 1);
	}
	else if(pDI->KeyPressed(DIK_DOWNARROW))
	{
		if(GetCursorSelection() >= 3)
			SetCursorSelection(0);
		else
			SetCursorSelection(GetCursorSelection() + 1);

	}
	else if(pDI->KeyPressed(DIK_RETURN))
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
