#include "ProfileMenuState.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../TinyXML/tinyxml.h"

#include "Commands.h"
#include "BasicAttack.h"
#include "TriggerSpree.h"
#include "TriggerMatch.h"
#include "ChargeCrystal.h"
#include "ComboGame.h"
#include "UseItem.h"
#include "PrecisionStrike.h"
#include "SteadyShot.h"

#include "MainMenuState.h"
#include "GamePlayState.h"
#include "Game.h"
#include "Buff.h"
#include <sstream>
CProfileMenuState::CProfileMenuState(void)
{
	m_eCurrState = PS_SELECT;
	m_bLeft = false;
	m_fOffSetX = 0.0f;

	SetSFXID(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/SFX/POA_CursorSFX.wav")));
	SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_logo.png")));
	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));

	SetBackgroundMusic(-1);
}

CProfileMenuState::~CProfileMenuState(void)
{
	Sleep();
}

CProfileMenuState* CProfileMenuState::GetInstance( void )
{
	static CProfileMenuState s_Instance;

	return &s_Instance;
}

void CProfileMenuState::Activate()
{
	CGamePlayState::GetInstance()->Activate();
	CGamePlayState::GetInstance()->Sleep();

	LoadSave("Player1.xml");
	LoadSave("Player2.xml");
	LoadSave("Player3.xml");

	m_eCurrState = PS_SELECT;

	m_bLeft = false;
	m_fOffSetX = 0.0f;
	m_fPosY = 172.0f;

	if(CMainMenuState::GetInstance()->GetLeftMenuState())
	{
		if(!CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(CMainMenuState::GetInstance()->GetBackgroundMusic()))
			CSGD_XAudio2::GetInstance()->MusicPlaySong(CMainMenuState::GetInstance()->GetBackgroundMusic(), true);
		CMainMenuState::GetInstance()->SetLeftMenuState(false);
	}
}

void CProfileMenuState::Sleep()
{
	for(unsigned int i = 0; i < m_vCharacterList.size(); i++)
	{
		m_vCharacterList[i]->Release();
		m_vCharacterList[i] = nullptr;
	}

	m_vCharacterList.clear();
	m_vWorldData.clear();


}

