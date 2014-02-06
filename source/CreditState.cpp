#include "CreditState.h"
#include "MainMenuState.h"
#include "Game.h"
#include <sstream>

CCreditState::CCreditState(void)
{
	m_szCredits = "\t            Path of Arin\n\t\tCredits\nExecutive Producer:\t John Oleske\nAssociate Producer:\t Robert Martinez\n\nProgrammer:\t\t James Bean\nProgrammer:\t\t David Lindley\nProgrammer:\t\t Daniel Tyree\n\nArtist:\t\t\tGregory Bey\nArtist:\t\t\tCaris Frasier";
	SetBackgroundMusic(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(-1);
	SetSFXID(-1);
}



CCreditState::~CCreditState(void)
{
	Sleep();
}

CCreditState* CCreditState::GetInstance( void )
{
	static CCreditState s_Instance;

	return &s_Instance;
}

void CCreditState::Activate( void )	
{
	m_fDrawY = 600.0f;
	//SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_MainMenu.png")));

}

void CCreditState::Sleep( void )	
{
	//SetBackgroundImg(-1);
}

void CCreditState::Update( float fElapsedTime )	
{
	m_fDrawY -= (100 * fElapsedTime);

	if(m_fDrawY < -300)
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());

}

void CCreditState::Render( void )
{
	CBitmapFont *pFont = CGame::GetInstance()->GetFont2();
	//CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(),0,0);

	std::wostringstream woss;
	woss << m_szCredits.c_str();

	pFont->Draw(woss.str().c_str(), 100,int(m_fDrawY), 1.0f, D3DCOLOR_XRGB(255,0,0));
}

bool CCreditState::Input( void )
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());

	return true;
}