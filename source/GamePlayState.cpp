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
	CObjectManager*			pOM = CObjectManager::GetInstance();


	m_pES = CSGD_EventSystem::GetInstance();
	m_pRM = new CRenderManager;

	WorldHeight = CGame::GetInstance()->GetScreenHeight();
	WorldWidth = CGame::GetInstance()->GetScreenWidth();

	m_pPlayer = CreatePlayer();


	WorldCamX =  int(m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2));
	WorldCamY =  int(m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2));


	pOM->AddObject(m_pPlayer, 5); // Player goes on layer 5

}

void CGamePlayState::Sleep(void)
{
	CObjectManager* pOM = CObjectManager::GetInstance();
	// Clear the event system
	if( m_pES != nullptr )
	{
		m_pES->Terminate();
		m_pES = nullptr;
	}

	delete m_pRM;
	m_pRM = nullptr;
	m_pPlayer->Release();

	pOM->RemoveAll();
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
			SetCursorSelection(GetCursorSelection() - 1);
		if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_DOWN ) == true )
			SetCursorSelection(GetCursorSelection() + 1);

		if(GetCursorSelection() > 1)
			SetCursorSelection(0);
		else if(GetCursorSelection() < 0)
			SetCursorSelection(1);


		if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_RETURN ) == true )
		{
			switch( GetCursorSelection() )
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
					SetCursorSelection(0);
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
	CObjectManager* pOM = CObjectManager::GetInstance();

	if(bisPaused == false)
	{
		WorldCamX = int(m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2));
		WorldCamY = int(m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2));


		//if(WorldCamX < 0)
		//	WorldCamX = 0;
		//else if(WorldCamX > CGame::GetInstance()->GetScreenWidth() )
		//	WorldCamX = CGame::GetInstance()->GetScreenWidth();

		//if(WorldCamY < 0)
		//	WorldCamY = 0;
		//else if(WorldCamY > CGame::GetInstance()->GetScreenHeight() )
		//	WorldCamY = CGame::GetInstance()->GetScreenHeight();

		pOM->Update(fElapsedTime);
		m_pES->ProcessEvents();

	}
	else
		return;
}

void CGamePlayState::Render(void)
{
	RECT temp = { 0, 0, WorldHeight, WorldWidth };
	OffsetRect(&temp, -WorldCamX, -WorldCamY);
	CSGD_Direct3D::GetInstance()->DrawRect( temp, D3DCOLOR_XRGB( 255,255,0 ) );

	//RECT player = { m_pPlayer->GetPosX(), m_pPlayer->GetPosY(),  m_pPlayer->GetPosX() + 20, m_pPlayer->GetPosY() + 20};
	//CSGD_Direct3D::GetInstance()->DrawRect( player, D3DCOLOR_XRGB( 0,0,0 ) );



	m_pRM->Render();
}

CPlayer* CGamePlayState::CreatePlayer()
{
	CPlayer* temp = new CPlayer; // TODO: THIS IS A PLACE HOLDER
	temp->SetPosX(50.0f);
	temp->SetPosY(50.0f);
	temp->SetVelX(0.0f);
	temp->SetVelY(0.0f);
	return temp;
}