bool CProfileMenuState::Input()
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(m_fPosY <= 0.0f)
	{
		if(pDI->KeyPressed(DIK_ESCAPE) || pDI->JoystickButtonPressed(2))
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		if(pDI->KeyPressed(DIK_W) || pDI->KeyPressed(DIK_UPARROW) || pDI->JoystickDPadPressed(DIR_UP) || pDI->JoystickGetLStickDirPressed(DIR_UP))
		{
			if(GetCursorSelection() <= 0)
				SetCursorSelection(5);
			else
				SetCursorSelection(GetCursorSelection() - 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_S) || pDI->KeyPressed(DIK_DOWNARROW) || pDI->JoystickDPadPressed(DIR_DOWN) || pDI->JoystickGetLStickDirPressed(DIR_DOWN))
		{
			if(GetCursorSelection() >= 5)
				SetCursorSelection(0);
			else
				SetCursorSelection(GetCursorSelection() + 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(1))
		{
			switch (GetCursorSelection())
			{
			case 0:
				if(m_eCurrState != PS_NEWGAME)
					m_eCurrState = PS_NEWGAME;
				else
					m_eCurrState = PS_SELECT;
				break;
			case 1:
				if(m_eCurrState == PS_DELETE)
				{
					if(m_vCharacterList[0]->GetUnit()->GetName() != "Empty")
					{
						m_vCharacterList[0]->Release();
						m_vCharacterList[0] = nullptr;
						m_vCharacterList[0] = CreatePlayer();
						m_vCharacterList[0]->GetUnit()->SetName("Empty");
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[0]);
						m_vWorldData[0].clear();
						SaveGame("Player1.xml");
						m_eCurrState = PS_SELECT;
					}

				}
				else if(m_eCurrState == PS_NEWGAME)
				{
					if(m_vCharacterList[0]->GetUnit()->GetName() == "Empty")
					{
						m_vCharacterList[0]->Release();
						m_vCharacterList[0] = nullptr;
						m_vCharacterList[0] = CreatePlayer();
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[0]);
						m_vWorldData[0].clear();
						SaveGame("Player1.xml");
						m_eCurrState = PS_SELECT;
					}

				}
				else
				{
					if(m_vCharacterList[0]->GetUnit()->GetName() == "Arin")
					{
						string szZone = m_vCharacterList[0]->GetZone() + ".xml";
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[0]);
						CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
						for(unsigned int i = 0; i < m_vWorldData[0].size();i++)
							pWorld->AddClear(m_vWorldData[0][i]);
						CMainMenuState::GetInstance()->SetLeftMenuState(true);
						CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
					}
				}

				break;
			case 2:
				if(m_eCurrState == PS_DELETE)
				{
					if(m_vCharacterList[1]->GetUnit()->GetName() != "Empty")
					{
						m_vCharacterList[1]->Release();
						m_vCharacterList[1] = nullptr;
						m_vCharacterList[1] = CreatePlayer();
						m_vCharacterList[1]->GetUnit()->SetName("Empty");
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[1]);
						m_vWorldData[1].clear();
						SaveGame("Player2.xml");
						m_eCurrState = PS_SELECT;
					}

				}
				else if(m_eCurrState == PS_NEWGAME)
				{
					if(m_vCharacterList[1]->GetUnit()->GetName() == "Empty")
					{
						m_vCharacterList[1]->Release();
						m_vCharacterList[1] = nullptr;
						m_vCharacterList[1] = CreatePlayer();
						m_vWorldData[1].clear();
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[1]);
						SaveGame("Player2.xml");
						m_eCurrState = PS_SELECT;
					}

				}
				else
				{
					if(m_vCharacterList[1]->GetUnit()->GetName() == "Arin")
					{
						string szZone = m_vCharacterList[1]->GetZone() + ".xml";
						CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[1]);
						for(unsigned int i = 0; i < m_vWorldData[1].size();i++)
							pWorld->AddClear(m_vWorldData[1][i]);
						CMainMenuState::GetInstance()->SetLeftMenuState(true);
						CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
					}
				}
				break;
			case 3:
				if(m_eCurrState == PS_DELETE)
				{
					if(m_vCharacterList[2]->GetUnit()->GetName() != "Empty")
					{
						m_vCharacterList[2]->Release();
						m_vCharacterList[2] = nullptr;
						m_vCharacterList[2] = CreatePlayer();
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[2]);
						m_vCharacterList[2]->GetUnit()->SetName("Empty");
						m_vWorldData[2].clear();
						SaveGame("Player3.xml");
						m_eCurrState = PS_SELECT;
					}
				}
				else if(m_eCurrState == PS_NEWGAME)
				{
					if(m_vCharacterList[2]->GetUnit()->GetName() == "Empty")
					{
						m_vCharacterList[2]->Release();
						m_vCharacterList[2] = nullptr;
						m_vCharacterList[2] = CreatePlayer();
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[2]);
						m_vWorldData[2].clear();
						SaveGame("Player3.xml");
						m_eCurrState = PS_SELECT;
					}
				}
				else
				{
					if(m_vCharacterList[2]->GetUnit()->GetName() == "Arin")
					{
						string szZone = m_vCharacterList[2]->GetZone() + ".xml";
						CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[2]);
						for(unsigned int i = 0; i < m_vWorldData[2].size();i++)
							pWorld->AddClear(m_vWorldData[2][i]);
						CMainMenuState::GetInstance()->SetLeftMenuState(true);
						CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
					}
				}
				break;
			case 4:
				if(m_eCurrState != PS_DELETE)
					m_eCurrState = PS_DELETE;
				else
					m_eCurrState = PS_SELECT;
				break;
			case 5:
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			default:
				break;
			}
		}
		return true;
	}
	return true;
}

void CProfileMenuState::Update(float fElapsedTime )
{
	if(CMainMenuState::GetInstance()->GetLeftMenuState())
	{
		if(CSGD_XAudio2::GetInstance()->MusicIsSongPlaying(CMainMenuState::GetInstance()->GetBackgroundMusic()))
			CSGD_XAudio2::GetInstance()->MusicStopSong(CMainMenuState::GetInstance()->GetBackgroundMusic());
	}

	if(m_fPosY > 0)
	{
		m_fPosY -= 200 * fElapsedTime;
		return;
	}
	else
	{
		if(m_bLeft)
			m_fOffSetX -= (20 * fElapsedTime);
		else
			m_fOffSetX += (20 * fElapsedTime);

		if(m_fOffSetX >= 10.0f)
			m_bLeft = true;
		else if(m_fOffSetX <= 0.0f)
			m_bLeft = false;
	}

}

