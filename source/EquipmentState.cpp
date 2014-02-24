#include "EquipmentState.h"
#include "Game.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "../SGD Wrappers/SGD_Math.h"

#include "GamePlayState.h"
#include <cassert>
CEquipmentState* CEquipmentState::GetInstance( void )
{
	static CEquipmentState s_Instance;
	return &s_Instance;
}

CEquipmentState::CEquipmentState(void)
{
	m_nUnusedSlotID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Equipment_Slot_Unused.png"));
	m_nUsedSlotID = CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Equipment_Slot_used.png"));
	SetBackgroundImg(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_EquipmentScreen.png")));
	m_nEquipmentCursorID= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Equipment_Slot_Selection.png"));
	SetCursorIMG(CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/POA_Cursor.png")));
	m_nArmorSelection = 0;
	m_nWeaponSelection =0;
	m_nAugmentSelection = 0;
	m_nItemSelection = 0;
	m_nGearSelection = 0;
	m_bSubMenu = false;
	m_vInventory = nullptr;
	m_pPlayer = nullptr;
	m_nTotalItems = 0;
	m_nHealthBar			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_HealthBar.png"));
	m_nHealthBarPlate		= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_HealthBarPlate.png"));

	m_nWeapon1ID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Sword.png"));
	m_nWeapon2ID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Staff.png"));
	m_nWeapon3ID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Bow.png"));
	m_nArmor1ID				= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Plate.png"));
	m_nArmor2ID				= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Robe.png"));
	m_nArmor3ID				= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Leather.png"));
	m_nAugment1ID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Augment1.png"));
	m_nAugment2ID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Augment2.png"));
	m_nAugment3ID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Augment3.png"));
	m_nAugment4ID			= CSGD_TextureManager::GetInstance()->LoadTexture(_T("Assets/Graphics/Menus/PoA_Augment4.png"));

}

CEquipmentState::~CEquipmentState(void)
{
	Sleep();
}

void CEquipmentState::Activate( void )	
{
	m_bSubMenu = false;
	m_nArmorSelection = 0;
	m_nWeaponSelection =0;
	m_nAugmentSelection = 0;
	m_nItemSelection = 0;

	CUnits* pUnit = CGamePlayState::GetInstance()->GetPlayerUnit();
	if(pUnit->GetType() == OBJ_PLAYER_UNIT)
	{
		m_pPlayer = reinterpret_cast<CPlayerUnit*>(pUnit);
		if(m_pPlayer == nullptr)
			assert(m_pPlayer == nullptr && "Player not set correctly");
		m_vInventory = m_pPlayer->GetInv();
	}

	for(auto i = m_vInventory->begin(); i != m_vInventory->end(); i++)
	{
		if(i->second.Item->GetItemType() == IT_CONSUMABLE)
		{
			m_nTotalItems++;
		}
	}

	string szWeapon = "";
	string szArmor = "";
	string szAugment = "";

	if(m_pPlayer->GetWeapon() != nullptr)
		szWeapon = m_pPlayer->GetWeapon()->GetName();

	if(m_pPlayer->GetArmor() != nullptr)
		szArmor = m_pPlayer->GetArmor()->GetName();

	if(m_pPlayer->GetAugment() != nullptr)
		szAugment = m_pPlayer->GetAugment()->GetName();

	if(szAugment != "")
	{
		if(szAugment == "HP Augment")
			m_nEquippedAugment = 0;
		if(szAugment == "AP Augment")
			m_nEquippedAugment = 1;
		if(szAugment == "Atk Augment")
			m_nEquippedAugment = 2;
		if(szAugment == "Speed Augment")
			m_nEquippedAugment = 3;
	}
	else
		m_nEquippedAugment = -1;

	if(szWeapon != "")
	{
		if(szWeapon == "Sword of Suffering")
			m_nEquippedWeapon = 0;
		if(szWeapon == "Staff of Lucidity")
			m_nEquippedWeapon = 1;
		if(szWeapon == "Bow of the Great Hunt")
			m_nEquippedWeapon = 2;
	}
	else
		m_nEquippedWeapon = -1;
	if(szArmor != "")
	{
		if(szArmor == "Armor of the Ghost Wolf")
			m_nEquippedArmor = 0;
		if(szArmor == "Robes of the Ancient One")
			m_nEquippedArmor = 1;
		if(szArmor == "Vestments of the Savage tribes")
			m_nEquippedArmor = 2;
	}
	else
		m_nEquippedArmor = -1;


}
void CEquipmentState::Sleep( void )		
{
	m_vInventory = nullptr;
	m_pPlayer = nullptr;
	m_nTotalItems = 0;
}			
void CEquipmentState::Update( float fElapsedTime )	
{

}
void CEquipmentState::Render( void )
{
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();


	pTM->Draw(GetBackgroundImg(),0,0);
	CGame::GetInstance()->GetFont("Arial")->Draw(_T("\tChange Equipment\t\t\t\t\tUse Item"),0,64,0.75f,D3DCOLOR_ARGB(255,200,200,0));
	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Weapon"),64 + 128,292,0.75f,D3DCOLOR_ARGB(255,200,200,0));
	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Armor"),64 + 128,360,0.75f,D3DCOLOR_ARGB(255,200,200,0));
	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Augments"),64 + 128,428,0.75f,D3DCOLOR_ARGB(255,200,200,0));

	RECT rTemp = {0,0,16,32};
	if(!m_bSubMenu)
	{
		if(GetCursorSelection() == 0)
			pTM->Draw(GetCursorIMG(),80,68,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		else
			pTM->Draw(GetCursorIMG(),644,68,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
	}
	else
	{
		if(GetCursorSelection() == 0)
			pTM->Draw(GetCursorIMG(),80,68,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
		else
			pTM->Draw(GetCursorIMG(),644,68,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
	}

	RECT rItem = {0,0,64,64};

	if((*m_vInventory)["Sword of Suffering"].Owned > 0)
		pTM->Draw(m_nWeapon1ID, 164 + 128, 268, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nWeapon1ID, 164 + 128, 268, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));


	if((*m_vInventory)["Staff of Lucidity"].Owned > 0)
		pTM->Draw(m_nWeapon2ID, 232 + 128, 268, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nWeapon2ID, 232 + 128, 268, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));

	if((*m_vInventory)["Bow of the Great Hunt"].Owned > 0)
		pTM->Draw(m_nWeapon3ID, 300 + 128, 268, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nWeapon3ID, 300 + 128, 268, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));

	if((*m_vInventory)["Armor of the Ghost Wolf"].Owned > 0)
		pTM->Draw(m_nArmor1ID, 164 + 128, 336, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nArmor1ID, 164 + 128, 336, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));

	if((*m_vInventory)["Robes of the Ancient One"].Owned > 0)
		pTM->Draw(m_nArmor2ID, 232 + 128, 336, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nArmor2ID, 232 + 128, 336, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));

	if((*m_vInventory)["Vestments of the Savage tribes"].Owned > 0)
		pTM->Draw(m_nArmor3ID, 300 + 128, 336, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nArmor3ID, 300 + 128, 336, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));


	if((*m_vInventory)["HP Augment"].Owned > 0)
		pTM->Draw(m_nAugment1ID, 164 + 128, 404, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nAugment1ID, 164 + 128, 404, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));

	if((*m_vInventory)["AP Augment"].Owned > 0)
		pTM->Draw(m_nAugment2ID, 232 + 128, 404, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nAugment2ID, 232 + 128, 404, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));

	if((*m_vInventory)["Atk Augment"].Owned > 0)
		pTM->Draw(m_nAugment3ID, 300 + 128, 404, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nAugment3ID, 300 + 128, 404, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));

	if((*m_vInventory)["Speed Augment"].Owned > 0)
		pTM->Draw(m_nAugment4ID, 368 + 128, 404, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(255,255,255));
	else
		pTM->Draw(m_nAugment4ID, 368 + 128, 404, 1.0f,1.0f,&rItem,0,0,0,D3DCOLOR_XRGB(50,50,50));



	//// Draw All the slots First
	pTM->Draw(m_nUnusedSlotID, 164 + 128, 268);
	pTM->Draw(m_nUnusedSlotID, 232 + 128, 268);
	pTM->Draw(m_nUnusedSlotID, 300 + 128, 268);

	pTM->Draw(m_nUnusedSlotID, 164 + 128, 336);
	pTM->Draw(m_nUnusedSlotID, 232 + 128, 336);
	pTM->Draw(m_nUnusedSlotID, 300 + 128, 336);

	pTM->Draw(m_nUnusedSlotID, 164 + 128, 404);
	pTM->Draw(m_nUnusedSlotID, 232 + 128, 404);
	pTM->Draw(m_nUnusedSlotID, 300 + 128, 404);
	pTM->Draw(m_nUnusedSlotID, 368 + 128, 404);

	////Draw the Cursor
	if(GetCursorSelection() == 0 && m_bSubMenu)
	{
		if(m_nWeaponSelection == 0)
			pTM->Draw(m_nEquipmentCursorID, 164 + 128, 268);
		if(m_nWeaponSelection == 1)
			pTM->Draw(m_nEquipmentCursorID, 232 + 128, 268);
		if(m_nWeaponSelection == 2)
			pTM->Draw(m_nEquipmentCursorID, 300 + 128, 268);
		if(m_nArmorSelection == 0)
			pTM->Draw(m_nEquipmentCursorID, 164 + 128, 336);
		if(m_nArmorSelection == 1)
			pTM->Draw(m_nEquipmentCursorID, 232 + 128, 336);
		if(m_nArmorSelection == 2)
			pTM->Draw(m_nEquipmentCursorID, 300 + 128, 336);
		if(m_nAugmentSelection == 0)
			pTM->Draw(m_nEquipmentCursorID, 164 + 128, 404);
		if(m_nAugmentSelection == 1)
			pTM->Draw(m_nEquipmentCursorID, 232 + 128, 404);
		if(m_nAugmentSelection == 2)
			pTM->Draw(m_nEquipmentCursorID, 300 + 128, 404);
		if(m_nAugmentSelection == 3)
			pTM->Draw(m_nEquipmentCursorID, 368 + 128, 404);

		switch (m_nGearSelection)
		{
		case 0:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),380 + 128,304,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI * 1.5f,D3DCOLOR_ARGB(255,255,255,255));
			break;
		case 1:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),380 + 128,372,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI* 1.5f,D3DCOLOR_ARGB(255,255,255,255));
			break;
		case 2:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),444 + 128,440,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI* 1.5f,D3DCOLOR_ARGB(255,255,255,255));

			break;
		default:
			break;
		}
	}
	else if(m_bSubMenu)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),628,112 + (m_nItemSelection * 16),1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
	}
	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Worn"),108,240,0.75f,D3DCOLOR_ARGB(255,200,200,0));

	switch (m_nEquippedWeapon)
	{
	case 0:
		pTM->Draw(m_nWeapon1ID, 108, 268);
		break;
	case 1:
		pTM->Draw(m_nWeapon2ID, 108, 268);
		break;
	case 2:
		pTM->Draw(m_nWeapon3ID, 108, 268);
		break;
	default:
		break;
	}

	switch (m_nEquippedArmor)
	{
	case 0:
		pTM->Draw(m_nArmor1ID, 108, 336);
		break;
	case 1:
		pTM->Draw(m_nArmor2ID, 108, 336);
		break;
	case 2:
		pTM->Draw(m_nArmor3ID, 108, 336);
		break;
	default:
		break;
	}
	switch (m_nEquippedAugment)
	{
	case 0:
		pTM->Draw(m_nAugment1ID, 108, 404);
		break;
	case 1:
		pTM->Draw(m_nAugment2ID, 108, 404);
		break;
	case 2:
		pTM->Draw(m_nAugment3ID, 108, 404);
		break;
	case 3:
		pTM->Draw(m_nAugment4ID, 108, 404);
		break;
	default:
		break;
	}

	pTM->Draw(m_nUsedSlotID, 108, 268);
	pTM->Draw(m_nUsedSlotID, 108, 336);
	pTM->Draw(m_nUsedSlotID, 108, 404);

	wostringstream woss;
	int nCount = 0;
	for(auto i = m_vInventory->begin(); i != m_vInventory->end(); i++)
	{
		woss.str(_T(""));
		if(i->second.Owned > 0)
		{
			if(i->second.Item->GetItemType() == IT_CONSUMABLE)
			{
				woss << i->second.Item->GetName().c_str() << " x" << i->second.Owned;
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),632,112 + (nCount * 16),0.75f,D3DCOLOR_ARGB(255,200,200,0));
				nCount++;
			}
		}
	}

	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Arin"),84,100,0.75f,D3DCOLOR_ARGB(255,200,200,0));
	float hPercent = m_pPlayer->GetHealth() / float(m_pPlayer->GetMaxHealth());
	RECT rHealth = {0,0,256, 32};
	pTM->Draw(m_nHealthBar, 100,122,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(0,0,0));
	rHealth.right = long(256 * hPercent);
	pTM->Draw(m_nHealthBar, 100,122,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(255,255,255));
	rHealth.right = 256;
	pTM->Draw(m_nHealthBarPlate, 100,122,1.0f,1.0f,&rHealth,0.0f,0.0f,0.0f,D3DCOLOR_XRGB(255,255,255));
	woss.str(_T(""));
	woss << m_pPlayer->GetHealth();
	CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),112,126,0.75f,D3DCOLOR_ARGB(255,0,0,0));
	woss.str(_T(""));
	woss << m_pPlayer->GetAbilityPoints() << " / " << m_pPlayer->GetMaxAP();
	CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),232,134,0.75f,D3DCOLOR_ARGB(255,0,0,0));
	woss.str(_T(""));
	woss <<"Level: " << m_pPlayer->GetLevel() << "\nAttack: " << m_pPlayer->GetAttack() << "\nSpeed: " << m_pPlayer->GetSpeed() << "\nExperience: " << m_pPlayer->GetExperience() << " / " << m_pPlayer->GetLevel() * m_pPlayer->GetLevel() * 100;
	CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),232,150,0.75f,D3DCOLOR_ARGB(255,0,0,0));

	/////////////////////////////////////////////////////////////////////////////
	int nHealthMod, nAPMod, nAttackMod, nSpeedMod;
	nHealthMod = nAPMod = nAttackMod = nSpeedMod = 0;
	CWeapon* pWeapon = nullptr;
	CArmor* pArmor = nullptr;
	CAugment* pAugment = nullptr;
	switch(m_nEquippedWeapon)
	{
	case 0:
		pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Sword of Suffering"].Item);
		break;
	case 1:
		pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Staff of Lucidity"].Item);
		break;
	case 2:
		pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Sword of Suffering"].Item);
		break;
	default:
		break;
	}

	switch(m_nEquippedArmor)
	{
	case 0:
		pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Armor of the Ghost Wolf"].Item);
		break;
	case 1:
		pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Robes of the Ancient One"].Item);
		break;
	case 2:
		pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Vestments of the Savage tribes"].Item);
		break;
	default:
		break;
	}

	switch(m_nEquippedAugment)
	{

	case 0:
		pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["HP Augment"].Item);
		break;
	case 1:
		pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["AP Augment"].Item);
		break;
	case 2:
		pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["Atk Augment"].Item);
		break;
	case 3:
		pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["Speed Augment"].Item);
		break;
	default:
		break;
	}

	CWeapon* pLWeapon = nullptr;
	CArmor* pLArmor = nullptr;
	CAugment* pLAugment = nullptr;

	switch(m_nWeaponSelection)
	{
	case 0:
		pLWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Sword of Suffering"].Item);
		break;
	case 1:
		pLWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Staff of Lucidity"].Item);
		break;
	case 2:
		pLWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Sword of Suffering"].Item);
		break;
	default:
		break;
	}

	switch(m_nArmorSelection)
	{
	case 0:
		pLArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Armor of the Ghost Wolf"].Item);
		break;
	case 1:
		pLArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Robes of the Ancient One"].Item);
		break;
	case 2:
		pLArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Vestments of the Savage tribes"].Item);
		break;
	default:
		break;
	}

	switch(m_nAugmentSelection)
	{

	case 0:
		pLAugment = reinterpret_cast<CAugment*>((*m_vInventory)["HP Augment"].Item);
		break;
	case 1:
		pLAugment = reinterpret_cast<CAugment*>((*m_vInventory)["AP Augment"].Item);
		break;
	case 2:
		pLAugment = reinterpret_cast<CAugment*>((*m_vInventory)["Atk Augment"].Item);
		break;
	case 3:
		pLAugment = reinterpret_cast<CAugment*>((*m_vInventory)["Speed Augment"].Item);
		break;
	default:
		break;
	}
	//////////////////////////////////////////////////////////////////////////////

	if(pWeapon != nullptr)
		nAttackMod -= (int)pWeapon->GetAttack();

	if(pArmor != nullptr)
	{
		nSpeedMod -=  (int)pArmor->GetSpeedStat();
		nHealthMod -= (int)pArmor->GetHpStat();
		nAttackMod -= (int)pArmor->GetAttkStat();

	}
	if(pAugment != nullptr)
	{
		if(pAugment->GetAugType() == "HP")
			nHealthMod -= (int)pAugment->GetEffect();
		else if(pAugment->GetAugType() == "ATTK")
			nAttackMod -= (int)pAugment->GetEffect();
		else if(pAugment->GetAugType() == "AP")
			nAPMod -= (int)pAugment->GetEffect();
		else if(pAugment->GetAugType() == "SPEED")
			nSpeedMod -= (int)pAugment->GetEffect();
	}

	if(pLWeapon != nullptr)
		nAttackMod += (int)pLWeapon->GetAttack();

	if(pLArmor != nullptr)
	{
		nSpeedMod +=  (int)pLArmor->GetSpeedStat();
		nHealthMod += (int)pLArmor->GetHpStat();
		nAttackMod += (int)pLArmor->GetAttkStat();

	}
	if(pLAugment != nullptr)
	{
		if(pLAugment->GetAugType() == "HP")
			nHealthMod += (int)pLAugment->GetEffect();
		else if(pLAugment->GetAugType() == "ATTK")
			nAttackMod += (int)pLAugment->GetEffect();
		else if(pLAugment->GetAugType() == "AP")
			nAPMod += (int)pLAugment->GetEffect();
		else if(pLAugment->GetAugType() == "SPEED")
			nSpeedMod += (int)pLAugment->GetEffect();
	}
	if(m_bSubMenu && GetCursorSelection() == 0)
	{
		//////////////////////////////////////////////////////////////////////////////
		woss.str(_T(""));
		if(nHealthMod > 0)
			woss << "+";
		woss << nHealthMod;
		if(nHealthMod != 0)
		{
			if(nHealthMod > 0)
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),168,126,0.75f,D3DCOLOR_ARGB(255,0,255,0));
			else 
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),168,126,0.75f,D3DCOLOR_ARGB(255,255,0,0));
		}

		woss.str(_T(""));
		if(nAPMod > 0)
			woss << "+";
		woss << nAPMod;
		if(nAPMod != 0)
		{
			if(nAPMod > 0)
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),332,134,0.75f,D3DCOLOR_ARGB(255,0,255,0));
			else
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),332,134,0.75f,D3DCOLOR_ARGB(255,255,0,0));
		}


		woss.str(_T(""));
		woss << "\n ";
		if(nAttackMod > 0)
			woss << "+";
		woss << nAttackMod;

		if(nAttackMod != 0)
		{
			if(nAttackMod > 0)
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),332,150,0.75f,D3DCOLOR_ARGB(255,0,255,0));
			else
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),332,150,0.75f,D3DCOLOR_ARGB(255,255,0,0));
		}
		woss.str(_T(""));
		woss << "\n\n " ;
		if(nSpeedMod > 0)
			woss << "+";
		woss << nSpeedMod;
		if(nSpeedMod != 0)
		{
			if(nSpeedMod > 0)
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),332,150,0.75f,D3DCOLOR_ARGB(255,0,255,0));
			else
				CGame::GetInstance()->GetFont("Arial")->Draw(woss.str().c_str(),332,150,0.75f,D3DCOLOR_ARGB(255,255,0,0));
		}
	}

}	

