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
#include "ProfileMenuState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "CharacterMenuState.h"
#include "BattleState.h"
#include "Npcs.h"
#include "../TinyXML/tinyxml.h"
#include <sstream>
#include "AnimationSystem.h"
#include "Animation.h"
#include "AnimationTimeStamp.h"
#include "Warp.h"
#include "GameOverState.h"
#include "BasicAttack.h"



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
	m_fFireBallTimer = 0.0f;
	m_eCurrPhase = GP_START;
}
// Destructor
CGamePlayState::~CGamePlayState(void)
{
	SetPlayer(nullptr);
}

void CGamePlayState::Activate(void)
{
	switch (m_eCurrPhase)
	{
	case CGamePlayState::GP_NAV:
		break;
	case CGamePlayState::GP_BATTLE:
		m_eCurrPhase = GP_NAV;
		break;
	case CGamePlayState::GP_MENU:
		break;
	case CGamePlayState::GP_START:
		{
			int nTemp = CMainMenuState::GetInstance()->GetBackgroundMusic();
			if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(nTemp))
			{
				CSGD_XAudio2::GetInstance()->MusicStopSong(nTemp);

			}
			LoadWorld("RealSimple.xml");

			m_pES = CSGD_EventSystem::GetInstance();
			m_pRM = new CRenderManager;

			WorldHeight = CGame::GetInstance()->GetScreenHeight();
			WorldWidth = CGame::GetInstance()->GetScreenWidth();

			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TEMP_Player_Walk_Right.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TEMP_Player_Walk_Up.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TEMP_Player_Walk_Down.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TEMP_Player_Walk_Left.xml");

			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/testAnim.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/testAnim2.xml");


			WorldCamX =  int(m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2));
			WorldCamY =  int(m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2));

			m_pES->RegisterClient("INIT_BATTLE", this);
			m_pES->RegisterClient("GAME_OVER", this);
			m_pES->RegisterClient("PLAYER_MENU", this);
			m_pES->RegisterClient("VICTORY", this);
			m_pES->RegisterClient("WARP", this);
			m_pES->RegisterClient("TEMP_SPAWN_FIREBALL", this);

			m_eCurrPhase = GP_NAV;

			CNpcs* pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetPosX(100);
			pTemp->SetPosY(100);
			pTemp->AddWaypoint(100,100);
			pTemp->AddWaypoint(0,100);
			pTemp->AddWaypoint(0,200);
			pTemp->AddWaypoint(0,100);
			pTemp->AddWaypoint(-100,100);
			pTemp->GetAnimInfo()->SetAnimation("TestAnimation2");
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);
			m_mWorldManager[m_sCurrWorld]->AddObject(m_pPlayer, 2);
			pTemp->SetUnits(CreateTempEnemy("Enemy 1", 100.0f, 100.0f, 12, 20, 20));
			pTemp->SetUnits(CreateTempEnemy("Enemy 2", 200.0f, 200.0f, 5, 50, 20));
			pTemp->SetUnits(CreateTempEnemy("Enemy 3", 100.0f, 300.0f, 9, 75, 20));


			CNpcs* pTemp2 = new CNpcs();
			pTemp2->SetActive(true);
			pTemp2->SetHostile(true);
			pTemp2->SetPosX(200);
			pTemp2->SetPosY(100);
			pTemp2->AddWaypoint(200,100);
			pTemp2->AddWaypoint(300,100);
			pTemp2->SetUnits(CreateTempEnemy("ThornBiter 1", 100.0f, 100.0f, 12, 20, 20));
			pTemp2->SetUnits(CreateTempEnemy("ThornBiter 2", 200.0f, 200.0f, 5, 50, 20));
			pTemp2->SetUnits(CreateTempEnemy("ManDrake", 100.0f, 300.0f, 9, 75, 20));
			pTemp2->GetAnimInfo()->SetAnimation("TestAnimation2");
			pTemp2->GetAnimInfo()->SetCurrentFrame(1);
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp2, 2);




			pTemp->Release();
			pTemp = nullptr;
			pTemp2->Release();
			pTemp2 = nullptr;

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
			// Clear the event system
			if( m_pES != nullptr )
			{
				m_pES->Terminate();
				m_pES = nullptr;
			}

			delete m_pRM;
			m_pRM = nullptr;
			SetPlayer(nullptr);
			m_eCurrPhase = GP_START;

			CSGD_EventSystem::GetInstance()->UnregisterClientAll(this);

			for(auto Iter = m_mWorldManager.begin(); Iter != m_mWorldManager.end(); ++Iter)
			{
				delete Iter->second;
			}

			CAnimationSystem::GetInstance()->DeleteInstance();
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
		if( pDI->KeyPressed( DIK_W ) == true || pDI->JoystickDPadPressed(DIR_UP))
			SetCursorSelection(GetCursorSelection() - 1);
		if( pDI->KeyPressed( DIK_S ) == true || pDI->JoystickDPadPressed(DIR_DOWN))
			SetCursorSelection(GetCursorSelection() + 1);

		if(GetCursorSelection() > 2)
			SetCursorSelection(0);
		else if(GetCursorSelection() < 0)
			SetCursorSelection(2);


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
			case 1:			// PLAY
				{
					CProfileMenuState::GetInstance()->SaveGame(m_pPlayer->GetName());
					return true;
				}
				break;

			case 2:			
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
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(m_eCurrPhase == GP_END)
	{
		CGame::GetInstance()->ChangeState(CGameOverState::GetInstance());
		return;
	}
	if(bisPaused == false)
	{
		WorldCamX = int(m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2));
		WorldCamY = int(m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2));

		if(WorldCamX < 0)
			WorldCamX = 0;
		else if(WorldCamX > m_mWorldManager[m_sCurrWorld]->GetWidth() * m_mWorldManager[m_sCurrWorld]->GetTileWidth() - 800)
			WorldCamX = m_mWorldManager[m_sCurrWorld]->GetWidth() * m_mWorldManager[m_sCurrWorld]->GetTileWidth() - 800;

		if(WorldCamY < 0)
			WorldCamY = 0;

		m_fFireBallTimer += fElapsedTime;

		m_mWorldManager[m_sCurrWorld]->Update(fElapsedTime);
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

		CGame::GetInstance()->GetFont2()->Draw(_T("Resume\nSave\nQuit"), 352,244, 1.0f, D3DCOLOR_XRGB(0, 0, 255));
		CGame::GetInstance()->GetFont2()->Draw(_T("-"), 344,244 + (GetCursorSelection() * 28), 1.0f, D3DCOLOR_XRGB(0, 0, 255));
	}
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
		m_eCurrPhase = GP_END;
	else if(pEvent->GetEventID() == "PLAYER_MENU")
	{

	}
	else if(pEvent->GetEventID() == "VICTORY")
	{
		m_eCurrPhase = GP_NAV;
	}
	else if(pEvent->GetEventID() == "WARP")
	{
		CWarp* pWarp = reinterpret_cast<CWarp*>(pEvent->GetSender());
		m_pPlayer->SetPosX((float)pWarp->GetWarpX());
		m_pPlayer->SetPosY((float)pWarp->GetWarpY());
		TransitionWorld(pWarp->GetMapName());
	}
	else if (pEvent->GetEventID() == "TEMP_SPAWN_FIREBALL")
	{
		if (m_fFireBallTimer > 1.0f)
		{
			CEntity* pTempFire = new CEntity();
			pTempFire->SetActive(true);
			//pTemp->SetHostile(true);
			pTempFire->SetPosX(200);
			pTempFire->SetPosY(0);
			pTempFire->SetVelX(200);
			pTempFire->GetAnimInfo()->SetAnimation("TestAnimation");
			m_mWorldManager[m_sCurrWorld]->AddObject(pTempFire, 4);

			pTempFire->Release();
			pTempFire = nullptr;
			m_fFireBallTimer = 0.0f;
		}
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


						ReadIn = pTileData->Attribute("EventType");
						if(ReadIn == "EVENT")
						{
							pTempTile->SetEvent(true);
							pTempTile->SetEventID(pLoad->Attribute("EventID"));
						}
						else if(ReadIn == "BLOCK")
						{
							CObjects* block = new CObjects;
							block->SetPosX(float(tileID % layerWidth * tileWidth));
							block->SetPosY(float(tileID / layerWidth * tileHeight));
							block->SetHeight(tileHeight);
							block->SetWidth(tileWidth);
							Worldtemp->AddObject(block, 2);
							block->Release();
						}
						else if(ReadIn == "NPCS")
						{

						}
						else if(ReadIn == "WARP")
						{
							CWarp* warp = new CWarp;
							warp->SetPosX(float(tileID % layerWidth * tileWidth));
							warp->SetPosY(float(tileID / layerWidth * tileHeight));
							warp->SetHeight(tileHeight);
							warp->SetWidth(tileWidth);
							int nX = 0;
							int nY = 0;

							pLoad->Attribute("WarpX", &nX);
							pLoad->Attribute("WarpY", &nY);

							warp->SetWarpX(nX);
							warp->SetWarpY(nY);

							warp->SetMapName(pTileData->Attribute("EventID"));
							Worldtemp->AddObject(warp, 2);
							warp->Release();
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

CUnits* CGamePlayState::GetPlayerUnit()
{
	return m_pPlayer->GetUnit();
}

void CGamePlayState::TransitionWorld(std::string szNewWorld)
{
	if(m_sCurrWorld == szNewWorld || szNewWorld == "")
		return;


	m_mWorldManager[m_sCurrWorld]->RemoveObject(m_pPlayer);

	m_mWorldManager[szNewWorld]->AddObject(m_pPlayer, 2);
	m_sCurrWorld = szNewWorld;
}

void CGamePlayState::SetPlayer(CPlayer* pPlayer)
{
	if(m_pPlayer != nullptr)
		m_pPlayer->Release();

	m_pPlayer = pPlayer;

	if(m_pPlayer != nullptr)
		m_pPlayer->AddRef();
}

CEnemyUnit* CGamePlayState::CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp)
{
	CEnemyUnit* temp = new CEnemyUnit;
	CAIController* tempAI = new CAIController;
	CBasicAttack* tempAtk = new CBasicAttack;
	tempAI->AddMinigame(tempAtk);
	tempAI->MakeOwner(temp);
	temp->SetAIController(tempAI);
	temp->SetMaxHealth(hp);
	temp->SetMaxAP(mp);
	temp->SetPosX(X);
	temp->SetPosY(Y);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(speed);
	temp->SetTurn(false);
	temp->SetName(input);

	return temp;
}
