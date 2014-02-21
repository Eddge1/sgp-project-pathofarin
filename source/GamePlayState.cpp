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
#include "EquipmentState.h"
#include "Game.h"
#include "MainMenuState.h"
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
#include "EnemyUnit.h"
#include "Augment.h"
#include "TutorialBattle.h"

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
	m_bSaveGameStatus = false;
	m_bSaveSuccess = false;

	m_nCursor = 0;
	m_nSaveSelection = 0;
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
	case CGamePlayState::GP_INIT:
		if(m_pPlayer->GetUnit()->GetClass() == UC_NONE)
		{
			m_eCurrPhase = GP_NAV;
			int nTemp = CMainMenuState::GetInstance()->GetBackgroundMusic();
			if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(nTemp))
			{
				CMainMenuState::GetInstance()->SetLeftMenuState(true);
				CSGD_XAudio2::GetInstance()->MusicStopSong(nTemp);
			}
			CGame::GetInstance()->ChangeState(CTutorialBattle::GetInstance());
			return;
		}
	case CGamePlayState::GP_NAV:
		if(m_pPlayer != nullptr)
		{
			TransitionWorld(m_pPlayer->GetZone());
			m_mWorldManager[m_sCurrWorld]->AddObject(m_pPlayer, 2);
			WorldCamX =  int(m_pPlayer->GetPosX() - (CGame::GetInstance()->GetScreenWidth() / 2));
			WorldCamY =  int(m_pPlayer->GetPosY() - (CGame::GetInstance()->GetScreenHeight() / 2));

			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["HP Augment"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["AP Augment"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Atk Augment"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Speed Augment"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Sword of Suffering"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Staff of Lucidity"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Bow of the Great Hunt"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Armor of the Ghost Wolf"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Robes of the Ancient One"].Item, 1);
			m_pPlayer->GetUnit()->AddConsumableItem(m_mItemManager["Vestments of the Savage tribes"].Item, 1);

			int nTemp = CMainMenuState::GetInstance()->GetBackgroundMusic();
			if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(nTemp))
			{
				CMainMenuState::GetInstance()->SetLeftMenuState(true);
				CSGD_XAudio2::GetInstance()->MusicStopSong(nTemp);
			}
		}
		break;
	case CGamePlayState::GP_MENU:
	case CGamePlayState::GP_BATTLE:
		if(m_mWorldManager[m_sCurrWorld]->GetMusicID() != -1)
			CSGD_XAudio2::GetInstance()->MusicPlaySong(m_mWorldManager[m_sCurrWorld]->GetMusicID(), true);
		m_eCurrPhase = GP_NAV;
		break;
	case CGamePlayState::GP_START:
		{
			m_fGameEndTimer = 0.0f;
			m_bGameVictory = false;
			SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_SelectionMenu.png")));
			SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));
			// setting up the items

			m_mItemManager["HP Augment"].Item = CreateAugment("HP", 25.0f);
			m_mItemManager["AP Augment"].Item = CreateAugment("AP", 15.0f);
			m_mItemManager["Atk Augment"].Item = CreateAugment("ATTK", 10.0f);
			m_mItemManager["Speed Augment"].Item = CreateAugment("SPEED", 10.0f);
			m_mItemManager["Sword of Suffering"].Item = CreateWeapon("Sword of Suffering", 10);
			m_mItemManager["Staff of Lucidity"].Item = CreateWeapon("Staff of Lucidity", 8);
			m_mItemManager["Bow of the Great Hunt"].Item = CreateWeapon("Bow of the Great Hunt", 12);
			m_mItemManager["Armor of the Ghost Wolf"].Item = CreateArmor("Armor of the Ghost Wolf", 50.0f, 5.0f, 1.0f);
			m_mItemManager["Robes of the Ancient One"].Item = CreateArmor("Robes of the Ancient One", 20.0f, 10.0f, 5.0f);
			m_mItemManager["Vestments of the Savage tribes"].Item = CreateArmor("Vestments of the Savage tribes", 30.0f, 8.0f, 8.0f);

			m_mItemManager["Potion"].Item = CreatePotion("Potion");
			m_mItemManager["Hi-Potion"].Item = CreatePotion("Hi-Potion");
			m_mItemManager["Titan-Potion"].Item = CreatePotion("Titan-Potion");
			m_mItemManager["Ether"].Item = CreatePotion("Ether");
			m_mItemManager["Hi-Ether"].Item = CreatePotion("Hi-Ether");
			m_mItemManager["Titan-Ether"].Item = CreatePotion("Titan-Ether");

			LoadWorld("Testing.xml");


			m_pES = CSGD_EventSystem::GetInstance();
			m_pRM = new CRenderManager;

			WorldHeight = CGame::GetInstance()->GetScreenHeight();
			WorldWidth = CGame::GetInstance()->GetScreenWidth();

			m_pES->RegisterClient("INIT_BATTLE", this);
			m_pES->RegisterClient("GAME_OVER", this);
			m_pES->RegisterClient("PLAYER_MENU", this);
			m_pES->RegisterClient("VICTORY", this);
			m_pES->RegisterClient("WARP", this);
			m_pES->RegisterClient("TEMP_SPAWN_FIREBALL", this);
			m_pES->RegisterClient("LEVEL_UP", this);
			m_pES->RegisterClient("VALRION_DEFEAT", this);
			m_pES->RegisterClient("GIVE_ITEM", this);
			m_pES->RegisterClient("GAME_WON", this);



			m_eCurrPhase = GP_INIT;
		}
		break;
	case CGamePlayState::GP_END:
		break;
	default:
		break;
	}
	m_bDialogue = false;

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
			}

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

			for(auto Iter = m_mItemManager.begin(); Iter != m_mItemManager.end(); ++Iter)
			{
				delete Iter->second.Item;
				Iter->second.Item = nullptr;
			}

			m_mItemManager.clear();
		}

		break;
	case GP_INIT:
		{
		}
		break;

	default:
		break;
	}

}

