#include "UseItem.h"
#include "BitmapFont.h"
#include "PlayerUnit.h"
#include "Game.h"
#include <sstream>
using namespace std;

CUseItem::CUseItem(void)
{
	timer = 0.0f;
}


CUseItem::~CUseItem(void)
{
}


void CUseItem::Update(float fElapsedTime)
{
	CPlayerUnit* tempP = reinterpret_cast<CPlayerUnit*>(GetOwner());

	timer += fElapsedTime;


	if(timer > 3.0f)
	{
		timer = 0.0f;
		if(tempP != nullptr)
		{
			tempP->SetReady(false);
			tempP->SetCasting(false);
			return;
		}
	}




}


void CUseItem::Render(void)
{

	CBitmapFont* m_pFont = CGame::GetInstance()->GetFont2();
	if(GetOwner() != nullptr)
	{
		map<string, InventoryItems> temp = GetOwner()->GetInv();
		wostringstream woss;
		int m_nCount = 0;


		for(auto i = temp.begin(); i != temp.end(); i++)
		{
			CConsumable* ItemTemp = reinterpret_cast<CConsumable*>(&(i->second.Item));
			if(ItemTemp != nullptr)
			{
				woss << ItemTemp->GetName().c_str();
				m_pFont->Draw(woss.str().c_str(), 300, 300 + m_nCount * 16, 0.75f, D3DCOLOR_XRGB(0,0,0));
			}
		}
	}


}