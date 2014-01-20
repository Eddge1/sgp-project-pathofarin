#include "Game.h"
#include "GameStates.h"
#include "MainMenuState.h"

CGame* CGame::s_pInstance = nullptr;

// GetInstance
CGame* CGame::GetInstance( void ) // Remember these are static.
{
	// Allocate the static pointer if necessary
	if( s_pInstance == nullptr )
		s_pInstance = new CGame;

	// Return the singleton
	return s_pInstance;
}

// DeleteInstance
void CGame::DeleteInstance( void )
{
	delete s_pInstance;
	s_pInstance = nullptr;
}


CGame::CGame(void)
{
	// - set all the data members to clean values.
	m_pD3D			= nullptr;
	m_pDI			= nullptr;
	m_pTM			= nullptr;
	m_pXA			= nullptr;

	m_nScreenWidth	= 1;
	m_nScreenHeight	= 1;
	m_bIsWindowed	= true;

	m_pCurrState	= nullptr;

	m_dwCurrTime	= 0;

	// seeding the random number generator
	srand( (unsigned int)time( nullptr ) );
}


CGame::~CGame(void)
{

}


void CGame::Initialize( HWND hWnd, HINSTANCE hInstance,
					   int nWidth, int nHeight,
					   bool bIsWindowed )
{
	// Store the SGD Wrapper singletons
	m_pD3D			= CSGD_Direct3D::GetInstance();
	m_pDI			= CSGD_DirectInput::GetInstance();
	m_pTM			= CSGD_TextureManager::GetInstance();
	m_pXA			= CSGD_XAudio2::GetInstance();

	// Store the parameters
	m_nScreenWidth	= nWidth;
	m_nScreenHeight	= nHeight;
	m_bIsWindowed	= bIsWindowed;


	// Initialize the wrappers
	m_pD3D->Initialize( hWnd, m_nScreenWidth, m_nScreenHeight, m_bIsWindowed, false );
	m_pDI->Initialize( hWnd, hInstance, DI_KEYBOARD /*| DI_MOUSE*/ | DI_JOYSTICKS );
	m_pTM->Initialize( m_pD3D->GetDirect3DDevice(),	m_pD3D->GetSprite() );
	m_pXA->Initialize();



	// Start in the Main Menu state
	ChangeState( CMainMenuState::GetInstance() );

	// Store the current time
	m_dwCurrTime	= GetTickCount();
}

// Run
// - run one frame of the gameplay
bool CGame::Run( void )
{
	// Update & render
	if( Update() == false)
		return false;

	Render();
	return true;
}

//Terminate
// - shutting down the SGD wrappers( in reverse order )
void CGame::Terminate(void)
{
	// Exit the current state
	ChangeState( nullptr );

	// Shutdown the wrappers
	m_pXA->Terminate();
	m_pTM->Terminate();
	m_pDI->Terminate();
	m_pD3D->Terminate();

	// Reset the data members to null so they cant use them
	m_pD3D			= nullptr;
	m_pDI			= nullptr;
	m_pTM			= nullptr;
	m_pXA			= nullptr;

	m_nScreenWidth	= 1;
	m_nScreenHeight	= 1;
	m_bIsWindowed	= true;

}

// Update
//	- update the game
bool CGame::Update( void )
{
	// Update the audio
	m_pXA->Update();


	// Calculate the elapsed time between frames
	DWORD dwNow = GetTickCount();
	float fElapsedTime = (dwNow - m_dwCurrTime) / 1000.0f;
	m_dwCurrTime = dwNow;


	// Cap the elapsed time to 1/8th
	if( fElapsedTime > 0.125f )
		fElapsedTime = 0.125f;

	// Reading input here, before update.

	m_pDI->ReadDevices();

	if(m_pCurrState->Input() == false)
		return false;

	// Current state updates
	m_pCurrState->Update( fElapsedTime );
	return true;
}


// Render
//	- render the game
void CGame::Render(void)
{
	// Clear the backbuffer
	m_pD3D->Clear( D3DCOLOR_XRGB( 255, 255, 255 ) ); // White 

	// Begin rendering
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();
	{
		// Current state renders
		m_pCurrState->Render();
	}
	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();

	// Present the backbuffer to the screen
	m_pD3D->Present();

}


void CGame::ChangeState( CGameStates* pState )
{
	// Exit the current state if we are in one.
	if( m_pCurrState != nullptr )
		m_pCurrState->Sleep();

	// Store the new state
	m_pCurrState = pState;

	// Enter the new state (if any)
	if( m_pCurrState != nullptr )
		m_pCurrState->Activate();
}
