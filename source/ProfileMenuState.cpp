#include "ProfileMenuState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"

#include "MainMenuState.h"
#include "Game.h"

	CProfileMenuState::CProfileMenuState(void)
	{

	}
CProfileMenuState::~CProfileMenuState(void)
{
}

CProfileMenuState* CProfileMenuState::GetInstance( void )
{
	static CProfileMenuState s_Instance;

	return &s_Instance;
}

void CProfileMenuState::Activate()
{


}

void CProfileMenuState::Sleep()
{


}

bool CProfileMenuState::Input()
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(pDI->KeyPressed(DIK_ESCAPE))
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
	return true;
}

void CProfileMenuState::Update(float fElapsedTime )
{


}

void CProfileMenuState::Render()
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	pD3D->DrawText(_T("We are in the Profile Menu State"),15,15, D3DCOLOR_XRGB(0,0,0));

}