bool CGamePlayState::Input(void)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(pDI->KeyPressed( DIK_ESCAPE ) == true || pDI->JoystickButtonPressed(9) || pDI->JoystickButtonPressed(6))
	{
		if(m_bSaveGameStatus && !m_bSaveSuccess)
			m_bSaveGameStatus = false;
		else if(m_bSaveSuccess)
		{
			m_bSaveGameStatus = false;
			m_bSaveSuccess = false;
		}
		else
			bisPaused = !bisPaused;
		return true;

	}
	if(!bisPaused)
	{
		if(m_bDialogue)
		{
			if(pDI->GetInstance()->KeyPressed(DIK_RETURN)|| pDI->JoystickButtonPressed(1))
			{
				m_pPlayer->SetInteraction(false);
				m_bDialogue = false;
				m_vShowOnScreen[0]->pOwner->Release();
				m_vShowOnScreen[0]->pOwner = nullptr;
				delete m_vShowOnScreen[0];
				m_vShowOnScreen.clear();
			}
		}
	}
	else if(bisPaused && !m_bSaveGameStatus)
	{
		if( pDI->KeyPressed( DIK_W ) == true || pDI->JoystickDPadPressed(DIR_UP))
			SetCursorSelection(GetCursorSelection() - 1);
		if( pDI->KeyPressed( DIK_S ) == true || pDI->JoystickDPadPressed(DIR_DOWN))
			SetCursorSelection(GetCursorSelection() + 1);

		if(GetCursorSelection() > 3)
			SetCursorSelection(0);
		else if(GetCursorSelection() < 0)
			SetCursorSelection(3);


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
					m_eCurrPhase = GP_MENU;
					CGame::GetInstance()->ChangeState(CEquipmentState::GetInstance());
					return true;
				}
				break;
			case 2:			// PLAY
				{
					m_bSaveGameStatus = true;
					return true;
				}
				break;

			case 3:			
				{
					bisPaused = !bisPaused;
					m_eCurrPhase = GP_END;
					if(m_mWorldManager[m_sCurrWorld]->GetMusicID() != -1 && CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(m_mWorldManager[m_sCurrWorld]->GetMusicID()))
						CSGD_XAudio2::GetInstance()->MusicStopSong(m_mWorldManager[m_sCurrWorld]->GetMusicID());
					CGame::GetInstance()->ChangeState( CMainMenuState::GetInstance() ); // Will return you to the main menu
					SetCursorSelection(0);
					return true;
				}
				break;
			}
		}
	}
	else if(m_bSaveGameStatus && !m_bSaveSuccess)
	{
		if( pDI->KeyPressed( DIK_W ) == true || pDI->JoystickDPadPressed(DIR_UP))
			m_nSaveSelection -= 1;
		if( pDI->KeyPressed( DIK_S ) == true || pDI->JoystickDPadPressed(DIR_DOWN))
			m_nSaveSelection += 1;

		if(m_nSaveSelection > 1)
			m_nSaveSelection = 0;
		else if(m_nSaveSelection < 0)
			m_nSaveSelection = 1;


		if( pDI->KeyPressed( DIK_RETURN ) == true || pDI->JoystickButtonPressed(1))
		{
			switch( m_nSaveSelection )
			{
			case 0:			// PLAY
				{
					CProfileMenuState::GetInstance()->SaveGame(m_pPlayer->GetName());
					m_bSaveSuccess = true;
					return true;
				}
				break;
			case 1:			// PLAY
				{
					m_bSaveGameStatus = false;
					return true;
				}
				break;
			default:
				break;
			}
		}


	}
	else if(m_bSaveSuccess)
	{
		if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(1))
		{
			m_bSaveSuccess = false;
			m_bSaveGameStatus = false;
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
		if(!m_bDialogue)
		{
			for(unsigned int i = 0; i < m_vShowOnScreen.size();i++)
			{
				m_vShowOnScreen[i]->m_fTimer -= fElapsedTime;
				if(m_vShowOnScreen[i]->m_fTimer < 0)
				{
					m_bDialogue = true;
				}
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

			m_mWorldManager[m_sCurrWorld]->Update(fElapsedTime);
		}
		m_pES->ProcessEvents();
	}
}

