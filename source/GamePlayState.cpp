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
#include "CreditState.h"
#include "Chest.h"
#include "AITigerlily.h"
#include "AIValrion.h"

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
	m_fGameEndTimer = 0.0f;
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
		if(m_pPlayer != nullptr)
		{
			TransitionWorld(m_pPlayer->GetZone());
			m_mWorldManager[m_sCurrWorld]->AddObject(m_pPlayer, 2);
			WorldCamX =  int(m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2));
			WorldCamY =  int(m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2));

			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Potion"].Item, 2);
		}
		break;
	case CGamePlayState::GP_BATTLE:
		m_eCurrPhase = GP_NAV;
		break;
	case CGamePlayState::GP_MENU:
		break;
	case CGamePlayState::GP_START:
		{
			m_fGameEndTimer = 0.0f;
			m_bGameVictory = false;
			SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_SelectionMenu.png")));
			SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));
			m_mItemManager["Potion"].Item = CreatePotion("Potion");
			m_mItemManager["Hi-Potion"].Item = CreatePotion("Hi-Potion");
			m_mItemManager["Titan-Potion"].Item = CreatePotion("Titan-Potion");
			m_mItemManager["Ether"].Item = CreatePotion("Ether");
			m_mItemManager["Hi-Ether"].Item = CreatePotion("Hi-Ether");
			m_mItemManager["Titan-Ether"].Item = CreatePotion("Titan-Ether");

			int nTemp = CMainMenuState::GetInstance()->GetBackgroundMusic();
			if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(nTemp))
			{
				CSGD_XAudio2::GetInstance()->MusicStopSong(nTemp);

			}
			CNpcs* pTemp = new CNpcs();
			LoadWorld();
			m_sCurrWorld = "Level2.xml";
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
			pTemp->SetUnits(CreateTempEnemy("Thornbiter", 100.0f, 250.0f, 12, 150, 20));
			pTemp->SetUnits(CreateTempEnemy("Thornbiter", 100.0f, 400.0f, 9,  150, 20));
			pTemp->SetUnits(CreateTempEnemy("Tree", 200.0f,		  350.0f, 25, 500, 20, 25));
			pTemp->SetEvent("VALRION_DEFEAT");
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
			pTemp->SetUnits(CreateTempEnemy("Thornbiter", 100.0f, 250.0f, 12, 150, 20));
			pTemp->SetUnits(CreateTempEnemy("Thornbiter", 200.0f, 350.0f, 5,  150, 20));
			pTemp->SetUnits(CreateTempEnemy("Thornbiter", 100.0f, 400.0f, 9,  150, 20));
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
			pTemp->SetUnits(CreateTempEnemy("Thornbiter", 100.0f, 250.0f, 12, 150, 20));
			pTemp->SetUnits(CreateTempEnemy("Thornbiter", 200.0f, 350.0f, 5,  150, 20));
			pTemp->SetUnits(CreateTempEnemy("Thornbiter", 100.0f, 400.0f, 9,  150, 20));
			pTemp->Release();

			m_sCurrWorld = "testing.xml";

			pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetPosX(200);
			pTemp->SetPosY(420);
			pTemp->AddWaypoint(200,420);
			pTemp->AddWaypoint(200,260);
			pTemp->SetName("Pathetic_Orc");
			pTemp->GetAnimInfo()->SetAnimation("Pathetic_Orc_Idle");
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);
			pTemp->SetUnits(CreateTempEnemy("Orc_Leader", 100.0f, 250.0f, 12, 150, 20));
			pTemp->SetUnits(CreateTempEnemy("Pathetic_Orc", 200.0f, 350.0f, 5, 150, 20));
			pTemp->SetUnits(CreateTempEnemy("Orc", 100.0f, 400.0f, 9, 150, 20));
			pTemp->Release();

			pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(true);
			pTemp->SetPosX(557);
			pTemp->SetPosY(535);
			pTemp->AddWaypoint(557,535);
			pTemp->AddWaypoint(203,535);
			pTemp->SetUnits(CreateTempEnemy("Snail", 100.0f, 250.0f, 12, 150, 20));
			pTemp->SetUnits(CreateTempEnemy("Snail", 200.0f, 350.0f, 5,  150, 20));
			pTemp->SetUnits(CreateTempEnemy("Snail", 100.0f, 400.0f, 9,  150, 20));
			pTemp->GetAnimInfo()->SetAnimation("Snail_Idle");
			pTemp->GetAnimInfo()->SetCurrentFrame(1);
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);

			pTemp->Release();
			pTemp = nullptr;


			pTemp = new CNpcs();
			pTemp->SetActive(true);
			pTemp->SetHostile(false);
			pTemp->SetPosX(557);
			pTemp->SetPosY(300);
			pTemp->RegEvent("VALRION_DEFEAT");
			pTemp->AddConversation("Hello Mortal! There is an Evil Tree \nthat is terrorizing our Village! Please help us!");
			pTemp->SetName("OldMan");
			pTemp->GetAnimInfo()->SetAnimation("NPC_Male_Idle");
			pTemp->GetAnimInfo()->SetCurrentFrame(0);
			m_mWorldManager[m_sCurrWorld]->AddObject(pTemp, 2);

			pTemp->Release();
			pTemp = nullptr;

			CChest* pChest = new CChest();
			pChest->SetPosX(609);
			pChest->SetPosY(161);
			pChest->AddConsumableItem(m_mItemManager["Ether"].Item, 3);
			pChest->RegEvent("TEST_ITEM");
			pChest->GetAnimInfo()->SetAnimation("Chest_Closed");
			m_mWorldManager[m_sCurrWorld]->AddObject(pChest, 2);
			pChest->Release();
			pChest = nullptr;

			m_pES = CSGD_EventSystem::GetInstance();
			m_pRM = new CRenderManager;

			WorldHeight = CGame::GetInstance()->GetScreenHeight();
			WorldWidth = CGame::GetInstance()->GetScreenWidth();

			CAnimationSystem::GetInstance()->LoadAnimations();
			/*CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/Player_Warrior_Battle.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TwistedTree_Overworld.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/TwistedTree_Battle.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/Orc_Overworld.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/Orc_Battle.xml");

			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/NPC_Male.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/testAnim.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/testAnim2.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/MageIdle.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/Plantdude.xml");
			CAnimationSystem::GetInstance()->LoadAnimations("assets/Data/Animations/World_Chest.xml");*/


			m_pES->RegisterClient("INIT_BATTLE", this);
			m_pES->RegisterClient("GAME_OVER", this);
			m_pES->RegisterClient("PLAYER_MENU", this);
			m_pES->RegisterClient("VICTORY", this);
			m_pES->RegisterClient("WARP", this);
			m_pES->RegisterClient("TEMP_SPAWN_FIREBALL", this);
			m_pES->RegisterClient("LEVEL_UP", this);
			m_pES->RegisterClient("VALRION_DEFEAT", this);
			m_pES->RegisterClient("TEST_ITEM", this);
			m_pES->RegisterClient("GAME_WON", this);

			

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
		break;
	case CGamePlayState::GP_END:
		{
			if(m_pES != nullptr)
			{
				m_pES->UnregisterClientAll(this);
				m_pES = nullptr;

				for(unsigned int i = 0; i < m_vShowOnScreen.size();)
				{
					m_vShowOnScreen[i]->pOwner->Release();
					m_vShowOnScreen[i]->pOwner = nullptr;
					delete m_vShowOnScreen[i];
					m_vShowOnScreen.erase(m_vShowOnScreen.begin() + i);
				}
				m_vShowOnScreen.clear();

				delete m_pRM;
				m_pRM = nullptr;
				SetPlayer(nullptr);
				m_eCurrPhase = GP_START;

				for(auto Iter = m_mWorldManager.begin(); Iter != m_mWorldManager.end(); ++Iter)
				{
					delete Iter->second;
				}
				m_mWorldManager.clear();
				CAnimationSystem::GetInstance()->DeleteInstance();
				for(auto Iter = m_mItemManager.begin(); Iter != m_mItemManager.end(); ++Iter)
				{
					delete Iter->second.Item;
					Iter->second.Item = nullptr;
				}
				m_mItemManager.clear();
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
					m_eCurrPhase = GP_END;
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
		m_fGameEndTimer -= fElapsedTime;
		if(m_bGameVictory && m_fGameEndTimer < 0.0f)
		{
			CGame::GetInstance()->ChangeState(CCreditState::GetInstance());
			return;
		}
	}
	if(bisPaused == false)
	{
		for(unsigned int i = 0; i < m_vShowOnScreen.size();)
		{
			m_vShowOnScreen[i]->m_fTimer -= fElapsedTime;
			if(m_vShowOnScreen[i]->m_fTimer < 0)
			{
				m_vShowOnScreen[i]->pOwner->Release();
				m_vShowOnScreen[i]->pOwner = nullptr;
				delete m_vShowOnScreen[i];
				m_vShowOnScreen.erase(m_vShowOnScreen.begin() + i);
			}
			else
				i++;
		}
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
	wostringstream woss;

	for(unsigned int i = 0; i < m_vShowOnScreen.size();i++)
	{
		woss << m_vShowOnScreen[i]->szText.str();

		CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), m_vShowOnScreen[i]->pOwner->GetPosX() - WorldCamX - ( m_vShowOnScreen[i]->szText.str().length() * 8 * 0.5f), m_vShowOnScreen[i]->pOwner->GetPosY() - WorldCamY, 0.8f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str(_T(""));
	}

	if(bisPaused)
	{
		RECT rTemp = {336, 236, 464,364};
		pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(190,0,0,0));
		CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(), 272, 172);
		CGame::GetInstance()->GetFont("Arial")->Draw(_T("Resume\nSave\nQuit"), 368,258, 0.75f, D3DCOLOR_XRGB(255,255, 255));
		rTemp.left = 0;
		rTemp.top = 0;
		rTemp.right = 16;
		rTemp.bottom = 32;
		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 360, 262 + (GetCursorSelection() * 21),1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI /2, D3DCOLOR_XRGB(255,255,255));
	}
	woss.str(_T(""));

	woss << m_pPlayer->GetPosX() << "\n" << m_pPlayer->GetPosY();
	CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 5, 5, 0.8f, D3DCOLOR_XRGB(255, 255, 255));
}