void CProfileMenuState::Render()
{
	CSGD_Direct3D* pD3D = CSGD_Direct3D::GetInstance();
	RECT rLogo = {0,0,512,256};
	RECT temp = {0, 0, 800, 600};
	CSGD_Direct3D::GetInstance()->DrawRect(temp, D3DCOLOR_XRGB(255,255,255));
	CSGD_TextureManager::GetInstance()->Draw(GetBackgroundImg(),144,(int)m_fPosY,1.0f,1.0f,&rLogo,0.0f,0.0f,0.0f,D3DCOLOR_ARGB(230,255,255,255));
	if(m_fPosY <= 0.0f)
	{
		std::wostringstream woss;
		woss << "New Game\n\n    Slot 1: " << m_vCharacterList[0]->GetUnit()->GetName().c_str() << "\tLevel: " << m_vCharacterList[0]->GetUnit()->GetLevel() << "\tZone: " << m_vCharacterList[0]->GetZone().c_str()
			<< "\n\n    Slot 2: " << m_vCharacterList[1]->GetUnit()->GetName().c_str() << "\tLevel: " << m_vCharacterList[1]->GetUnit()->GetLevel() << "\tZone: " << m_vCharacterList[1]->GetZone().c_str()
			<< "\n\n    Slot 3: " << m_vCharacterList[2]->GetUnit()->GetName().c_str() << "\tLevel: " << m_vCharacterList[2]->GetUnit()->GetLevel() << "\tZone: " << m_vCharacterList[2]->GetZone().c_str()
			<< "\n\nDelete\nMain Menu";
		CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 64, 272,1.0f, D3DCOLOR_XRGB(0,0,0));
		woss.str(_T(""));
		RECT rTemp = {0,0,16,32};
		switch(GetCursorSelection())
		{
		case 0:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 48 + (int)m_fOffSetX, 278, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);
			break;

		case 1:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 72 + (int)m_fOffSetX, 339, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);
			break;

		case 2:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 72 + (int)m_fOffSetX, 400, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);
			break;

		case 3:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 72 + (int)m_fOffSetX, 461, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);
			break;

		case 4:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 48 + (int)m_fOffSetX, 522, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);

			break;

		case 5:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(), 48 + (int)m_fOffSetX, 552, 1.0f,1.0f,&rTemp, 0.0f,0.0f, D3DX_PI / 2);

			break;

		default:
			break;


		}
		switch (m_eCurrState)
		{
		case CProfileMenuState::PS_NEWGAME:
			woss << "Which Slot would you like to use?";
			CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 256, 272,1.0f,D3DCOLOR_XRGB(0,0,0));
			break;
		case CProfileMenuState::PS_SELECT:
			break;
		case CProfileMenuState::PS_DELETE:
			woss << "Which Slot would you like to delete?";
			CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(), 256, 272,1.0f,D3DCOLOR_XRGB(0,0,0));

			break;
		default:
			break;
		}
	}
}

