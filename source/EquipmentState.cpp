#include "EquipmentState.h"
#include "Game.h"
#include "../SGD Wrappers/CSGD_Direct3D.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "../SGD Wrappers/SGD_Math.h"

CEquipmentState* CEquipmentState::GetInstance( void )
{
	static CEquipmentState s_Instance;
	return &s_Instance;
}

CEquipmentState::CEquipmentState(void)
{
	m_pPlayer = nullptr;
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
}
void CEquipmentState::Sleep( void )		
{

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

}		
bool CEquipmentState::Input( void )	
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();

	if(pDI->KeyPressed(DIK_ESCAPE))
	{
		if(!m_bSubMenu)
		{


		}
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
			m_bSubMenu = true;
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


			}
		}
	}

	return true;
}	