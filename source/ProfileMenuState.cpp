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
	SetBackgroundImg(-1);
	SetBackgroundMusic(-1);
	SetSFXID(-1);
	SetCursorIMG(-1);
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
	SetSFXID(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/SFX/POA_CursorSFX.wav")));
	SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_logo.png")));
	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));

	m_bLeft = false;
	m_fOffSetX = 0.0f;
	m_fPosY = 172.0f;
}

void CProfileMenuState::Sleep()
{
	if(GetBackgroundImg() != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(GetBackgroundImg());
	if(GetCursorIMG() != -1)
		CSGD_TextureManager::GetInstance()->UnloadTexture(GetCursorIMG());
	if(GetSFXID() != -1)
		CSGD_XAudio2::GetInstance()->SFXUnloadSound(GetSFXID());
	SetSFXID(-1);
	SetBackgroundImg(-1);
	SetCursorIMG(-1);

	for(unsigned int i = 0; i < m_vCharacterList.size(); i++)
		m_vCharacterList[i]->Release();

	m_vCharacterList.clear();
	m_vWorldData.clear();
}

bool CProfileMenuState::Input()
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(m_fPosY <= 0.0f)
	{
		if(pDI->KeyPressed(DIK_ESCAPE))
			CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
		if(pDI->KeyPressed(DIK_W) || pDI->JoystickDPadPressed(DIR_UP))
		{
			if(GetCursorSelection() <= 0)
				SetCursorSelection(5);
			else
				SetCursorSelection(GetCursorSelection() - 1);
			if(CSGD_XAudio2::GetInstance()->SFXIsSoundPlaying(GetSFXID()) == false)
				CSGD_XAudio2::GetInstance()->SFXPlaySound(GetSFXID());
		}
		else if(pDI->KeyPressed(DIK_S) || pDI->JoystickDPadPressed(DIR_DOWN))
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
					m_vCharacterList[0]->Release();
					m_vCharacterList[0] = nullptr;
					m_vCharacterList[0] = CreatePlayer();
					m_vCharacterList[0]->GetUnit()->SetName("Empty");
					CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[0]);
					SaveGame("Player1.xml");
					m_vWorldData[0].clear();

				}
				else if(m_eCurrState == PS_NEWGAME)
				{
					m_vCharacterList[0]->Release();
					m_vCharacterList[0] = nullptr;
					m_vCharacterList[0] = CreatePlayer();
					CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[0]);
					SaveGame("Player1.xml");
					m_vWorldData[0].clear();

				}
				else
				{
					if(m_vCharacterList[0]->GetUnit()->GetName() == "Empty")
					{
						m_vCharacterList[0]->GetUnit()->SetName("Arin");
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[0]);
						SaveGame("Player1.xml");
					}
					else
					{
						string szZone = m_vCharacterList[0]->GetZone() + ".xml";
						CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[0]);
						for(unsigned int i = 0; i < m_vWorldData[0].size();i++)
							pWorld->AddClear(m_vWorldData[0][i]);
					}
					CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
				}
				m_eCurrState = PS_SELECT;

				break;
			case 2:
				if(m_eCurrState == PS_DELETE)
				{
					m_vCharacterList[1]->Release();
					m_vCharacterList[1] = nullptr;
					m_vCharacterList[1] = CreatePlayer();
					m_vCharacterList[1]->GetUnit()->SetName("Empty");
					CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[1]);
					SaveGame("Player2.xml");
					m_vWorldData[1].clear();
					m_eCurrState = PS_SELECT;

				}
				else if(m_eCurrState == PS_NEWGAME)
				{
					m_vCharacterList[1]->Release();
					m_vCharacterList[1] = nullptr;
					m_vCharacterList[1] = CreatePlayer();
					CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[1]);
					SaveGame("Player2.xml");
					m_vWorldData[1].clear();

				}
				else
				{
					if(m_vCharacterList[1]->GetUnit()->GetName() == "Empty")
					{
						m_vCharacterList[1]->GetUnit()->SetName("Arin");
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[1]);
						SaveGame("Player2.xml");

					}
					else
					{
						string szZone = m_vCharacterList[1]->GetZone() + ".xml";
						CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[1]);
						for(unsigned int i = 0; i < m_vWorldData[1].size();i++)
							pWorld->AddClear(m_vWorldData[1][i]);
					}
					CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());

				}
				m_eCurrState = PS_SELECT;

				break;
			case 3:
				if(m_eCurrState == PS_DELETE)
				{
					m_vCharacterList[2]->Release();
					m_vCharacterList[2] = nullptr;
					m_vCharacterList[2] = CreatePlayer();
					m_vCharacterList[2]->GetUnit()->SetName("Empty");
					CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[2]);
					SaveGame("Player3.xml");
					m_vWorldData[2].clear();

					m_eCurrState = PS_SELECT;
				}
				else if(m_eCurrState == PS_NEWGAME)
				{
					m_vCharacterList[2];
					m_vCharacterList[2] = CreatePlayer();
					CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[2]);
					SaveGame("Player3.xml");
					m_vWorldData[2].clear();

				}
				else
				{
					if(m_vCharacterList[2]->GetUnit()->GetName() == "Empty")
					{
						m_vCharacterList[2]->GetUnit()->SetName("Arin");
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[2]);
						SaveGame("Player3.xml");
					}
					else
					{
						string szZone = m_vCharacterList[2]->GetZone() + ".xml";
						CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
						CGamePlayState::GetInstance()->SetPlayer(m_vCharacterList[2]);
						for(unsigned int i = 0; i < m_vWorldData[2].size();i++)
							pWorld->AddClear(m_vWorldData[2][i]);
					}
					CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
				}
				m_eCurrState = PS_SELECT;
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
		pSlot->SetAttribute("Zone", "testing");
		string szZone = "testing.xml";
		CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
		pRoot->LinkEndChild(pSlot);
		pRoot->LinkEndChild(pWorldData);

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

		m_vCharacterList.push_back(pPlayer);
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
		pSlot->SetAttribute("Class", 0);
		pSlot->SetAttribute("posX", int(pTemp->GetPosX()));
		pSlot->SetAttribute("posY", int(pTemp->GetPosY()));
		pSlot->SetAttribute("Zone", pTemp->GetZone().c_str());


		pTemp->SetName(szFileName);
		string szZone = pTemp->GetZone();
		szZone += ".xml";
		CWorld* pWorld = CGamePlayState::GetInstance()->GetWorld(szZone);
		vector<int>& vTemp = pWorld->GetClearedNpcs();
		TiXmlElement* pNPCid;
		for(unsigned int i = 0; i < vTemp.size(); i++)
		{
			pNPCid = new TiXmlElement("NPC");
			pNPCid->SetAttribute("ID",vTemp[i]);
			pWorldData->LinkEndChild(pNPCid);
		}

	}
	pRoot->LinkEndChild(pSlot);
	pRoot->LinkEndChild(pWorldData);
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
	temp->SetZone("testing");
	pTemp->SetCurrentFrame(0);
	CPlayerUnit* pUnit = CreateTempPlayer();
	temp->SetUnit(pUnit);
	pUnit->Release();
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
	pTemp = temp->GetAnimInfo();
	pTemp->SetAnimation("Warrior_Battle_Idle");
	pTemp->SetCurrentFrame(0);
	tempC->SetName("Attack");
	tempC->SetMiniGame(tempM);
	temp->AddSkill(tempC);
	tempC = new CCommands;
	tempC->SetName("Spells");
	tempC->SetIsGame(false);
	CCommands* pTest = new CCommands;
	CTriggerSpree *pSpree = new CTriggerSpree;
	pTest->SetName("SwordSlash");
	pTest->SetMiniGame(pSpree);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	CComboGame *pCombo = new CComboGame;
	pTest->SetName("Blitz");
	pTest->SetMiniGame(pCombo);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	CTriggerMatch *pTrig = new CTriggerMatch;
	pTest->SetName("FireBall");
	CProjectile* pFireBall = new CProjectile();

	pFireBall->SetMasterGame(pTrig);
	pFireBall->GetAnimInfo()->SetAnimation("Fireball_Left");
	pFireBall->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_LargeFireball.wav")));
	pTrig->SetSkill(pFireBall);
	pTest->SetMiniGame(pTrig);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	pTrig = new CTriggerMatch;
	pTest->SetName("Icespear");
	CProjectile* pIceSpear = new CProjectile();
	pIceSpear->SetMasterGame(pTrig);
	pIceSpear->GetAnimInfo()->SetAnimation("Ice_Spear_Left");
	pIceSpear->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_IceSpear.wav")));
	pTrig->SetSkill(pIceSpear);
	pTest->SetMiniGame(pTrig);
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
	pTrig->SetAOE(true);
	pTest->SetMiniGame(pTrig);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	CChargeCrystal* pCrystal = new CChargeCrystal;
	pCrystal->SetDamageSkill(false);
	pCrystal->SetHeal(true);
	pTest->SetName("Heal");
	CBuff* pHeal = new CBuff();
	pHeal->SetMasterGame(pTrig);
	pHeal->GetAnimInfo()->SetAnimation("Heal");
	pHeal->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_HealingSpell.wav")));
	pCrystal->SetSkill(pHeal);
	pCrystal->SetCost(20);
	pTest->SetMiniGame(pCrystal);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	pTest = new CCommands;
	pCrystal = new CChargeCrystal;
	pCrystal->SetDamageSkill(false);
	pCrystal->SetHeal(false);
	pTest->SetName("Meditiate");
	CBuff* pMeditate = new CBuff();
	pMeditate->SetMasterGame(pTrig);
	pMeditate->GetAnimInfo()->SetAnimation("Meditate");
	pMeditate->SetAudio(CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("Assets/Audio/Spells/POA_Med.wav")));
	pCrystal->SetSkill(pMeditate);
	pCrystal->SetCost(5);
	pTest->SetMiniGame(pCrystal);
	pTest->SetIsGame(true);
	tempC->AddCommands(pTest);

	temp->AddSkill(tempC);
	tempC = new CCommands;
	CUseItem* tempL = new CUseItem;
	tempC->SetName("Items");
	tempC->SetMiniGame(tempL);
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
