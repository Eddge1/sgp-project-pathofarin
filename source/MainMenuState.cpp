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

bool CMainMenuState::Input(void)
{
	return true;
}
