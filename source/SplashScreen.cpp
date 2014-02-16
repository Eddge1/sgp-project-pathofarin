#include "SplashScreen.h"
#include "AnimationSystem.h"
#include "MainMenuState.h"
#include "Game.h"
#include <sstream>
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"

CSplashScreen* CSplashScreen::GetInstance( void )
{
	static CSplashScreen s_Instance;

	return &s_Instance;
}

CSplashScreen::CSplashScreen(void)
{
	m_szLoadStatus = "";
	SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/Menus/PoA_DNAS_Logo.png")));
	m_fPercentDone = 0.0f;
}


CSplashScreen::~CSplashScreen(void)
{
	CAnimationSystem::GetInstance()->DeleteInstance();
}

void CSplashScreen::Activate( void )
{
	m_szLoadStatus = "";
	m_fPercentDone = 0.0f;

	CAnimationSystem::GetInstance()->LoadAnimations();

}
void CSplashScreen::Sleep( void )	
{
	m_szLoadStatus = "";
	m_fPercentDone = 0.0f;

}
void CSplashScreen::Update( float fElapsedTime )
{
	CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
}
void CSplashScreen::Render( void )	
{
	std::wostringstream woss;
	RECT rTemp = {0,0,800,600};
	CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(),0,0, 1.0f,1.0f,&rTemp,0,0,0,D3DCOLOR_ARGB(200,255,255,255));

	RECT rLoadBar = {100,528,long(100 + (600 * m_fPercentDone)),560};
	CSGD_Direct3D::GetInstance()->DrawRect(rLoadBar, D3DCOLOR_XRGB(0,0,255));
	rLoadBar.right = 700;
	CSGD_Direct3D::GetInstance()->DrawHollowRect(rLoadBar, D3DCOLOR_XRGB(0,255,255));

	woss << "Loading " << m_szLoadStatus.c_str();
	CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 110,536,0.75f, D3DCOLOR_XRGB(255,255,255));
}
bool CSplashScreen::Input( void )	
{
	return true;
}