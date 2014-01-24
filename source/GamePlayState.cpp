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
#include "Npcs.h"
#include "../TinyXML/tinyxml.h"
#include <sstream>



// GetInstance
CGamePlayState* CGamePlayState::GetInstance( void )
{
	static CGamePlayState s_Instance;

	return &s_Instance;
}



CGamePlayState::CGamePlayState(void)
{
	CBattleState::GetInstance();
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

			pOM->AddObject(m_pPlayer, 4); // Player goes on layer 5

			m_pES->RegisterClient("INIT_BATTLE", this);
			m_pES->RegisterClient("GAME_OVER", this);
			m_pES->RegisterClient("PLAYER_MENU", this);
			m_pES->RegisterClient("VICTORY", this);

			m_eCurrPhase = GP_NAV;

			CNpcs* pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetVelX(0);
			pTemp->SetVelY(0);
			pTemp->SetPosX(100);
			pTemp->SetPosY(100);
			pOM->AddObject(pTemp, 4);
			pTemp->Release();
			pTemp = nullptr;

			LoadWorld("TestingCollide.xml");

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
	case CGamePlayState::GP_END:
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

			CSGD_EventSystem::GetInstance()->UnregisterClientAll(this);

			for(auto Iter = m_mWorldManager.begin(); Iter != m_mWorldManager.end(); ++Iter)
			{
				delete Iter->second;
			}

		}
		break;
	default:
		break;
	}

}

bool CGamePlayState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(pDI->KeyPressed( DIK_ESCAPE ) == true || pDI->JoystickButtonPressed(9) || pDI->JoystickButtonPressed(2))
	{
		bisPaused = !bisPaused;
		return true;
	}
	else if(bisPaused)
	{
		if( pDI->KeyPressed( DIK_UP ) == true || pDI->JoystickDPadPressed(DIR_UP))
			SetCursorSelection(GetCursorSelection() - 1);
		if( pDI->KeyPressed( DIK_DOWN ) == true || pDI->JoystickDPadPressed(DIR_DOWN))
			SetCursorSelection(GetCursorSelection() + 1);

		if(GetCursorSelection() > 1)
			SetCursorSelection(0);
		else if(GetCursorSelection() < 0)
			SetCursorSelection(1);


		if( pDI->KeyPressed( DIK_RETURN ) == true || pDI->JoystickButtonPressed(1))
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


		pOM->Update(fElapsedTime);
		pOM->HandleCollision(4,4);
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
	temp->SetUnit(CreateTempPlayer());
	temp->SetHeight(10);
	temp->setWidth(10);	return temp;
}

void CGamePlayState::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "INIT_BATTLE")
	{
		m_eCurrPhase = GP_BATTLE;
		CBattleState::GetInstance()->SetSender((CObjects*)(pEvent->GetSender()));
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
	else if(pEvent->GetEventID() == "VICTORY")
	{
		m_eCurrPhase = GP_NAV;
	}
}

void CGamePlayState::LoadWorld(string input)
{

	string temp = "Assets/Data/Levels/"; 
	temp += input;

	CWorld* Worldtemp = new CWorld;

	TiXmlDocument doc;
	if(doc.LoadFile(temp.c_str()) == false)
		return;

	TiXmlElement *pRoot = doc.RootElement();
	if(pRoot == nullptr)
		return;

	temp = pRoot->Attribute("Image");
	wostringstream texture;
	texture << "Assets/Graphics/Tilesets/" << temp.c_str();
	int transparency = 0;

	pRoot->Attribute("Transparency", &transparency);
	Worldtemp->SetID(CSGD_TextureManager::GetInstance()->LoadTexture(texture.str().c_str(), transparency));

	int tileWidth = 0;
	int tileHeight = 0;
	int layerWidth = 0;
	int layerHeight = 0;
	int TotalLayers = 0;

	pRoot->Attribute("Layers", &TotalLayers);
	pRoot->Attribute("TileHeight", &tileHeight);
	pRoot->Attribute("TileWidth", &tileWidth);
	pRoot->Attribute("Height", &layerHeight);
	pRoot->Attribute("Width", &layerWidth);

	Worldtemp->SetHeight(layerHeight);
	Worldtemp->SetWidth(layerWidth);
	Worldtemp->SetTileHeight(tileHeight);
	Worldtemp->SetTileWidth(tileWidth);



	TiXmlElement* pLoad = pRoot->FirstChildElement("Layer");
	if(pLoad != nullptr)
	{
		TiXmlElement* pTile;
		TiXmlElement* pTileData;


		string ReadIn = "";
		int TileXID = 0;
		int TileYID = 0;
		CLayer* tempLayer;
		CTile* pTempTile;

		for(int i = 0; i < TotalLayers; i++)
		{
			tempLayer =  new CLayer;
			pTile = pLoad->FirstChildElement("Tile");
			if(pTile != nullptr)
				pTileData = pTile->FirstChildElement("Tile_Data");
			if(pLoad != nullptr)
			{
				for(int tileID = 0; tileID < layerWidth * layerHeight; tileID++)
				{

					if(pTileData != nullptr)
					{


						pTempTile = new CTile;
						pTileData->Attribute("yTileID", &TileYID);
						pTileData->Attribute("xTileID", &TileXID);

						pTempTile->SetTileX(TileXID);
						pTempTile->SetTileY(TileYID);


						ReadIn = pTileData->Attribute("isEvent");
						if(ReadIn == "true")
						{
							pTempTile->SetEvent(true);
							pTempTile->SetEventID(pLoad->Attribute("EventID"));
						}
						ReadIn = pTileData->Attribute("isBlocked");
						if(ReadIn == "true")
						{
							CObjects* block = new CObjects;
							block->SetPosX(tileID % layerWidth * tileWidth);
							block->SetPosY(tileID / layerWidth * tileHeight);
							block->SetHeight(tileHeight);
							block->SetWidth(tileWidth);
							CObjectManager::GetInstance()->AddObject(block, 4);
						}
						ReadIn = pTileData->Attribute("isNPC");
						if(ReadIn == "true")
						{
							//pTempTile->SetEvent(true);
							//pTempTile->SetEventID(pLoad->Attribute("EventID")); TODO;
						}
						tempLayer->AddTile(pTempTile);
						pTile = pTile->NextSiblingElement();
						if(pTile != nullptr)
							pTileData = pTile->FirstChildElement("Tile_Data");
					}
				}

				Worldtemp->AddLayers(tempLayer);
				pLoad = pLoad->NextSiblingElement();
			}
		}
	}

	m_mWorldManager[input] = Worldtemp;
	m_sCurrWorld = input;

}

CPlayerUnit* CGamePlayState::CreateTempPlayer(void)
{
	CPlayerUnit* temp = new CPlayerUnit;
	temp->SetMaxHealth(80);
	temp->SetMaxAP(50);
	temp->SetPosX(600);
	temp->SetPosY(250);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(1);
	temp->SetType(OBJ_PLAYER_UNIT);
	return temp;
}
CUnits* CGamePlayState::GetPlayerUnit()
{
	return m_pPlayer->GetUnit();
}