void CProfileMenuState::LoadSave(std::string szFileName)
{
	string szSaveName = CGame::GetInstance()->GetSafePath();
	szSaveName +=szFileName;
	TiXmlDocument doc;
	if(doc.LoadFile(szSaveName.c_str()) == false)
	{
		TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "");
		doc.LinkEndChild(pDecl);	
		TiXmlElement* pRoot = new TiXmlElement("Saves");
		doc.LinkEndChild(pRoot);
		std::string szTemp = "";
		TiXmlElement* pSlot = new TiXmlElement("Slot");
		TiXmlElement* pWorldData = new TiXmlElement("Defeated");
		TiXmlElement* pInventory = new TiXmlElement("Inventory");
		TiXmlElement* pEquipment = new TiXmlElement("Equipped");
		szTemp = "Empty";

		pSlot->SetAttribute("Name", szTemp.c_str());
		pSlot->SetAttribute("Level", 1);
		pSlot->SetAttribute("Attack", 20);
		pSlot->SetAttribute("Health", 350);
		pSlot->SetAttribute("Max_Health", 350);
		pSlot->SetAttribute("AP", 100);
		pSlot->SetAttribute("Max_AP", 100);
		pSlot->SetAttribute("Experience", 0);
		pSlot->SetAttribute("Speed:", 3);
		pSlot->SetAttribute("Class", 0);
		pSlot->SetAttribute("posX", 488);
		pSlot->SetAttribute("posY", 420);
		pSlot->SetAttribute("Zone", "Caveren_of_souls");
		string szZone = "Caveren_of_souls.xml";

		TiXmlElement* pItem;
		pItem = new TiXmlElement("Item");
		pItem->SetAttribute("Name", "Potion");
		pItem->SetAttribute("Amount", 2);

		pInventory->LinkEndChild(pItem);


		pEquipment->SetAttribute("Weapon", "Empty");
		pEquipment->SetAttribute("Armor", "Empty");
		pEquipment->SetAttribute("Augment", "Empty");


		pRoot->LinkEndChild(pSlot);
		pRoot->LinkEndChild(pEquipment);
		pRoot->LinkEndChild(pWorldData);
		pRoot->LinkEndChild(pInventory);

		doc.SaveFile(szSaveName.c_str());
	}

	if(doc.LoadFile(szSaveName.c_str()) == false)
		return;
	TiXmlElement *pRoot = doc.RootElement();
	if(	pRoot == nullptr )
		return;

	TiXmlElement* pSlot = pRoot->FirstChildElement("Slot");
	if(pSlot != nullptr)
	{
		CPlayer* pPlayer;
		int nTemp = 0;
		pPlayer = CreatePlayer();
		int nClass = 0;
		pSlot->Attribute("Class", &nClass);
		CPlayerUnit* pUnit = nullptr;
		switch(nClass)
		{
		case 1:
			pUnit = CreateWarrior();
			break;
		case 2:
			pUnit = CreateRanger();
			break;
		case 3: 
			pUnit = CreateMage();
			break;
		default:
			pUnit = CreateTempPlayer();
		}

		pPlayer->SetUnit(pUnit);
		pUnit->Release();

		pPlayer->GetUnit()->SetName(pSlot->Attribute("Name"));
		pSlot->Attribute("posX", &nTemp);
		pPlayer->SetPosX(float(nTemp));
		pSlot->Attribute("posY", &nTemp);
		pPlayer->SetPosY(float(nTemp));
		pPlayer->SetName(szFileName);
		pPlayer->SetZone(pSlot->Attribute("Zone"));

		int nLevel = 0;
		int nAttack = 0;
		int nHealth = 0;
		int nMaxHealth = 0;
		int nAP = 0;
		int nMaxAP = 0;
		int nExp = 0;
		int nSpeed = 0;

		pSlot->Attribute("Level", &nLevel);
		pSlot->Attribute("Attack", &nAttack);
		pSlot->Attribute("Health", &nHealth);
		pSlot->Attribute("Max_Health", &nMaxHealth);
		pSlot->Attribute("AP", &nAP);
		pSlot->Attribute("Max_AP", &nMaxAP);
		pSlot->Attribute("Experience", &nExp);
		pSlot->Attribute("Speed", &nSpeed);

		pPlayer->GetUnit()->SetLevel(nLevel);
		pPlayer->GetUnit()->SetMaxHealth(nMaxHealth);
		pPlayer->GetUnit()->SetMaxAP(nAP);
		pPlayer->GetUnit()->GiveExperience(nExp);
		pPlayer->GetUnit()->SetSpeed(nSpeed);
		pPlayer->GetUnit()->SetHealth(nHealth);
		pPlayer->GetUnit()->SetAP(nAP);
		pPlayer->GetUnit()->SetAttack(nAttack);

		TiXmlElement* pWorldData = pRoot->FirstChildElement("Defeated");
		TiXmlElement* pNPCid = pWorldData->FirstChildElement("NPC");
		nTemp = -1;
		vector<int> vTemp;

		for(;pNPCid != nullptr;)
		{
			pNPCid->Attribute("ID", &nTemp);
			if(nTemp != -1)
			{
				vTemp.push_back(nTemp);
			}
			pNPCid = pNPCid->NextSiblingElement("NPC");
		}
		m_vWorldData.push_back(vTemp);

		TiXmlElement* pInventory = pRoot->FirstChildElement("Inventory");
		map<string, InventoryItems>* pTempItemManager = CGamePlayState::GetInstance()->GetItemManager();

		if(pInventory != nullptr)
		{
			CPlayerUnit* pTempUnit = reinterpret_cast<CPlayerUnit*>(pPlayer->GetUnit());

			string szItemName = "";
			int nItemAmount = 0;
			TiXmlElement* pItem = pInventory->FirstChildElement("Item");
			for(;;)
			{
				if(pItem == nullptr)
					break;
				szItemName = pItem->Attribute("Name");
				pItem->Attribute("Amount", &nItemAmount);

				if(nItemAmount > 0 && szItemName != "")
					pTempUnit->AddConsumableItem((*pTempItemManager)[szItemName].Item, nItemAmount);

				pItem = pItem->NextSiblingElement("Item");
			}
		}

		TiXmlElement* pEquipment = pRoot->FirstChildElement("Equipped");
		if(pEquipment != nullptr)
		{
			CPlayerUnit* pTempUnit = reinterpret_cast<CPlayerUnit*>(pPlayer->GetUnit());
			string szItemEquipped = "";
			szItemEquipped = pEquipment->Attribute("Weapon");
			if(szItemEquipped != "Empty" || szItemEquipped != "")
				pTempUnit->EquipWeapon(reinterpret_cast<CWeapon*>((*pTempItemManager)[szItemEquipped].Item));

			szItemEquipped = "";
			szItemEquipped = pEquipment->Attribute("Armor");
			if(szItemEquipped != "Empty" || szItemEquipped != "")
				pTempUnit->EquipArmor(reinterpret_cast<CArmor*>((*pTempItemManager)[szItemEquipped].Item));

			szItemEquipped = "";
			szItemEquipped = pEquipment->Attribute("Augment");
			if(szItemEquipped != "Empty" || szItemEquipped != "")
				pTempUnit->EquipAugment(reinterpret_cast<CAugment*>((*pTempItemManager)[szItemEquipped].Item));

		}
		m_vCharacterList.push_back(pPlayer);


	}
}