bool CEquipmentState::Input( void )	
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE) || pDI->JoystickButtonPressed(2))
	{
		if(!m_bSubMenu)
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		else
			m_bSubMenu = false;
	}
	if(pDI->KeyPressed(DIK_W) || pDI->KeyPressed(DIK_UPARROW) || pDI->JoystickDPadPressed(DIR_UP) || pDI->JoystickGetLStickDirPressed(DIR_UP))
	{
		if(m_bSubMenu)
		{
			if(GetCursorSelection() == 0)
			{
				m_nGearSelection--;
				if(m_nGearSelection <0)
					m_nGearSelection = 0;
			}
			else
			{
				m_nItemSelection--;
				if(m_nItemSelection < 0)
					m_nItemSelection = 0;
			}
		}
	}
	if(pDI->KeyPressed(DIK_S) || pDI->KeyPressed(DIK_DOWNARROW) || pDI->JoystickDPadPressed(DIR_DOWN) || pDI->JoystickGetLStickDirPressed(DIR_DOWN))
	{

		if(m_bSubMenu)
		{
			if(GetCursorSelection() == 0)
			{
				m_nGearSelection++;
				if(m_nGearSelection > 2)
					m_nGearSelection = 2;
			}
			else
			{
				m_nItemSelection++;
				if(m_nItemSelection > m_nTotalItems -1)
					m_nItemSelection = m_nTotalItems -1;
			}
		}
	}
	if(pDI->KeyPressed(DIK_A) || pDI->KeyPressed(DIK_LEFTARROW) || pDI->JoystickDPadPressed(DIR_LEFT) || pDI->JoystickGetLStickDirPressed(DIR_LEFT))
	{

		if(!m_bSubMenu)
		{
			if(GetCursorSelection() != 0)
				SetCursorSelection(0);
		}
		else
		{
			if(GetCursorSelection() == 0)
			{
				switch (m_nGearSelection)
				{
				case 0:
					{
						m_nWeaponSelection--;
						if(m_nWeaponSelection <0)
							m_nWeaponSelection = 0;
					}
					break;
				case 1:
					{
						m_nArmorSelection--;
						if(m_nArmorSelection <0)
							m_nArmorSelection = 0;
					}
					break;
				case 2:
					{
						m_nAugmentSelection--;
						if(m_nAugmentSelection <0)
							m_nAugmentSelection = 0;
					}
					break;
				default:
					break;
				}
			}
		}

	}
	if(pDI->KeyPressed(DIK_D) || pDI->KeyPressed(DIK_RIGHTARROW) || pDI->JoystickDPadPressed(DIR_RIGHT) || pDI->JoystickGetLStickDirPressed(DIR_RIGHT))
	{
		if(!m_bSubMenu)
		{
			if(GetCursorSelection() != 1)
				SetCursorSelection(1);
		}
		else
		{
			if(GetCursorSelection() == 0)
			{
				switch (m_nGearSelection)
				{
				case 0:
					{
						m_nWeaponSelection++;
						if(m_nWeaponSelection >2)
							m_nWeaponSelection = 2;
					}
					break;
				case 1:
					{
						m_nArmorSelection++;
						if(m_nArmorSelection >2)
							m_nArmorSelection = 2;
					}
					break;
				case 2:
					{
						m_nAugmentSelection++;
						if(m_nAugmentSelection >3)
							m_nAugmentSelection = 3;
					}
					break;
				default:
					break;
				}
			}
		}
	}

	if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(1))
	{
		if(!m_bSubMenu)
		{
			if((GetCursorSelection() == 1 && m_nTotalItems > 0) || GetCursorSelection() == 0)
				m_bSubMenu = true;
		}
		else
		{
			if(GetCursorSelection() == 0)
			{
				switch(m_nGearSelection)
				{
				case 0:
					{
						if(m_nWeaponSelection == 0)
						{
							if((*m_vInventory)["Sword of Suffering"].Owned > 0)
							{
								if(m_pPlayer->GetWeapon() != nullptr)
								{
									if(m_pPlayer->GetWeapon()->GetName() == "Sword of Suffering")
										m_nEquippedWeapon = -1;
									else
										m_nEquippedWeapon = m_nWeaponSelection;
									CWeapon* pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Sword of Suffering"].Item);
									if(pWeapon != nullptr)
										m_pPlayer->EquipWeapon(pWeapon);
								}
								else
								{
									m_nEquippedWeapon = m_nWeaponSelection;
									CWeapon* pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Sword of Suffering"].Item);
									if(pWeapon != nullptr)
										m_pPlayer->EquipWeapon(pWeapon);
								}
							}

						}
						else if(m_nWeaponSelection == 1)
						{
							if((*m_vInventory)["Staff of Lucidity"].Owned > 0)
							{
								if(m_pPlayer->GetWeapon() != nullptr)
								{
									if(m_pPlayer->GetWeapon()->GetName() == "Staff of Lucidity")
										m_nEquippedWeapon = -1;
									else
										m_nEquippedWeapon = m_nWeaponSelection;
									CWeapon* pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Staff of Lucidity"].Item);
									if(pWeapon != nullptr)
										m_pPlayer->EquipWeapon(pWeapon);
								}
								else
								{
									m_nEquippedWeapon = m_nWeaponSelection;
									CWeapon* pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Staff of Lucidity"].Item);
									if(pWeapon != nullptr)
										m_pPlayer->EquipWeapon(pWeapon);
								}
							}
						}
						else if(m_nWeaponSelection == 2)
						{
							if((*m_vInventory)["Bow of the Great Hunt"].Owned > 0)
							{
								if(m_pPlayer->GetWeapon() != nullptr)
								{
									if(m_pPlayer->GetWeapon()->GetName() == "Bow of the Great Hunt")
										m_nEquippedWeapon = -1;
									else
										m_nEquippedWeapon = m_nWeaponSelection;
									CWeapon* pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Bow of the Great Hunt"].Item);
									if(pWeapon != nullptr)
										m_pPlayer->EquipWeapon(pWeapon);
								}
								else
								{
									m_nEquippedWeapon = m_nWeaponSelection;
									CWeapon* pWeapon = reinterpret_cast<CWeapon*>((*m_vInventory)["Bow of the Great Hunt"].Item);
									if(pWeapon != nullptr)
										m_pPlayer->EquipWeapon(pWeapon);
								}
							}
						}
					}
					break;
				case 1:
					{
						if(m_nArmorSelection == 0)
						{
							if((*m_vInventory)["Armor of the Ghost Wolf"].Owned > 0)
							{
								if(m_pPlayer->GetArmor() != nullptr)
								{
									if(m_pPlayer->GetArmor()->GetName() == "Armor of the Ghost Wolf")
										m_nEquippedArmor = -1;
									else
										m_nEquippedArmor = m_nArmorSelection;
									CArmor* pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Armor of the Ghost Wolf"].Item);
									if(pArmor != nullptr)
										m_pPlayer->EquipArmor(pArmor);
								}
								else
								{
									m_nEquippedArmor = m_nArmorSelection;
									CArmor* pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Armor of the Ghost Wolf"].Item);
									if(pArmor != nullptr)
										m_pPlayer->EquipArmor(pArmor);
								}
							}

						}
						else if(m_nArmorSelection == 1)
						{
							if((*m_vInventory)["Robes of the Ancient One"].Owned > 0)
							{
								if(m_pPlayer->GetArmor() != nullptr)
								{
									if(m_pPlayer->GetArmor()->GetName() == "Robes of the Ancient One")
										m_nEquippedArmor = -1;
									else
										m_nEquippedArmor = m_nArmorSelection;
									CArmor* pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Robes of the Ancient One"].Item);
									if(pArmor != nullptr)
										m_pPlayer->EquipArmor(pArmor);
								}
								else
								{
									m_nEquippedArmor = m_nArmorSelection;
									CArmor* pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Robes of the Ancient One"].Item);
									if(pArmor != nullptr)
										m_pPlayer->EquipArmor(pArmor);
								}
							}
						}
						else if(m_nArmorSelection == 2)
						{
							if((*m_vInventory)["Vestments of the Savage tribes"].Owned > 0)
							{
								if(m_pPlayer->GetArmor() != nullptr)
								{
									if(m_pPlayer->GetArmor()->GetName() == "Vestments of the Savage tribes")
										m_nEquippedArmor = -1;
									else
										m_nEquippedArmor = m_nArmorSelection;
									CArmor* pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Vestments of the Savage tribes"].Item);
									if(pArmor != nullptr)
										m_pPlayer->EquipArmor(pArmor);
								}
								else
								{
									m_nEquippedArmor = m_nArmorSelection;
									CArmor* pArmor = reinterpret_cast<CArmor*>((*m_vInventory)["Vestments of the Savage tribes"].Item);
									if(pArmor != nullptr)
										m_pPlayer->EquipArmor(pArmor);
								}
							}
						}
					}
					break;
				case 2:
					{
						if(m_nAugmentSelection == 0)
						{
							if((*m_vInventory)["HP Augment"].Owned > 0)
							{
								if(m_pPlayer->GetAugment() != nullptr)
								{
									if(m_pPlayer->GetAugment()->GetName() == "HP Augment")
										m_nEquippedAugment = -1;
									else
										m_nEquippedAugment = m_nAugmentSelection;
									CAugment* pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["HP Augment"].Item);
									if(pAugment != nullptr)
										m_pPlayer->EquipAugment(pAugment);
								}
								else
								{
									m_nEquippedAugment = m_nAugmentSelection;
									CAugment* pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["HP Augment"].Item);
									if(pAugment != nullptr)
										m_pPlayer->EquipAugment(pAugment);
								}
							}

						}
						else if(m_nAugmentSelection == 1)
						{
							if((*m_vInventory)["AP Augment"].Owned > 0)
							{
								if(m_pPlayer->GetAugment() != nullptr)
								{
									if(m_pPlayer->GetAugment()->GetName() == "AP Augment")
										m_nEquippedAugment = -1;
									else
										m_nEquippedAugment = m_nAugmentSelection;
									CAugment* pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["AP Augment"].Item);
									if(pAugment != nullptr)
										m_pPlayer->EquipAugment(pAugment);
								}
								else
								{
									m_nEquippedAugment = m_nAugmentSelection;
									CAugment* pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["AP Augment"].Item);
									if(pAugment != nullptr)
										m_pPlayer->EquipAugment(pAugment);
								}
							}
						}
						else if(m_nAugmentSelection == 2)
						{
							if((*m_vInventory)["Atk Augment"].Owned > 0)
							{
								if(m_pPlayer->GetAugment() != nullptr)
								{
									if(m_pPlayer->GetAugment()->GetName() == "Atk Augment")
										m_nEquippedAugment = -1;
									else
										m_nEquippedAugment = m_nAugmentSelection;
									CAugment* pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["Atk Augment"].Item);
									if(pAugment != nullptr)
										m_pPlayer->EquipAugment(pAugment);
								}
								else
								{
									m_nEquippedAugment = m_nAugmentSelection;
									CAugment* pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["Atk Augment"].Item);
									if(pAugment != nullptr)
										m_pPlayer->EquipAugment(pAugment);
								}
							}
						}
						else if(m_nAugmentSelection == 3)
						{
							if((*m_vInventory)["Speed Augment"].Owned > 0)
							{
								if(m_pPlayer->GetAugment() != nullptr)
								{
									if(m_pPlayer->GetAugment()->GetName() == "Speed Augment")
										m_nEquippedAugment = -1;
									else
										m_nEquippedAugment = m_nAugmentSelection;
									CAugment* pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["Speed Augment"].Item);
									if(pAugment != nullptr)
										m_pPlayer->EquipAugment(pAugment);
								}
								else
								{
									m_nEquippedAugment = m_nAugmentSelection;
									CAugment* pAugment = reinterpret_cast<CAugment*>((*m_vInventory)["Speed Augment"].Item);
									if(pAugment != nullptr)
										m_pPlayer->EquipAugment(pAugment);
								}
							}
						}
					}
					break;
				default:
					break;
				}
			}
			else
			{
				int nID = 0;
				for(auto i = m_vInventory->begin(); i != m_vInventory->end(); i++)
				{
					if(i->second.Item->GetItemType() == IT_CONSUMABLE)
					{
						if(nID == m_nItemSelection)
						{
							CConsumable* ItemTemp = reinterpret_cast<CConsumable*>(i->second.Item);
							if(ItemTemp != nullptr)
							{
								if(i->second.Owned > 0)
								{
									if(ItemTemp->GetType() == "HP")
										m_pPlayer->ModifyHealth(-ItemTemp->GetAmount(), false, true);

									else if(ItemTemp->GetType() == "MP")
										m_pPlayer->ModifyAP(-ItemTemp->GetAmount(), true);

									if(i->second.Item != nullptr)
									{
										if(i->second.Item->GetItemType() == IT_CONSUMABLE)
										{
											CConsumable* pTemp = reinterpret_cast<CConsumable*>(i->second.Item);
											if(pTemp != nullptr)
											{
												m_pPlayer->RemoveConsumableItem(pTemp);
												if(i->second.Owned <= 0)
													m_nTotalItems--;
												if(m_nTotalItems <= 0)
													m_bSubMenu = false;
												else
												{
													if(m_nItemSelection >= m_nTotalItems)
														m_nItemSelection = m_nTotalItems -1;
												}
												break;
											}
										}
									}
								}
							}
						}
						else
							nID++;
					}
				}
			}
		}
	}
	return true;
}	