void CGamePlayState::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "INIT_BATTLE" && m_eCurrPhase != GP_END)
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
		m_pPlayer->SetLastPositionX((float)pWarp->GetWarpX());
		m_pPlayer->SetLastPositionY((float)pWarp->GetWarpY());

		m_pPlayer->SetPosX((float)pWarp->GetWarpX());
		m_pPlayer->SetPosY((float)pWarp->GetWarpY());
		TransitionWorld(pWarp->GetMapName());
	}
	else if (pEvent->GetEventID() == "TEMP_SPAWN_FIREBALL")
	{

	}
	else if(pEvent->GetEventID() == "VALRION_DEFEAT")
	{
		//m_eCurrPhase = GP_END;
		m_bGameVictory = true;
	}
	else if(pEvent->GetEventID() == "TEST_ITEM")
	{
		map<string,InventoryItems>* mTemp = reinterpret_cast<map<string,InventoryItems>*>(pEvent->GetParam());
		if(mTemp != nullptr)
		{
			wostringstream woss;
			for(auto i = mTemp->begin(); i != mTemp->end(); i++)
			{
				if(i->second.Item != nullptr)
				{
					if(i->second.Item->GetItemType() == IT_CONSUMABLE)
					{
						CConsumable* pTemp = reinterpret_cast<CConsumable*>(i->second.Item);
						if(pTemp != nullptr)
						{
							woss << "Obtained " << pTemp->GetName().c_str() << " x" << i->second.Owned << "\n";
							m_pPlayer->GetUnit()->AddConsumableItem(pTemp, i->second.Owned);
						}
					}
				}
			}
			AddFloatingText(m_pPlayer, D3DCOLOR_XRGB(0,0,0), woss);
		}
	}
	else if(pEvent->GetEventID() == "GAME_WON")
	{
		m_eCurrPhase = GP_END;
		m_bGameVictory = true;
		m_fGameEndTimer = 4.0f;
	}

	
}

