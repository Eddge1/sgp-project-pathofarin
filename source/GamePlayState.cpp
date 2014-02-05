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
#include "AIOrcLeader.h"
#include "AIBasicHealer.h"
#include "AIBrute.h"



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

	SetBackgroundMusic(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(-1);
	SetSFXID(-1);
}
// Destructor
CGamePlayState::~CGamePlayState(void)
{
	m_eCurrPhase = GP_END;
	Sleep();
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
			SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_SelectionMenu.png")));
			SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));

			int nTemp = CMainMenuState::GetInstance()->GetBackgroundMusic();
			if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(nTemp))
			{
				CSGD_XAudio2::GetInstance()->MusicStopSong(nTemp);

			}
			CNpcs* pTemp = new CNpcs();

			LoadWorld("Level2.xml");

			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetPosX(1778);
			pTemp->SetPosY(162);
			pTemp->AddWaypoint(1778,162);
			pTemp->AddWaypoint(1778,273);
			pTemp->AddWaypoint(1581,273);
			pTemp->AddWaypoint(1581,162);
			pTemp->GetAnimInfo()->SetAnimation("TestAnimation2");
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 1", 100.0f, 100.0f, 12, 20, 20));
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 2", 200.0f, 200.0f, 5, 50, 20));
			pTemp->SetUnits(CreateTempEnemy("Mandrake", 100.0f, 300.0f, 9, 75, 20));
			pTemp->Release();

			pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetPosX(355);
			pTemp->SetPosY(410);
			pTemp->AddWaypoint(355,410);
			pTemp->AddWaypoint(355,555);
			pTemp->GetAnimInfo()->SetAnimation("TestAnimation2");
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 1", 100.0f, 100.0f, 12, 20, 20));
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 2", 200.0f, 200.0f, 5, 50, 20));
			pTemp->SetUnits(CreateTempEnemy("Mandrake", 100.0f, 300.0f, 9, 75, 20));
			pTemp->Release();

			pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetPosX(1376);
			pTemp->SetPosY(468);
			pTemp->AddWaypoint(1376,468);
			pTemp->AddWaypoint(975,405);
			pTemp->AddWaypoint(1162,206);
			pTemp->AddWaypoint(1358,139);
			pTemp->AddWaypoint(1162,206);
			pTemp->AddWaypoint(975,405);
			pTemp->GetAnimInfo()->SetAnimation("TestAnimation2");
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 1", 100.0f, 100.0f, 12, 20, 20));
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 2", 200.0f, 200.0f, 5, 50, 20));
			pTemp->SetUnits(CreateTempEnemy("Mandrake", 100.0f, 300.0f, 9, 75, 20));
			pTemp->Release();



			LoadWorld("testing.xml");
			m_mWorldManager[m_sCurrWorld]->AddObject(m_pPlayer, 2);

			pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetPosX(200);
			pTemp->SetPosY(420);
			pTemp->AddWaypoint(200,420);
			pTemp->AddWaypoint(200,260);
			pTemp->GetAnimInfo()->SetAnimation("Orc_Walk_Down");
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 1", 100.0f, 100.0f, 12, 20, 20));
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 2", 200.0f, 200.0f, 5, 50, 20));
			pTemp->SetUnits(CreateTempEnemy("Mandrake", 100.0f, 300.0f, 9, 75, 20));
			pTemp->Release();

			pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetPosX(557);
			pTemp->SetPosY(535);
			pTemp->AddWaypoint(557,535);
			pTemp->AddWaypoint(203,535);
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 1", 100.0f, 100.0f, 12, 20, 20));
			pTemp->SetUnits(CreateTempEnemy("ThornBiter 2", 200.0f, 200.0f, 5, 50, 20));
			pTemp->SetUnits(CreateTempEnemy("ManDrake", 100.0f, 300.0f, 9, 75, 20));
			pTemp->GetAnimInfo()->SetAnimation("TestAnimation2");
			pTemp->GetAnimInfo()->SetCurrentFrame(1);
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);

			pTemp->Release();
			pTemp = nullptr;

			TransitionWorld(m_pPlayer->GetZone());

			m_pES = CSGD_EventSystem::GetInstance();
			m_pRM = new CRenderManager;

			WorldHeight = CGame::GetInstance()->GetScreenHeight();
			WorldWidth = CGame::GetInstance()->GetScreenWidth();

			/*CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TEMP_Player_Walk_Right.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TEMP_Player_Walk_Up.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TEMP_Player_Walk_Down.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TEMP_Player_Walk_Left.xml");*/
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/Player_Overworld_Warrior.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TwistedTree_Overworld.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/Orc_Overworld.xml");

			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/testAnim.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/testAnim2.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/MageIdle.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/Plantdude.xml");


			WorldCamX =  int(m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2));
			WorldCamY =  int(m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2));

			m_pES->RegisterClient("INIT_BATTLE", this);
			m_pES->RegisterClient("GAME_OVER", this);
			m_pES->RegisterClient("PLAYER_MENU", this);
			m_pES->RegisterClient("VICTORY", this);
			m_pES->RegisterClient("WARP", this);
			m_pES->RegisterClient("TEMP_SPAWN_FIREBALL", this);
			m_pES->RegisterClient("LEVEL_UP", this);

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
	case CGamePlayState::GP_END:
		{
			if(m_pES != nullptr)
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

				for(auto Iter = m_mWorldManager.begin(); Iter != m_mWorldManager.end(); ++Iter)
				{
					delete Iter->second;
				}
				CAnimationSystem::GetInstance()->DeleteInstance();
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
		else if(WorldCamY > m_mWorldManager[m_sCurrWorld]->GetHeight() * m_mWorldManager[m_sCurrWorld]->GetTileHeight() - 600)
			WorldCamY = m_mWorldManager[m_sCurrWorld]->GetHeight() * m_mWorldManager[m_sCurrWorld]->GetTileHeight() - 600;

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
		pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(190,0,0,0));
		CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(), 272, 172);
		CGame::GetInstance()->GetFont2()->Draw(_T("Resume\nSave\nQuit"), 368,258, 0.75f, D3DCOLOR_XRGB(255,255, 255));
		rTemp.left = 0;
		rTemp.top = 0;
		rTemp.right = 16;
		rTemp.bottom = 32;
		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 360, 262 + (GetCursorSelection() * 21),1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI /2, D3DCOLOR_XRGB(255,255,255));
	}
	wostringstream woss;
	woss << m_pPlayer->GetPosX() << "\n" << m_pPlayer->GetPosY();
	CGame::GetInstance()->GetFont()->Draw(woss.str().c_str(), 5, 5, 0.8f, D3DCOLOR_XRGB(255, 255, 255));
}