void CGamePlayState::Render(void)
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	//RECT temp = { 0, 0, WorldHeight, WorldWidth };
	//OffsetRect(&temp, -WorldCamX, -WorldCamY);
	//pD3D->DrawRect( temp, D3DCOLOR_XRGB( 255,255,0 ) );

	m_pRM->Render();
	m_temp.Render();
	wostringstream woss;

	for(unsigned int i = 0; i < m_vShowOnScreen.size();i++)
	{
		woss << m_vShowOnScreen[i]->szText.str();
		pD3D->DrawRect(m_vShowOnScreen[i]->rPos, D3DCOLOR_ARGB(186,0,0,0));
		pD3D->DrawHollowRect(m_vShowOnScreen[i]->rPos, D3DCOLOR_ARGB(255,255,0,0));

		CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), m_vShowOnScreen[i]->rPos.left + 4, m_vShowOnScreen[i]->rPos.top + 4, 0.8f, D3DCOLOR_XRGB(255, 255, 255));

		woss.str(_T(""));
	}

	if(bisPaused && !m_bSaveGameStatus)
	{
		RECT rTemp = {336, 236, 464,364};
		pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(190,0,0,0));
		CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(), 272, 172);
		CGame::GetInstance()->GetFont("Arial")->Draw(_T("Resume\nCharacter\nSave\nQuit"), 368,258, 0.75f, D3DCOLOR_XRGB(255,255, 255));
		rTemp.left = 0;
		rTemp.top = 0;
		rTemp.right = 16;
		rTemp.bottom = 32;
		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 360, 262 + (GetCursorSelection() * 21),1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI /2, D3DCOLOR_XRGB(255,255,255));
	}
	else if(m_bSaveGameStatus && !m_bSaveSuccess)
	{
		RECT rTemp = {336, 236, 464,364};
		pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(190,0,0,0));
		CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(), 272, 172);
		CGame::GetInstance()->GetFont("Arial")->Draw(_T("Save?\n\nYes\nNo"), 368,258, 0.75f, D3DCOLOR_XRGB(255,255, 255));
		rTemp.left = 0;
		rTemp.top = 0;
		rTemp.right = 16;
		rTemp.bottom = 32;
		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 360, 304 + (m_nSaveSelection * 21),1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI /2, D3DCOLOR_XRGB(255,255,255));
	}
	else if(m_bSaveSuccess)
	{
		RECT rTemp = {336, 236, 464,364};
		pD3D->DrawRect(rTemp, D3DCOLOR_ARGB(190,0,0,0));
		CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(), 272, 172);
		CGame::GetInstance()->GetFont("Arial")->Draw(_T("Success!"), 360,294, 0.75f, D3DCOLOR_XRGB(255,255, 255));


	}
	woss.str(_T(""));
}