void CProfileMenuState::SaveGame(std::string szFileName)
{
	TiXmlDocument doc;
	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "utf-8", "");

	doc.LinkEndChild(pDecl);	
	TiXmlElement* pRoot = new TiXmlElement("Saves");

	doc.LinkEndChild(pRoot);
	TiXmlElement* pSlot = new TiXmlElement("Slot");
	TiXmlElement* pWorldData = new TiXmlElement("Defeated");
	TiXmlElement* pInventory = new TiXmlElement("Inventory");
	TiXmlElement* pEquipment = new TiXmlElement("Equipped");

	CPlayer* pTemp = reinterpret_cast<CPlayer*>(CGamePlayState::GetInstance()->GetPlayer());
	if(pTemp != nullptr)
	{
		pSlot->SetAttribute("Name", pTemp->GetUnit()->GetName().c_str());
		pSlot->SetAttribute("Level", pTemp->GetUnit()->GetLevel());
		pSlot->SetAttribute("Attack", pTemp->GetUnit()->GetAttack());
		pSlot->SetAttribute("Health", pTemp->GetUnit()->GetHealth());
		pSlot->SetAttribute("Max_Health", pTemp->GetUnit()->GetMaxHealth());
		pSlot->SetAttribute("AP", pTemp->GetUnit()->GetAbilityPoints());
		pSlot->SetAttribute("Max_AP", pTemp->GetUnit()->GetMaxAP());
		pSlot->SetAttribute("Experience", pTemp->GetUnit()->GetExperience());
		pSlot->SetAttribute("Speed", pTemp->GetUnit()->GetSpeed());
		pSlot->SetAttribute("Class", (int)pTemp->GetUnit()->GetClass());
		pSlot->SetAttribute("posX", int(pTemp->GetPosX()));
		pSlot->SetAttribute("posY", int(pTemp->GetPosY()));
		pSlot->SetAttribute("Zone", pTemp->GetZone().c_str());

		pTemp->SetName(szFileName);

		map<string, InventoryItems>* pTempInv = pTemp->GetUnit()->GetInv();
		TiXmlElement* pItem;
		for(auto i = pTempInv->begin(); i != pTempInv->end(); i++)
		{
			if(i->second.Owned > 0)
			{
				pItem = new TiXmlElement("Item");
				pItem->SetAttribute("Name", i->second.Item->GetName().c_str());
				pItem->SetAttribute("Amount", i->second.Owned);

				pInventory->LinkEndChild(pItem);
			}
		}


		CPlayerUnit* pTempUnit = reinterpret_cast<CPlayerUnit*>(pTemp->GetUnit());

		if(pTempUnit->GetWeapon() == nullptr)
			pEquipment->SetAttribute("Weapon", "Empty");
		else
			pEquipment->SetAttribute("Weapon", pTempUnit->GetWeapon()->GetName().c_str());

		if(pTempUnit->GetArmor() == nullptr)
			pEquipment->SetAttribute("Armor", "Empty");
		else
			pEquipment->SetAttribute("Armor", pTempUnit->GetArmor()->GetName().c_str());

		if(pTempUnit->GetAugment() == nullptr)
			pEquipment->SetAttribute("Augment", "Empty");
		else
			pEquipment->SetAttribute("Augment", pTempUnit->GetAugment()->GetName().c_str());

		string szZone = pTemp->GetZone();
		szZone += ".xml";
		CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
		if(pWorld != nullptr)
		{
			vector<int>& vTemp = pWorld->GetClearedNpcs();
			TiXmlElement* pNPCid;
			for(unsigned int i = 0; i < vTemp.size(); i++)
			{
				pNPCid = new TiXmlElement("NPC");
				pNPCid->SetAttribute("ID",vTemp[i]);
				pWorldData->LinkEndChild(pNPCid);
			}
		}

	}
	pRoot->LinkEndChild(pSlot);
	pRoot->LinkEndChild(pEquipment);
	pRoot->LinkEndChild(pWorldData);
	pRoot->LinkEndChild(pInventory);
	string szSaveName = CGame::GetInstance()->GetSafePath();
	szSaveName += szFileName;
	doc.SaveFile(szSaveName.c_str());
}

