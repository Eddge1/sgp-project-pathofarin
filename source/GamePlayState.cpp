#include "GamePlayState.h"

#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "../SGD Wrappers/SGD_Math.h"

#include "Objects.h"
#include "ObjectManager.h"
#include "Player.h"
#include "RenderManager.h"
#include "Game.h"
#include "MainMenuState.h"



// GetInstance
CGamePlayState* CGamePlayState::GetInstance( void )
{
	static CGamePlayState s_Instance;

	return &s_Instance;
}



CGamePlayState::CGamePlayState(void)
{
	m_pES = nullptr;
	m_pOM = nullptr;
	m_pRM = nullptr;

	m_pPlayer = nullptr;
	bisPaused = false;

	m_nCursor = 0;
}


// Destructor
CGamePlayState::~CGamePlayState(void)
{
}


void CGamePlayState::Activate(void)
{
	// SGD Wrapper singletons initialized in CGame
	CSGD_TextureManager*	pTM	= CSGD_TextureManager::GetInstance();
	CSGD_XAudio2*			pXA	= CSGD_XAudio2::GetInstance();

	m_pES = CSGD_EventSystem::GetInstance();

	WorldHeight = CGame::GetInstance()->GetScreenHeight();
	WorldWidth = CGame::GetInstance()->GetScreenWidth();

	WorldCamX =  m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2);
	WorldCamY =  m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2);


}

void CGamePlayState::Sleep(void)
{
	// Clear the event system
	if( m_pES != nullptr )
	{
		m_pES->Terminate();
		m_pES = nullptr;
	}


	//m_pPlayer->Release();
}

bool CGamePlayState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_ESCAPE ) == true )
	{
		bisPaused = !bisPaused;
		return true;
	}

	if(bisPaused)
	{
		if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_UP ) == true )
			m_nCursor++;
		if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_DOWN ) == true )
			m_nCursor--;

		if(m_nCursor > 1)
			m_nCursor = 0;
		else if(m_nCursor < 0)
			m_nCursor = 1;


		if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_RETURN ) == true )
		{
			switch( m_nCursor )
			{
			case 0:			// PLAY
				{
					bisPaused = !bisPaused;
					return true;
				}
				break;


			case 1:			
				{
					bisPaused = !bisPaused;
					CGame::GetInstance()->ChangeState( CMainMenuState::GetInstance() ); // Will return you to the main menu
					m_nCursor = 0;
					return true;
				}
				break;
			}


		}
	}





	return true;
}

void CGamePlayState::Update( float fElapsedTime )
{
	if(bisPaused == false)
	{
		WorldCamX = m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2);
		WorldCamY = m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2);

		m_pES->ProcessEvents();
	}
	else
		return;
}

void CGamePlayState::Render(void)
{

}

CPlayer* CGamePlayState::CreatePlayer()
{
	CPlayer* temp = new CPlayer; // TODO: THIS IS A PLACE HOLDER
	return temp;
}


