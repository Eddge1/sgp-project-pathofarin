#include "OptionsMenu.h"
#include "MainMenuState.h"
#include "Game.h"

COptionsMenu::COptionsMenu(void)
{

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
	CGame* pGame = CGame::GetInstance();
	m_bIsMemory = pGame->GetMemory();
	m_bIsWindow = pGame->GetIsWindow();


}
void COptionsMenu::Sleep( void )
{

}
void COptionsMenu::Update( float fElapsedTime )
{

}
void COptionsMenu::Render( void )
{
	CBitmapFont* pFont2 = CGame::GetInstance()->GetFont2();

	pFont2->Draw(_T("Options"), 10,10, 3.0f, D3DCOLOR_XRGB(0, 0, 255));
	pFont2->Draw(_T("Sound"), 10,120,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	pFont2->Draw(_T("Graphics"), 10,240,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	pFont2->Draw(_T("Cursor Memory"), 10,300,1.0f, D3DCOLOR_XRGB(0, 0, 0));
	pFont2->Draw(_T("Return"), 10,540,1.0f, D3DCOLOR_XRGB(0, 0, 0));


}
bool COptionsMenu::Input( void )	
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
	{
		//CGame::GetInstance()->SetMemory( );
		//CGame::GetInstance()->SetWindow( );
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
	}

	if(m_bSubMenu)
	{



	}

	return true;
}