CPlayer* CProfileMenuState::CreatePlayer()
{
	CPlayer* temp = new CPlayer; // TODO: THIS IS A PLACE HOLDER
	temp->SetPosX(488.0f);
	temp->SetPosY(420.0f);
	temp->SetVelX(0.0f);
	temp->SetVelY(0.0f);
	CAnimationTimeStamp* pTemp;
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Warrior_Idle_Down");
	temp->SetZone("Caveren_of_souls");
	CPlayerUnit* pUnit = CreateTempPlayer();
	pUnit->SetClass(UC_NONE);
	temp->SetUnit(pUnit);
	pUnit->Release();
	pTemp->SetCurrentFrame(0);
	temp->SetHeight(10);
	temp->SetWidth(10);	
	return temp;
}

CPlayerUnit* CProfileMenuState::CreateTempPlayer(void)
{
	CPlayerUnit* temp = new CPlayerUnit;
	CCommands* tempC = new CCommands;
	CBasicAttack* tempM = new CBasicAttack;
	CAnimationTimeStamp* pTemp;
	temp->SetClass(UC_NONE);
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Warrior_Battle_Idle");
	pTemp->SetCurrentFrame(0);
	tempC->SetName("Attack");
	tempM->SetCost(0);
	tempC->SetMiniGame(tempM);
	temp->AddSkill(tempC);
	tempC = new CCommands;

	CUseItem* tempL = new CUseItem;
	tempL->SetDamageSkill(false);
	tempL->SetCost(0);
	tempC->SetName("Items");
	tempC->SetMiniGame(tempL);
	tempC->SetIsGame(true);
	temp->AddSkill(tempC);
	temp->SetAttack(20);
	temp->SetMaxHealth(350);
	temp->SetMaxAP(100);
	temp->SetPosX(600);
	temp->SetPosY(250);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(3);
	temp->SetType(OBJ_PLAYER_UNIT);
	temp->SetName("Arin");

	return temp;
}

