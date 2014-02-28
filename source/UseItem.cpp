#include "UseItem.h"
#include "BitmapFont.h"
#include "PlayerUnit.h"
#include "Game.h"
#include <sstream>
using namespace std;

CUseItem::CUseItem(void)
{
	m_bGetInventory = false;
	m_mTemp = nullptr;
	m_nSelection = 0;
	m_nItemTotal = 0;
	m_bFirstDone = false;
}


CUseItem::~CUseItem(void)
{

}


void CUseItem::Update(float fElapsedTime)
{
	CPlayerUnit* tempP = reinterpret_cast<CPlayerUnit*>(GetOwner());
	if(tempP != nullptr)
	{
		//////////// BUG FIX FOR ITEM USE HAVING TO HIT ENTER MULTIPLE TIMES
		if(!m_bFirstDone)
		{
			if(!m_bGetInventory)
			{
				m_mTemp = GetOwner()->GetInv();
			}
			if(m_mTemp != nullptr)
			{
				for(auto i = m_mTemp->begin(); i != m_mTemp->end(); i++)
				{
					if(i->second.Item != nullptr)
					{
						if(i->second.Item->GetItemType() == IT_CONSUMABLE)
						{
							m_nItemTotal++;
						}
					}
					m_bFirstDone = true;
				}
			}
		}
		/////////////////////////////////////////////////////////////////

		if(m_bFirstDone && m_nItemTotal < 1)
		{
			ResetSkill();
			tempP->SetReady(false);
			tempP->SetCasting(false);
		}

		CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
		if(pDI->KeyPressed(DIK_ESCAPE)|| CSGD_DirectInput::GetInstance()->JoystickButtonPressed(1))
		{
			ResetSkill();
			tempP->SetReady(false);
			tempP->SetCasting(false);
		}
		if(pDI->KeyPressed(DIK_W) || pDI->KeyPressed(DIK_UPARROW) || pDI->JoystickDPadPressed(DIR_UP) || pDI->JoystickGetLStickDirPressed(DIR_UP))
		{
			m_nSelection--;
			if(m_nSelection < 0)
				m_nSelection = 0;

		}
		if(pDI->KeyPressed(DIK_S) || pDI->KeyPressed(DIK_DOWNARROW) || pDI->JoystickDPadPressed(DIR_DOWN) || pDI->JoystickGetLStickDirPressed(DIR_DOWN))
		{
			m_nSelection++;
			if(m_nSelection >= m_nItemTotal)
				m_nSelection = m_nItemTotal -1;
		}
		if(pDI->KeyPressed(DIK_RETURN)|| pDI->JoystickButtonPressed(1))
		{
			int nID = 0;
			for(auto i = m_mTemp->begin(); i != m_mTemp->end(); i++)
			{
				if(i->second.Item != nullptr)
				{
					if(i->second.Item->GetItemType() == IT_CONSUMABLE)
					{
						if(nID == m_nSelection)
						{
							CConsumable* ItemTemp = reinterpret_cast<CConsumable*>(i->second.Item);
							if(ItemTemp != nullptr)
							{
								if(i->second.Owned > 0)
								{
									if(ItemTemp->GetType() == "HP")
										GetOwner()->ModifyHealth(-ItemTemp->GetAmount(), false);

									else if(ItemTemp->GetType() == "MP")
										GetOwner()->ModifyAP(-ItemTemp->GetAmount());
									if(i->second.Item != nullptr)
									{
										if(i->second.Item->GetItemType() == IT_CONSUMABLE)
										{
											CConsumable* pTemp = reinterpret_cast<CConsumable*>(i->second.Item);
											if(pTemp != nullptr)
											{
												GetOwner()->RemoveConsumableItem(pTemp);
											}
										}
									}
									tempP->SetReady(false);
									tempP->SetCasting(false);
									tempP->SetTurn(false);
									ResetSkill();
									return;
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

}
void CUseItem::Render(void)
{
	CBitmapFont* m_pFont = CGame::GetInstance()->GetFont("Arial");
	if(GetOwner() != nullptr)
	{
		wostringstream woss;
		int m_nCount = 0;
		m_nItemTotal = 0;
		if(m_mTemp != nullptr)
		{
			for(auto i = m_mTemp->begin(); i != m_mTemp->end(); i++)
			{
				if(i->second.Item != nullptr)
				{
					if(i->second.Item->GetItemType() == IT_CONSUMABLE)
					{
						m_nItemTotal++;
						CConsumable* ItemTemp = reinterpret_cast<CConsumable*>(i->second.Item);
						if(ItemTemp != nullptr)
						{
							if(i->second.Owned > 0)
							{
								woss << ItemTemp->GetName().c_str() << " " << i->second.Owned;
								m_pFont->Draw(woss.str().c_str(), 360, 490 + m_nCount * 16, 0.75f, D3DCOLOR_XRGB(255,255,255));
								woss.str(_T(""));
								m_nCount++;
							}
						}
					}
				}
			}
			if(m_mTemp->size() > 0)
			{
				RECT rTemp = { };
				rTemp.top = 498 + (m_nSelection * 16);
				rTemp.bottom = rTemp.top + 10;
				rTemp.left = 348;
				rTemp.right = 358;
				CSGD_Direct3D::GetInstance()->DrawHollowRect(rTemp, D3DCOLOR_XRGB( 0,0,255 ));

			}
		}

	}
}