void CGamePlayState::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "INIT_BATTLE")
	{
		m_eCurrPhase = GP_BATTLE;
		CBattleState::GetInstance()->SetSender((CObjects*)(pEvent->GetSender()));
		CGame::GetInstance()->ChangeState(CBattleState::GetInstance());
		m_eCurrPhase = GP_NAV;
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
		m_pPlayer->SetLastPositionX((float)pWarp->GetWarpX());
		m_pPlayer->SetLastPositionY((float)pWarp->GetWarpY());

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

		int nLayerWidth = 0;
		int nLayerHeight = 0;
		int nLayerXOffset = 0;
		int nLayerYOffset = 0;

		for(int i = 0; i < TotalLayers; i++)
		{
			tempLayer =  new CLayer;

			pLoad->Attribute("Width", &nLayerWidth);
			pLoad->Attribute("Height", &nLayerHeight);
			pLoad->Attribute("Xoffset", &nLayerXOffset);
			pLoad->Attribute("Yoffset", &nLayerYOffset);

			tempLayer->SetOffsetX(nLayerXOffset);
			tempLayer->SetOffsetY(nLayerYOffset);
			tempLayer->SetSizeX(nLayerWidth);
			tempLayer->SetSizeY(nLayerHeight);

			pTile = pLoad->FirstChildElement("Tile");
			if(pTile != nullptr)
				pTileData = pTile->FirstChildElement("Tile_Data");
			if(pLoad != nullptr)
			{
				for(int tileID = 0; tileID < nLayerWidth * nLayerHeight; tileID++)
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

							pTileData->Attribute("WarpX", &nX);
							pTileData->Attribute("WarpY", &nY);

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
		pLoad = pRoot->FirstChildElement("Block_Data");
		int nObjects = 0;
		pLoad->Attribute("Total",&nObjects);
		TiXmlElement* pBlockData = pLoad->FirstChildElement("Block");
		if(pBlockData != nullptr)
		{
			for(int i = 0; i < nObjects; i++)
			{
				if(pBlockData != nullptr)
				{
					CObjects* block = new CObjects;
					int nPosX = 0;
					int nPosY = 0;
					int nWidth = 0;
					int nHeight = 0;
					pBlockData->Attribute("PosX", &nPosX);
					pBlockData->Attribute("PosY", &nPosY);
					pBlockData->Attribute("Width",&nWidth);
					pBlockData->Attribute("Height",&nHeight);

					block->SetPosX(float(nPosX));
					block->SetPosY(float(nPosY));
					block->SetHeight(nHeight);
					block->SetWidth(nWidth);
					Worldtemp->AddObject(block, 2);
					block->Release();
					pBlockData = pBlockData->NextSiblingElement();
				}
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
	m_pPlayer->SetZone(szNewWorld);
	m_mWorldManager[m_sCurrWorld]->RemoveObject(m_pPlayer);

	m_mWorldManager[szNewWorld + ".xml"]->AddObject(m_pPlayer, 2);
	m_sCurrWorld = szNewWorld + ".xml";
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
	CAnimationTimeStamp* pTemp;
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Plant_dude_Battle");
	pTemp->SetCurrentFrame(0);
	temp->SetType(OBJ_ENEMY_UNIT);
	if(input == "ManDrake")
	{
		int debug = 2;
		if(debug == 0)
		{
			delete tempAI;
			CAIOrcLeader* OrcTemp = new CAIOrcLeader;
			tempAI = reinterpret_cast<CAIController*>(OrcTemp);
			OrcTemp = nullptr;
			temp->SetType(OBJ_LEADER);
		}
		else if(debug == 1)
		{
			delete tempAI;
			CAIBasicHealer* Temp = new CAIBasicHealer;
			tempAI = reinterpret_cast<CAIController*>(Temp);
			Temp = nullptr;
			temp->SetType(OBJ_LEADER);
		}
		else if(debug == 2)
		{
			delete tempAI;
			CAIBrute* Temp = new CAIBrute;
			tempAI = reinterpret_cast<CAIController*>(Temp);
			Temp = nullptr;
			temp->SetType(OBJ_LEADER);
		}

	}
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
	temp->GiveExperience(90);

	return temp;
}
