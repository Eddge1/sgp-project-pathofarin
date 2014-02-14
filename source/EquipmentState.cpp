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
		if(i->second.Owned > 0)
		{
			if(i->second.Item->GetItemType() == IT_CONSUMABLE)
			{
				m_nTotalItems++;
			}
			else if(i->second.Item->GetItemType() == IT_WEAPON)
			{
				if(i->second.Item->GetName() == "")
				{

				}
				else if(i->second.Item->GetName() == "")
				{

				}
				else if(i->second.Item->GetName() == "")
				{

				}
			}
			else if(i->second.Item->GetItemType() == IT_ARMOR)
			{


			}
			else if(i->second.Item->GetItemType() == IT_AUGMENT)
			{


			}
		}
	}

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
	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Weapon"),64,292,0.75f,D3DCOLOR_ARGB(255,200,200,0));
	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Armor"),64,360,0.75f,D3DCOLOR_ARGB(255,200,200,0));
	CGame::GetInstance()->GetFont("Arial")->Draw(_T("Augments"),64,428,0.75f,D3DCOLOR_ARGB(255,200,200,0));

	RECT rTemp = {0,0,16,32};
	if(!m_bSubMenu)
	{
		if(GetCursorSelection() == 0)
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),80,68,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),644,68,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
	}
	else
	{
		if(GetCursorSelection() == 0)
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),80,68,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
		else
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),644,68,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(127,50,50,50));
	}



	//// Draw All the slots First
	pTM->Draw(m_nUnusedSlotID, 164, 268);
	pTM->Draw(m_nUnusedSlotID, 232, 268);
	pTM->Draw(m_nUnusedSlotID, 300, 268);

	pTM->Draw(m_nUnusedSlotID, 164, 336);
	pTM->Draw(m_nUnusedSlotID, 232, 336);
	pTM->Draw(m_nUnusedSlotID, 300, 336);


	pTM->Draw(m_nUnusedSlotID, 164, 404);
	pTM->Draw(m_nUnusedSlotID, 232, 404);
	pTM->Draw(m_nUnusedSlotID, 300, 404);
	pTM->Draw(m_nUnusedSlotID, 368, 404);

	////Draw All the Equipped Items


	////Draw the Cursor
	if(GetCursorSelection() == 0 && m_bSubMenu)
	{
		if(m_nWeaponSelection == 0)
			pTM->Draw(m_nEquipmentCursorID, 164, 268);
		if(m_nWeaponSelection == 1)
			pTM->Draw(m_nEquipmentCursorID, 232, 268);
		if(m_nWeaponSelection == 2)
			pTM->Draw(m_nEquipmentCursorID, 300, 268);
		if(m_nArmorSelection == 0)
			pTM->Draw(m_nEquipmentCursorID, 164, 336);
		if(m_nArmorSelection == 1)
			pTM->Draw(m_nEquipmentCursorID, 232, 336);
		if(m_nArmorSelection == 2)
			pTM->Draw(m_nEquipmentCursorID, 300, 336);
		if(m_nAugmentSelection == 0)
			pTM->Draw(m_nEquipmentCursorID, 164, 404);
		if(m_nAugmentSelection == 1)
			pTM->Draw(m_nEquipmentCursorID, 232, 404);
		if(m_nAugmentSelection == 2)
			pTM->Draw(m_nEquipmentCursorID, 300, 404);
		if(m_nAugmentSelection == 3)
			pTM->Draw(m_nEquipmentCursorID, 368, 404);

		switch (m_nGearSelection)
		{
		case 0:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),380,304,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI * 1.5f,D3DCOLOR_ARGB(255,255,255,255));
			break;
		case 1:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),380,372,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI* 1.5f,D3DCOLOR_ARGB(255,255,255,255));
			break;
		case 2:
			CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),444,440,1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI* 1.5f,D3DCOLOR_ARGB(255,255,255,255));

			break;
		default:
			break;
		}
	}
	else if(m_bSubMenu)
	{
		CSGD_TextureManager::GetInstance()->Draw(GetCursorIMG(),628,112 + (m_nItemSelection * 16),1.0f,1.0f,&rTemp,0.0f,0.0f,D3DX_PI/2,D3DCOLOR_ARGB(255,255,255,255));
	}
	wostringstream woss;
	int nCount = 0;
	for(auto i = m_vInventory->begin(); i != m_vInventory->end(); i++)
	{
		woss.str(_T(""));
		if(i->second.Owned > 0)
		{
			if(i->second.Item->GetItemType() == IT_CONSUMABLE)
			{
				woss << i->second.Item->GetName().c_str() << "\tx" << i->second.Owned;
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


}		
bool CEquipmentState::Input( void )	
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
	{
		if(!m_bSubMenu)
			CGame::GetInstance()->ChangeState(CGamePlayState::GetInstance());
		else
			m_bSubMenu = false;
	}
	if(pDI->KeyPressed(DIK_W) || pDI->KeyPressed(DIK_UPARROW))
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
	if(pDI->KeyPressed(DIK_S) || pDI->KeyPressed(DIK_DOWNARROW))
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
	if(pDI->KeyPressed(DIK_A) || pDI->KeyPressed(DIK_LEFTARROW))
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
	if(pDI->KeyPressed(DIK_D) || pDI->KeyPressed(DIK_RIGHTARROW))
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

	if(pDI->KeyPressed(DIK_RETURN))
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

					break;
				case 1:

					break;
				case 2:

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