void CProfileMenuState::ContinueGame( int ID )
{
	string szZone = m_vCharacterList[ID-1]->GetZone() + ".xml";
	CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
	CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[ID-1]);
	for(unsigned int i = 0; i < m_vWorldData[ID-1].size();i++)
		pWorld->AddClear(m_vWorldData[ID-1][i]);

	CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
}

CPlayerUnit* CProfileMenuState::CreateRanger(void)
{
	CPlayerUnit* temp = new CPlayerUnit;
	CCommands* tempC = new CCommands;
	CBasicAttack* tempM = new CBasicAttack;
	CAnimationTimeStamp* pTemp;
	temp->SetClass(UC_RANGER);
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Ranger_Battle_Idle");
	pTemp->SetCurrentFrame(0);
	tempC->SetName("Attack");
	tempM->SetCost(0);
	tempC->SetIsGame(true);
	tempC->SetMiniGame(tempM);
	temp->AddSkill(tempC);

	CCommands* pTest = new CCommands;
	tempC = new CCommands;
	tempC->SetName("Ranger");
	tempC->SetIsGame(false);
	CSteadyShot *pAim = new CSteadyShot;
	pTest->SetName("Aimed Shot");
	pTest->SetMiniGame(pAim);
	pAim->SetDamage(4.0f);
	pAim->SetCost(20);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	CPrecisionStrike *pMulti = new CPrecisionStrike;
	pTest->SetName("Multi-Shot");
	pMulti->SetAOE(true);
	pTest->SetMiniGame(pMulti);
	pMulti->SetDamage(0.75f);
	pMulti->SetCost(15);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);
	temp->AddSkill(tempC);

	tempC = new CCommands;
	CUseItem* tempL = new CUseItem;
	tempL->SetDamageSkill(false);
	tempL->SetCost(0);
	tempC->SetName("Items");
	tempC->SetMiniGame(tempL);
	tempC->SetIsGame(true);
	temp->AddSkill(tempC);
	temp->SetAttack(10);
	temp->SetMaxHealth(120);
	temp->SetMaxAP(120);
	temp->SetPosX(600);
	temp->SetPosY(250);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(3);
	temp->SetType(OBJ_PLAYER_UNIT);
	temp->SetName("Arin");

	return temp;
}

CPlayerUnit* CProfileMenuState::CreateWarrior(void)
{
	CPlayerUnit* temp = new CPlayerUnit;
	CCommands* tempC = new CCommands;
	CBasicAttack* tempM = new CBasicAttack;
	CAnimationTimeStamp* pTemp;
	temp->SetClass(UC_WARRIOR);
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Warrior_Battle_Idle");
	pTemp->SetCurrentFrame(0);
	tempC->SetName("Attack");
	tempM->SetCost(0);
	tempC->SetIsGame(true);
	tempC->SetMiniGame(tempM);
	temp->AddSkill(tempC);
	tempC = new CCommands;

	CCommands* pTest = new CCommands;
	tempC->SetName("Warrior");
	tempC->SetIsGame(false);
	CTriggerSpree *pSpree = new CTriggerSpree;
	pTest->SetName("SwordSlash");
	pSpree->SetCost(15);
	pSpree->SetDamage(0.75f);
	pTest->SetMiniGame(pSpree);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	CComboGame *pCombo = new CComboGame;
	pTest->SetName("Blitz");
	pCombo->SetCost(30);
	pCombo->SetDamage(1.3f);
	pTest->SetMiniGame(pCombo);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);
	temp->AddSkill(tempC);

	tempC = new CCommands;
	CUseItem* tempL = new CUseItem;
	tempL->SetDamageSkill(false);
	tempL->SetCost(0);
	tempC->SetName("Items");
	tempC->SetMiniGame(tempL);
	tempC->SetIsGame(true);
	temp->AddSkill(tempC);
	temp->SetAttack(10);
	temp->SetMaxHealth(150);
	temp->SetMaxAP(100);
	temp->SetPosX(600);
	temp->SetPosY(250);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(3);
	temp->SetType(OBJ_PLAYER_UNIT);
	temp->SetName("Arin");

	return temp;
}

