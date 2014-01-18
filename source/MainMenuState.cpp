#include "MainMenuState.h"

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

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

}

bool CMainMenuState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
		return false;

	return true;
}