void CGamePlayState::LoadWorld(void)
{
	WIN32_FIND_DATA fileSearch;
	HANDLE hFile;
	WCHAR cDirectory[] = L"assets/Data/Levels/*.xml";
	hFile = FindFirstFile(cDirectory,&fileSearch);

	do
	{
		std::string szInput;
		char cFile[128] = "assets/Data/Levels/";
		for(int i = 0; i < 128; i++)
		{
			cFile[i + 19] = char(fileSearch.cFileName[i]);
			if(fileSearch.cFileName[i] == '\0')
				break;
			szInput += char(fileSearch.cFileName[i]);
		}
		std::string temp;

		CWorld* Worldtemp = new CWorld;
		TiXmlDocument doc;
		if(doc.LoadFile(cFile) == false)
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

		m_mWorldManager[szInput] = Worldtemp;
		m_sCurrWorld = szInput;

	}while(FindNextFile(hFile, &fileSearch));
}

CUnits* CGamePlayState::GetPlayerUnit()
{
	return m_pPlayer->GetUnit();
}

void CGamePlayState::TransitionWorld(std::string szNewWorld)
{
	if(m_sCurrWorld == szNewWorld + ".xml" || szNewWorld == "")
		return;
	m_pPlayer->SetZone(szNewWorld);
	m_mWorldManager[m_sCurrWorld]->RemoveObject(m_pPlayer);
	m_mWorldManager[m_sCurrWorld]->ActivateNPCs();
	m_mWorldManager[m_sCurrWorld]->ClearNPCList();

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

CEnemyUnit* CGamePlayState::CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp, int attack)
{
	CEnemyUnit* temp = new CEnemyUnit;
	CAIController* tempAI = new CAIController;
	CBasicAttack* tempAtk = new CBasicAttack;
	CAnimationTimeStamp* pTemp;
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Thornbiter_Idle");
	pTemp->SetCurrentFrame(0);
	temp->SetType(OBJ_ENEMY_UNIT);
	if(input == "ManDrake")
	{
		delete tempAI;
		CAIBasicHealer* Temp = new CAIBasicHealer;
		tempAI = reinterpret_cast<CAIController*>(Temp);
		Temp = nullptr;
		temp->SetType(OBJ_LEADER);
	}
	else if(input == "Orc Zerker")
	{
		delete tempAI;
		CAIBrute* Temp = new CAIBrute;
		tempAI = reinterpret_cast<CAIController*>(Temp);
		Temp = nullptr;
		temp->SetType(OBJ_LEADER);


	}
	else if(input == "Orc_Leader")
	{
		delete tempAI;
		CAIOrcLeader* OrcTemp = new CAIOrcLeader;
		tempAI = reinterpret_cast<CAIController*>(OrcTemp);
		OrcTemp = nullptr;
		temp->SetType(OBJ_LEADER);
		pTemp->SetAnimation("Orc_Leader_Battle_Idle");
	}
	else if (input == "Tree")
	{
		delete tempAI;
		//CAIOrcLeader* OrcTemp = new CAIOrcLeader;
		//CAITigerlily* TigerTemp = new CAITigerlily;
		CAIValrion* Inferno = new CAIValrion;
		tempAI = reinterpret_cast<CAIController*>(Inferno);
		Inferno = nullptr;
		temp->SetType(OBJ_LEADER);
		pTemp->SetAnimation("Tree_Battle_Idle");
	}
	else if (input == "Orc")
	{
		pTemp->SetAnimation("Orc_Battle_Idle");
	}
	else if (input == "Pathetic_Orc")
	{
		pTemp->SetAnimation("Pathetic_Orc_Battle_Idle");
	}
	else if (input == "Snail")
	{
		pTemp->SetAnimation("Snail_Battle_Idle");
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
	temp->SetAttack(attack);
	temp->SetSpeed(speed);
	temp->SetTurn(false);
	temp->SetName(input);
	temp->GiveExperience(90);
	temp->AddConsumableItem(m_mItemManager["Potion"].Item,1,0.75f);
	temp->AddConsumableItem(m_mItemManager["Hi-Potion"].Item,1,0.75f);

	return temp;
}

CWorld* CGamePlayState::GetWorld(string szName) 
{
	return m_mWorldManager[szName];
}

void CGamePlayState::AddFloatingText(CObjects* pOwner, DWORD dColor, wostringstream &szText)
{
	NPCDialogue* ftTemp = new NPCDialogue;
	for(unsigned int i = 0; i < m_vShowOnScreen.size(); i++)
	{
		if(m_vShowOnScreen[i]->szText.str() == szText.str())
		{
			delete ftTemp;
			return;
		}
	}
	ftTemp->pOwner = pOwner;
	if(pOwner != nullptr)
		pOwner->AddRef();
	ftTemp->Color = dColor;
	ftTemp->szText << szText.str();
	ftTemp->m_fTimer = (szText.str().length() / 10.0f) + 1.0f;
	m_vShowOnScreen.push_back(ftTemp);
}

CConsumable* CGamePlayState::CreatePotion(string input)
{
	CConsumable* temp = nullptr;

	if(input == "Potion")
	{
		temp = new CConsumable;
		temp->SetName(input);
		temp->SetDes("Bottle with a liquid substance.");
		temp->SetType("HP");
		temp->SetAmount(200);
		return temp;
	}
	else if(input == "Hi-Potion")
	{
		temp = new CConsumable;
		temp->SetName(input);
		temp->SetDes("Bottle with a liquid substance.");
		temp->SetType("HP");
		temp->SetAmount(500);
		return temp;
	}
	else if(input == "Titan-Potion")
	{
		temp = new CConsumable;
		temp->SetName(input);
		temp->SetDes("Bottle with a liquid substance.");
		temp->SetType("HP");
		temp->SetAmount(1000);
		return temp;
	}
	else if(input == "Ether")
	{
		temp = new CConsumable;
		temp->SetName(input);
		temp->SetDes("Bottle with a magical liquid substance.");
		temp->SetType("MP");
		temp->SetAmount(50);
		return temp;
	}
	else if(input == "Hi-Ether")
	{
		temp = new CConsumable;
		temp->SetName(input);
		temp->SetDes("Bottle with a magical liquid substance.");
		temp->SetType("MP");
		temp->SetAmount(100);
		return temp;
	}
	else if(input == "Hi-Ether")
	{
		temp = new CConsumable;
		temp->SetName(input);
		temp->SetDes("Bottle with a magical liquid substance.");
		temp->SetType("MP");
		temp->SetAmount(300);
		return temp;
	}
	else
		return temp;

}

