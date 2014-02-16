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
	m_nLogoID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("assets/Graphics/Menus/PoA_Rizzle_Logo.png"));
	m_fDisappear1 = 1.0f;
	m_fDelay = 1.0f;
	m_fAppearDisappear = 0.0f;
	m_bComplete = false;
	m_bFadeIn = true;
}


CSplashScreen::~CSplashScreen(void)
{
	CAnimationSystem::GetInstance()->DeleteInstance();
}

void CSplashScreen::Activate( void )
{
	m_fDisappear1 = 1.0f;
	m_fAppearDisappear = 0.0f;
	m_fDelay = 1.0f;
	m_bComplete = false;
	m_bFadeIn = true;
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
	m_fPercentDone = 1.0f;
	if(m_fDisappear1 > 0)
		m_fDisappear1 -= 0.5f*fElapsedTime;
	else
	{
		if(m_bFadeIn)
		{
			m_fAppearDisappear += 0.5f*fElapsedTime;
			if(m_fAppearDisappear >= 1.0f)
			{
				m_bFadeIn = false;
				m_fAppearDisappear = 1.0f;
			}
		}
		else
		{
			m_fDelay -= 1.0f * fElapsedTime;
			if(m_fDelay <= 0.0f)
			{
				if(m_fAppearDisappear > 0)
				{
					m_fAppearDisappear -= 0.5f*fElapsedTime;
					if(m_fAppearDisappear < 0.0f)
						m_fAppearDisappear = 0;

				}
				if(m_fAppearDisappear <= 0)
				{
					m_fAppearDisappear = 0.0f;
					m_bComplete = true;
				}
			}
		}

	}

	if(m_bComplete)
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
}
void CSplashScreen::Render( void )	
{
	std::wostringstream woss;
	RECT rTemp = {0,0,800,600};
	if(m_fDisappear1 > 0.0f)
		CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(),0,0, 1.0f,1.0f,&rTemp,0,0,0,D3DCOLOR_ARGB(char(255 * (m_fDisappear1)),255,255,255));
	else
		CSGD_TextureManager::GetInstance()->Draw(m_nLogoID,0,0, 1.0f,1.0f,&rTemp,0,0,0,D3DCOLOR_ARGB(char(255 * (m_fAppearDisappear)),255,255,255));

	if(m_fPercentDone < 1.0f)
	{
		RECT rLoadBar = {100,528,long(100 + (600 * m_fPercentDone)),560};
		CSGD_Direct3D::GetInstance()->DrawRect(rLoadBar, D3DCOLOR_XRGB(0,0,255));
		rLoadBar.right = 700;
		CSGD_Direct3D::GetInstance()->DrawHollowRect(rLoadBar, D3DCOLOR_XRGB(0,255,255));
		woss << "Loading " << m_szLoadStatus.c_str();
		CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 110,536,0.75f, D3DCOLOR_XRGB(255,255,255));
	}
}
bool CSplashScreen::Input( void )	
{
	return true;
}