void CGamePlayState::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "INIT_BATTLE" && m_eCurrPhase != GP_END)
	{
		m_eCurrPhase = GP_BATTLE;
		if(m_mWorldManager[m_sCurrWorld]->GetMusicID() != -1 && CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(m_mWorldManager[m_sCurrWorld]->GetMusicID()))
			CSGD_XAudio2::GetInstance()->MusicStopSong(m_mWorldManager[m_sCurrWorld]->GetMusicID());
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
	else if(pEvent->GetEventID() == "GIVE_ITEM")
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

void CGamePlayState::LoadWorld(string szFileName)
{
	if(m_mWorldManager[szFileName] != nullptr)
	{
		m_sCurrWorld = szFileName;
		return;
	}
	string szTempFileName = "assets/Data/Levels/";
	szTempFileName += szFileName;

	std::string temp;

	CWorld* Worldtemp = new CWorld;
	TiXmlDocument doc;
	if(doc.LoadFile(szTempFileName.c_str()) == false)
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

	string szMusic = "";

	if(pRoot->Attribute("Music") != nullptr)
	{
		wostringstream woss;
		szMusic = pRoot->Attribute("Music");
		woss << "Assets/Audio/Music/" << szMusic.c_str();
		Worldtemp->SetMusic(CSGD_XAudio2::GetInstance()->MusicLoadSong(woss.str().c_str()));
	}



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
							pTempTile->SetEventID(pTileData->Attribute("EventID"));
						}
						else if(ReadIn == "NPCS")
						{
							CNpcs* pNpc = new CNpcs();
							string szTemp ="assets/Data/NPCS/";
							szTemp += pTileData->Attribute("EventID");
							szTemp += ".xml";
							int nWaypoints = 0;
							pTileData->Attribute("Total_Waypoints", &nWaypoints);
							TiXmlElement *pConvo = nullptr;
							TiXmlElement* pWaypoints = nullptr;
							if(nWaypoints != 0)
								pWaypoints = pTileData->FirstChildElement("Waypoint");
							TiXmlDocument tempDoc;
							if(tempDoc.LoadFile(szTemp.c_str()))
							{
								TiXmlElement* pOtherRoot = tempDoc.RootElement();
								pNpc->SetName(pOtherRoot->Attribute("Name"));
								string szTemporary = pNpc->GetName() + "_Idle";
								pNpc->GetAnimInfo()->SetAnimation(szTemporary);
								pNpc->SetPosX(float(tileID % layerWidth * tileWidth));
								pNpc->SetPosY(float(tileID / layerWidth * tileHeight));

								int nUnits = 0;
								int nConvos = 0;
								pOtherRoot->Attribute("Total_Conversations", &nConvos);
								pOtherRoot->Attribute("Units", &nUnits);
								string Hostile = pOtherRoot->Attribute("Hostile");
								if(Hostile == "true")
									pNpc->SetHostile(true);
								else
									pNpc->SetHostile(false);


								if(nConvos != 0)
									pConvo = pOtherRoot->FirstChildElement("Convo");
								TiXmlElement* pOtherUnits = pOtherRoot->FirstChildElement("Unit");
								string szUnitName = "";
								if(pOtherUnits != nullptr)
								{

									for(int i =0; i < nUnits; i++)
									{
										if(pOtherUnits != nullptr)
										{
											szUnitName = pOtherUnits->Attribute("Name");
											CEnemyUnit* pEUnit = reinterpret_cast<CEnemyUnit*>(LoadUnit(szUnitName));
											if(pEUnit != nullptr)
											{
												if(i == 0)
												{
													pEUnit->SetPosX(100.0f);
													pEUnit->SetPosY(250.0f);
												}
												else if(i == 1)
												{
													pEUnit->SetPosX(200.0f);
													pEUnit->SetPosY(350.0f);
												}
												else if(i == 2)
												{
													pEUnit->SetPosX(100.0f);
													pEUnit->SetPosY(400.0f);
												}
												pNpc->SetUnits(pEUnit);

											}
											szUnitName = "";
										}
										pOtherUnits = pOtherUnits->NextSiblingElement("Unit");
									}
								}

								if(pWaypoints != nullptr)
								{
									for(int i = 0; i < nWaypoints; i++)
									{
										if(pWaypoints != nullptr)
										{
											int nWPx = -1;
											int nWPy = -1;
											pWaypoints->Attribute("X", &nWPx);
											pWaypoints->Attribute("Y", &nWPy);
											pNpc->AddWaypoint(float(nWPx), float(nWPy));
										}
										pWaypoints = pWaypoints->NextSiblingElement("Waypoint");

									}
								}

								if(pConvo != nullptr)
								{
									for(int i = 0; i < nConvos; i++)
									{
										if(pConvo != nullptr)
										{
											pNpc->AddConversation(pConvo->Attribute("Text"));
										}
										pConvo = pConvo->NextSiblingElement("Convo");

									}
								}

								Worldtemp->AddObject(pNpc, 2);
								pNpc->Release();


							}
							else
							{
								delete pNpc;
							}
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
						else if(ReadIn == "CHESTS")
						{
							CChest* pChest = new CChest();
							pChest->SetPosX(float(tileID % layerWidth * tileWidth));
							pChest->SetPosY(float(tileID / layerWidth * tileHeight));
							pChest->GetAnimInfo()->SetAnimation("Chest_Closed");

							TiXmlElement* pXmlChest = pTileData->FirstChildElement("Chest");
							if(pXmlChest != nullptr)
							{
								int nItemAmount = 0;
								string szItemName = "";
								for(;;)
								{
									if(pXmlChest == nullptr)
										break;

									szItemName = pXmlChest->Attribute("Name");
									pXmlChest->Attribute("Amount", &nItemAmount);

									if(szItemName != "")
										pChest->AddConsumableItem(m_mItemManager[szItemName].Item, nItemAmount);

									pXmlChest = pXmlChest->NextSiblingElement("Chest");
									szItemName = "";
									nItemAmount = 0;
								}
							}
							Worldtemp->AddObject(pChest, 2);
							pChest->Release();
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

	m_mWorldManager[szFileName] = Worldtemp;
	m_sCurrWorld = szFileName;
}

CPlayerUnit* CGamePlayState::GetPlayerUnit()
{
	return reinterpret_cast<CPlayerUnit*>(m_pPlayer->GetUnit());
}

void CGamePlayState::TransitionWorld(std::string szNewWorld)
{
	if(m_sCurrWorld == szNewWorld + ".xml" || szNewWorld == "")
		return;

	int nOldMusic = m_mWorldManager[m_sCurrWorld]->GetMusicID();
	int nNewMusic = -1;
	m_pPlayer->SetZone(szNewWorld);
	m_mWorldManager[m_sCurrWorld]->RemoveObject(m_pPlayer);
	m_mWorldManager[m_sCurrWorld]->ActivateNPCs();
	m_mWorldManager[m_sCurrWorld]->ClearNPCList();

	LoadWorld(szNewWorld + ".xml");
	m_mWorldManager[szNewWorld + ".xml"]->AddObject(m_pPlayer, 2);
	m_sCurrWorld = szNewWorld + ".xml";

	nNewMusic = m_mWorldManager[m_sCurrWorld]->GetMusicID();

	if(nNewMusic != -1 && nOldMusic != -1 && nNewMusic != nOldMusic)
	{
		CSGD_XAudio2::GetInstance()->MusicStopSong(nOldMusic);
		CSGD_XAudio2::GetInstance()->MusicPlaySong(nNewMusic, true);
	}
	else if(nNewMusic != -1 && nOldMusic != -1 && CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(nNewMusic) == false)
		CSGD_XAudio2::GetInstance()->MusicPlaySong(nNewMusic, true);

	m_pPlayer->SetIsWarping(false);
}

void CGamePlayState::SetPlayer(CPlayer* pPlayer)
{
	if(m_pPlayer != nullptr)
		m_pPlayer->Release();

	m_pPlayer = pPlayer;

	if(m_pPlayer != nullptr)
	{
		m_pPlayer->AddRef();


	}
}

CEnemyUnit* CGamePlayState::CreateTempEnemy(string input, float X, float Y, int speed, int hp, int mp, int attack)
{
	CEnemyUnit* temp = new CEnemyUnit;
	CAIController* tempAI = new CAIController;
	CBasicAttack* tempAtk = new CBasicAttack;
	CAnimationTimeStamp* pTemp;
	pTemp = temp->GetAnimInfo();
	//pTemp->SetAnimation("Thornbiter_Idle");
	//pTemp->SetCurrentFrame(0);
	temp->SetType(OBJ_ENEMY_UNIT);
	if(input == "Mandrake")
	{
		pTemp->SetAnimation("Mandrake_Battle_Idle");
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
	else if (input == "Orc_Shaman")
	{
		pTemp->SetAnimation("Orc_Shaman_Battle_Idle");
	}
	else if (input == "Snail")
	{
		pTemp->SetAnimation("Snail_Battle_Idle");
	}
	else if (input == "Cave_Spider")
	{
		pTemp->SetAnimation("Cave_Spider_Battle_Idle");
	}
	else if (input == "Cave_Bat")
	{
		pTemp->SetAnimation("Cave_Bat_Battle_Idle");
	}
	else if (input == "Ogre")
	{
		pTemp->SetAnimation("Ogre_Battle_Idle");
	}
	else if (input == "Thornbiter")
	{
		pTemp->SetAnimation("Thornbiter_Battle_Idle");
	}
	else if (input == "TigerLily")
	{
		pTemp->SetAnimation("TigerLily_Battle_Idle");
	}
	else if (input == "Bee")
	{
		pTemp->SetAnimation("Bee_Battle_Idle");
	}
	else if (input == "Bandit")
	{
		pTemp->SetAnimation("Bandit_Battle_Idle");
	}
	else if (input == "Snake")
	{
		pTemp->SetAnimation("Snake_Battle_Idle");
	}
	else if (input == "Golem")
	{
		pTemp->SetAnimation("Golem_Battle_Idle");
	}
	else if (input == "Shade")
	{
		pTemp->SetAnimation("Shade_Battle_Idle");
	}
	else if (input == "Cultist")
	{
		pTemp->SetAnimation("Cultist_Battle_Idle");
	}
	else if (input == "Valrion")
	{
		pTemp->SetAnimation("Valrion_Battle_Idle");
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
	if(m_mWorldManager[szName] == nullptr)
	{
		string szTemporary = m_sCurrWorld;
		LoadWorld(szName);
		m_sCurrWorld = szTemporary;
	}
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

	CGame::GetInstance()->GetFont("Arial")->GetDimensions(pOwner,ftTemp->rPos, szText);

	ftTemp->Color = dColor;
	ftTemp->szText << szText.str();
	ftTemp->m_fTimer = 0.1f;


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

CUnits* CGamePlayState::LoadUnit(string szFileName)
{
	string szFile = "assets/Data/Units/" + szFileName + ".xml";
	TiXmlDocument doc;
	if(doc.LoadFile(szFile.c_str()) == false)
		return nullptr;

	TiXmlElement *pRoot = doc.RootElement();
	if(pRoot == nullptr)
		return nullptr;

	CEnemyUnit* pTempUnit = new CEnemyUnit();
	string szName = "";
	int nHealth = 0;
	int nAP = 0;
	int nAttack =0;
	int nEXP = 0;
	int nSpeed = 1;
	int nLevel = 0;
	string szAI = "";
	int nTotalItems = 0;

	szName = pRoot->Attribute("Name");
	szAI = pRoot->Attribute("AI");
	pRoot->Attribute("Health",&nHealth);
	pRoot->Attribute("AP",&nAP);
	pRoot->Attribute("Attack",&nAttack);
	pRoot->Attribute("Exp",&nEXP);
	pRoot->Attribute("Speed",&nSpeed);
	pRoot->Attribute("Level",&nLevel);
	pRoot->Attribute("Total_Items",&nTotalItems);
	pTempUnit->SetName(szName);
	pTempUnit->SetMaxHealth(nHealth);
	pTempUnit->SetMaxAP(nAP);
	pTempUnit->SetAttack(nAttack);
	pTempUnit->SetLevel(nLevel);
	pTempUnit->GiveExperience(nEXP);
	pTempUnit->SetSpeed(nSpeed);

	string szTemp = szFileName + "_Battle_Idle";
	pTempUnit->GetAnimInfo()->SetAnimation(szTemp);

	CBasicAttack* tempAtk = new CBasicAttack;
	CAIController* tempAI = new CAIController();
	if(szAI == "Brute")
	{
		delete tempAI;
		CAIBrute* Temp = new CAIBrute;
		tempAI = reinterpret_cast<CAIController*>(Temp);
		Temp = nullptr;
	}
	else if( szAI == "BasicHealer")
	{
		delete tempAI;
		CAIBasicHealer* Temp = new CAIBasicHealer;
		tempAI = reinterpret_cast<CAIController*>(Temp);
		Temp = nullptr;
		pTempUnit->SetType(OBJ_LEADER);
	}
	else if( szAI == "OrcLeader")
	{
		delete tempAI;
		CAIOrcLeader* Inferno = new CAIOrcLeader;
		tempAI = reinterpret_cast<CAIController*>(Inferno);
		Inferno = nullptr;
		pTempUnit->SetType(OBJ_LEADER);

	}
	else if(szAI == "TigerLily")
	{
		delete tempAI;
		CAITigerlily* Inferno = new CAITigerlily;
		tempAI = reinterpret_cast<CAIController*>(Inferno);
		Inferno = nullptr;
		pTempUnit->SetType(OBJ_LEADER);
	}
	else if(szAI == "Valrion")
	{
		delete tempAI;
		CAIValrion* Inferno = new CAIValrion;
		tempAI = reinterpret_cast<CAIController*>(Inferno);
		Inferno = nullptr;
		pTempUnit->SetType(OBJ_LEADER);
	}

	tempAI->AddMinigame(tempAtk);
	tempAI->MakeOwner(pTempUnit);
	pTempUnit->SetAIController(tempAI);

	TiXmlElement *pItems = pRoot->FirstChildElement("Item");
	{
		if(pItems != nullptr)
		{

			for(int i = 0; i < nTotalItems; i++)
			{
				if(pItems != nullptr)
				{
					int nDropChance = 0;
					string szItemName = pItems->Attribute("Name");
					pItems->Attribute("Chance", &nDropChance);
					pTempUnit->AddConsumableItem(m_mItemManager[szItemName].Item,1,nDropChance * 0.01f);
				}
				pItems = pItems->NextSiblingElement("Item");
			}
		}
	}

	return pTempUnit;
}

CAugment* CGamePlayState::CreateAugment(string Type, float Effect)
{

	CAugment* temp;

	if(Type == "HP")
	{
		temp = new CAugment;
		temp->SetAugType(Type);
		temp->SetName("HP Augment");
		temp->SetEffect(Effect);
	}
	else if(Type == "ATTK")
	{
		temp = new CAugment;
		temp->SetAugType(Type);
		temp->SetName("Atk Augment");
		temp->SetEffect(Effect);
	}
	else if(Type == "AP")
	{
		temp = new CAugment;
		temp->SetAugType(Type);
		temp->SetName("AP Augment");
		temp->SetEffect(Effect);
	}
	else if(Type == "SPEED")
	{
		temp = new CAugment;
		temp->SetAugType(Type);
		temp->SetName("Speed Augment");
		temp->SetEffect(Effect);
	}
	else
	{
		temp = nullptr;
	}

	return temp;
}

CArmor* CGamePlayState::CreateArmor(string Name, float Hp, float Attk, float Speed)
{
	CArmor* temp = new CArmor;
	temp->SetName(Name);
	temp->SetAttkStat(Attk);
	temp->SetHpStat(Hp);
	temp->SetSpeedStat(Speed);
	return temp;
}

CWeapon* CGamePlayState::CreateWeapon(string Name, int Attack)
{
	CWeapon* temp = new CWeapon;
	temp->SetAttack(Attack);
	temp->SetName(Name);
	return temp;
}