CPlayerUnit* CProfileMenuState::CreateMage(void)
{
	CPlayerUnit* temp = new CPlayerUnit;
	CCommands* tempC = new CCommands;
	CBasicAttack* tempM = new CBasicAttack;
	CAnimationTimeStamp* pTemp;
	temp->SetClass(UC_MAGE);
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Mage_Battle_Idle");
	pTemp->SetCurrentFrame(0);
	tempC->SetName("Attack");
	tempM->SetCost(0);
	tempC->SetIsGame(true);
	tempC->SetMiniGame(tempM);
	temp->AddSkill(tempC);
	tempC = new CCommands;
	tempC->SetName("Mage");
	tempC->SetIsGame(false);

	CCommands* pTest = new CCommands;
	CTriggerMatch *pTrig = new CTriggerMatch;
	pTest->SetName("FireBall");
	CProjectile* pFireBall = new CProjectile();

	pFireBall->SetMasterGame(pTrig);
	pFireBall->GetAnimInfo()->SetAnimation("Fireball_Left");
	pFireBall->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_LargeFireball.wav")));
	pTrig->SetSkill(pFireBall);
	pTrig->SetChances(5);
	pTrig->SetDamage(1.5f);
	pTrig->SetCost(15);
	pTest->SetMiniGame(pTrig);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	CChargeCrystal* pCrystal = new CChargeCrystal;
	pTest->SetName("Icespear");
	CProjectile* pIceSpear = new CProjectile();
	pIceSpear->SetMasterGame(pCrystal);
	pIceSpear->GetAnimInfo()->SetAnimation("Ice_Spear_Left");
	pIceSpear->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_IceSpear.wav")));
	pCrystal->SetSkill(pIceSpear);
	pCrystal->SetDamage(1.5f);
	pCrystal->SetCost(20);
	pTest->SetMiniGame(pCrystal);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	pTrig = new CTriggerMatch;
	pTest->SetName("EarthRip");
	CBuff* pEarthRip = new CBuff();
	pEarthRip->SetMasterGame(pTrig);
	pEarthRip->GetAnimInfo()->SetAnimation("Earth_Rip");
	pEarthRip->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_Earth_Rip.wav")));
	pTrig->SetSkill(pEarthRip);
	pTrig->SetCost(20);
	pTrig->SetChances(3);
	pTrig->SetDamage(1.0f);
	pTrig->SetAOE(true);
	pTest->SetMiniGame(pTrig);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	pCrystal = new CChargeCrystal;
	pCrystal->SetDamageSkill(false);
	pCrystal->SetHeal(true);
	pTest->SetName("Heal");
	CBuff* pHeal = new CBuff();
	pHeal->SetMasterGame(pCrystal);
	pHeal->GetAnimInfo()->SetAnimation("Heal");
	pHeal->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_HealingSpell.wav")));
	pCrystal->SetSkill(pHeal);
	pCrystal->SetCost(25);
	pCrystal->SetDamage(1.5f);
	pTest->SetMiniGame(pCrystal);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	pCrystal = new CChargeCrystal;
	pCrystal->SetDamageSkill(false);
	pCrystal->SetHeal(false);
	pTest->SetName("Meditiate");
	CBuff* pMeditate = new CBuff();
	pMeditate->SetMasterGame(pCrystal);
	pMeditate->GetAnimInfo()->SetAnimation("Meditate");
	pMeditate->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_Med.wav")));
	pCrystal->SetSkill(pMeditate);
	pCrystal->SetCost(0);
	pCrystal->SetDamage(1.5f);
	pTest->SetMiniGame(pCrystal);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	temp->AddSkill(tempC);

	tempC = new CCommands;
	CUseItem* tempL = new CUseItem;
	tempL->SetDamageSkill(false);
	tempL->SetCost(0);
	tempC->SetName("Items");
	tempC->SetMiniGame(tempL);
	tempC->SetIsGame(true);
	temp->AddSkill(tempC);
	temp->SetAttack(10);
	temp->SetMaxHealth(100);
	temp->SetMaxAP(150);
	temp->SetPosX(600);
	temp->SetPosY(250);
	temp->SetVelX(0);
	temp->SetVelY(0);
	temp->SetSpeed(3);
	temp->SetType(OBJ_PLAYER_UNIT);
	temp->SetName("Arin");

	return temp;
}