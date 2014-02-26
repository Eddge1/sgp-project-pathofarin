#include "Game.h"
#include <ctime>
#include "GameStates.h"
#include "MainMenuState.h"
#include "SplashScreen.h"
#include "..\TinyXML\tinyxml.h"
#include "AnimationSystem.h"
#include <string>
#include <ShlObj.h>
#include <sstream>

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
	m_pES			= nullptr;

	m_pFont			= nullptr;

	m_nScreenWidth	= 1;
	m_nScreenHeight	= 1;
	m_bIsWindowed	= true;
	m_bMemory		= false;

	m_pCurrState	= nullptr;

	m_dwCurrTime	= 0;
	m_szSafeFolders  = "";

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
	SetSafePath();

	// Store the SGD Wrapper singletons
	m_pD3D			= CSGD_Direct3D::GetInstance();
	m_pDI			= CSGD_DirectInput::GetInstance();
	m_pTM			= CSGD_TextureManager::GetInstance();
	m_pXA			= CSGD_XAudio2::GetInstance();
	m_pES			= CSGD_EventSystem::GetInstance();
	m_bGamePaused	= false;
	// Store the parameters
	m_nScreenWidth	= nWidth;
	m_nScreenHeight	= nHeight;
	m_bIsWindowed	= bIsWindowed;
	srand((unsigned int) time(0));
	m_hWnd = hWnd;

	// Initialize the wrappers
	m_pD3D->Initialize( hWnd, m_nScreenWidth, m_nScreenHeight, m_bIsWindowed, false );
	m_pDI->Initialize( hWnd, hInstance, DI_KEYBOARD /*| DI_MOUSE*/ | DI_JOYSTICKS );
	m_pTM->Initialize( m_pD3D->GetDirect3DDevice(),	m_pD3D->GetSprite() );

	m_pXA->Initialize();

	m_pFont = new CBitmapFont;
	m_pFont->Initialize();

	if(Load() == false)
		CreateConfig();

	// Start in the Main Menu state
	ChangeState( CSplashScreen::GetInstance() );

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
	m_pFont->Shutdown();
	m_pES->Terminate();

	// Reset the data members to null so they cant use them
	m_pD3D			= nullptr;
	m_pDI			= nullptr;
	m_pTM			= nullptr;
	m_pXA			= nullptr;
	m_pES			= nullptr;

	m_nScreenWidth	= 1;
	m_nScreenHeight	= 1;
	m_bIsWindowed	= true;

	delete m_pFont;
	m_pFont = nullptr;
}

// Update
//	- update the game
bool CGame::Update( void )
{
	if(GetFocus() != m_hWnd)
		m_bGamePaused = true;
	else
		m_bGamePaused = false;

	DWORD dwNow = GetTickCount();
	float fElapsedTime = (dwNow - m_dwCurrTime) / 1000.0f;
	m_dwCurrTime = dwNow;

	// Cap the elapsed time to 1/8th
	if( fElapsedTime > 0.125f )
		fElapsedTime = 0.125f;

	if(!m_bGamePaused)
	{
		// Update the audio

		// Reading input here, before update.

		m_pDI->ReadDevices();

		if(m_pCurrState->Input() == false)
			return false;

		// Current state updates
		m_pCurrState->Update( fElapsedTime );
	}
	m_pXA->Update();
	return true;
}


