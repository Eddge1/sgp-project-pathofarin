#include "CreditState.h"
#include "MainMenuState.h"
#include "Game.h"

CCreditState::CCreditState(void)
{

}



CCreditState::~CCreditState(void)
{

}

CCreditState* CCreditState::GetInstance( void )
{
	static CCreditState s_Instance;

	return &s_Instance;
}
void CCreditState::Activate( void )	
{

}
void CCreditState::Sleep( void )	
{

}
void CCreditState::Update( float fElapsedTime )	
{

}
void CCreditState::Render( void )
{

}
bool CCreditState::Input( void )
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());

	return true;
}