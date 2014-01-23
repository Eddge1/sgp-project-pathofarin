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
#include "CharacterMenuState.h"
#include "BattleState.h"



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

	m_eCurrPhase = GP_START;
}


// Destructor
CGamePlayState::~CGamePlayState(void)
{
}


void CGamePlayState::Activate(void)
{
	switch (m_eCurrPhase)
	{
	case CGamePlayState::GP_NAV:
		break;
	case CGamePlayState::GP_BATTLE:
		break;
	case CGamePlayState::GP_MENU:
		break;
	case CGamePlayState::GP_START:
		{
			CObjectManager*			pOM = CObjectManager::GetInstance();

			m_pES = CSGD_EventSystem::GetInstance();
			m_pRM = new CRenderManager;

			WorldHeight = CGame::GetInstance()->GetScreenHeight();
			WorldWidth = CGame::GetInstance()->GetScreenWidth();

			m_pPlayer = CreatePlayer();


			WorldCamX =  int(m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2));
			WorldCamY =  int(m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2));

			pOM->AddObject(m_pPlayer, 5); // Player goes on layer 5

			m_pES->RegisterClient("INIT_BATTLE", this);
			m_pES->RegisterClient("GAME_OVER", this);
			m_pES->RegisterClient("PLAYER_MENU", this);
			m_eCurrPhase = GP_NAV;
		}
		break;
	case CGamePlayState::GP_END:
		break;
	default:
		break;
	}



}

void CGamePlayState::Sleep(void)
{

	switch (m_eCurrPhase)
	{
	case CGamePlayState::GP_BATTLE:
		break;
	case CGamePlayState::GP_MENU:
		break;
	case CGamePlayState::GP_START:
		break;
	case CGamePlayState::GP_NAV:
	case GamePhase::GP_END:
		{
			m_pES->UnregisterClientAll(this);
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

			m_eCurrPhase = GP_START;
		}
		break;
	default:
		break;
	}

}

bool CGamePlayState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_ESCAPE ) == true)
	{
		bisPaused = !bisPaused;
		return true;
	}
	else if(bisPaused)
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
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
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
		pOM->HandleCollision(5,5);
		m_pES->ProcessEvents();
		m_temp.Update(fElapsedTime);

		m_pES->ProcessEvents();
	}
}

void CGamePlayState::Render(void)
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	RECT temp = { 0, 0, WorldHeight, WorldWidth };
	OffsetRect(&temp, -WorldCamX, -WorldCamY);
	pD3D->DrawRect( temp, D3DCOLOR_XRGB( 255,255,0 ) );

	m_pRM->Render();
	m_temp.Render();

	if(bisPaused)
	{
		RECT rTemp = {336, 236, 464,364};
		pD3D->DrawHollowRect(rTemp, D3DCOLOR_XRGB(0,127,255));

		CGame::GetInstance()->GetFont2()->Draw(_T("Resume\nQuit"), 352,244, 1.0f, D3DCOLOR_XRGB(0, 0, 255));
		CGame::GetInstance()->GetFont2()->Draw(_T("-"), 344,244 + (GetCursorSelection() * 28), 1.0f, D3DCOLOR_XRGB(0, 0, 255));
	}
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

void CGamePlayState::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "INIT_BATTLE")
	{
		m_eCurrPhase = GP_BATTLE;
		CGame::GetInstance()->ChangeState(CBattleState::GetInstance());
	}
	else if(pEvent->GetEventID() == "GAME_OVER")
	{
		m_eCurrPhase = GP_END;
		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
	}
	else if(pEvent->GetEventID() == "PLAYER_MENU")
	{

	}
}