// Render
//	- render the game
void CGame::Render(void)
{
	// Clear the backbuffer
	m_pD3D->Clear( D3DCOLOR_XRGB( 0, 0, 0 ) ); // Black

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

bool CGame::Load()
{
	TiXmlDocument doc;
	string szTemp = m_szSafeFolders;
	szTemp += "Options.xml";
	if(doc.LoadFile(szTemp.c_str()) == false)
		return false;

	TiXmlElement *pRoot = doc.RootElement();
	if(	pRoot == nullptr )
		return false;

	int nMusicVolume = -1;
	int nSFXVolume = -1;
	m_bIsWindowed = true;
	m_bMemory = false;

	TiXmlElement* pConfig = pRoot->FirstChildElement("Sound_Settings");
	if(pConfig != nullptr)
	{
		pConfig->Attribute("Music", &nMusicVolume);
		pConfig->Attribute("SFX", &nSFXVolume);
		pConfig = pRoot->FirstChildElement("Cursor_Memory");
		if(pConfig != nullptr)
		{
			std::string szTemp = pConfig->Attribute("Enabled");
			if(szTemp == "true")
				m_bMemory = true;
			szTemp = "";
			pConfig = pRoot->FirstChildElement("Fullscreen_Mode");
			if(pConfig != nullptr)
			{
				szTemp = pConfig->Attribute("Enabled");
				if(szTemp == "true")
					m_bIsWindowed = false;
			}
		}
		if(nSFXVolume >= 0 && nSFXVolume <= 100)
			m_pXA->SFXSetMasterVolume(nSFXVolume /100.0f);
		if(nMusicVolume >= 0 && nMusicVolume <= 100)
			m_pXA->MusicSetMasterVolume(nMusicVolume /100.0f);
		if(m_bIsWindowed == false)
			m_pD3D->Resize(m_nScreenHeight, m_nScreenHeight, m_bIsWindowed);
	}
	return true;
}

void CGame::CreateConfig(int nMusic/* = 100*/, int nSFX/* = 100*/, bool bFullscreen/* = false*/, bool bMemory/* = false*/)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "");

	doc.LinkEndChild(pDecl);	
	TiXmlElement* pRoot = new TiXmlElement("Config");
	doc.LinkEndChild(pRoot);

	TiXmlElement* pConfig = new TiXmlElement("Sound_Settings");
	pConfig->SetAttribute("Music", nMusic);
	pConfig->SetAttribute("SFX", nSFX);
	pRoot->LinkEndChild(pConfig);

	pConfig = new TiXmlElement("Cursor_Memory");
	std::string szTemp = "";
	if(bMemory == false)
		szTemp = "false";
	else
		szTemp = "true";

	pConfig->SetAttribute("Enabled", szTemp.c_str());
	pRoot->LinkEndChild(pConfig);

	if(bFullscreen == true)
		szTemp = "false";
	else
		szTemp = "true";

	pConfig = new TiXmlElement("Fullscreen_Mode");
	pConfig->SetAttribute("Enabled",  szTemp.c_str());
	pRoot->LinkEndChild(pConfig);
	string szSaveName = m_szSafeFolders;
	szSaveName += "Options.xml";
	doc.SaveFile(szSaveName.c_str());
}

CBitmapFont* CGame::GetFont(std::string szFont) const
{
	if(szFont == "")
		return nullptr;

	return m_pFont->GetFont(szFont);

}

void CGame::SetSafePath()
{
	HRESULT hr;
	ostringstream oss;
	char path[MAX_PATH];
	WCHAR wPath[MAX_PATH];
	LPWSTR wszPath = NULL;
	size_t   size;

	// Get the path to the app data folder
	hr = SHGetKnownFolderPath( FOLDERID_LocalAppData, 0, 0, &wszPath); 

	// Convert from LPWSTR to char[]
	wcstombs_s(&size,path,MAX_PATH,wszPath,MAX_PATH);

	// Convert char types
	if(hr == S_OK)
		oss << path;
	m_szSafeFolders = oss.str();
	// Add the company and game information
	m_szSafeFolders += "\\DNaS\\Path of Arin\\Config\\";
	for(unsigned int i = 0; i < m_szSafeFolders.length(); i++)
	{
		wPath[i] = m_szSafeFolders.c_str()[i];
		if(i == m_szSafeFolders.length() -1)
			wPath[i+1] = '\0';
	}
	// Create our directory
	SHCreateDirectoryEx(NULL,wPath,0);
}