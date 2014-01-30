#include "UseItem.h"
#include "BitmapFont.h"
#include "PlayerUnit.h"
#include "Game.h"

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
	m_pFont->Draw(_T("Out of Items!"), 320, 400, 1.0f, D3DCOLOR_XRGB(0, 0, 0) );

}