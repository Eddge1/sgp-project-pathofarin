#include "World.h"
#include "Game.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"



CWorld::CWorld(void)
{
}


CWorld::~CWorld(void)
{
	for(unsigned int i = 0; i < m_vMyLayers.size(); i++)
	{
		delete m_vMyLayers[i];
	}
}


void CWorld::Render(int layer)
{
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();


	if(GetID() == -1 || layer >= int(m_vMyLayers.size()))
		return;

	int WorldCamX = CGamePlayState::GetInstance()->GetWorldCamX();
	int WorldCamY = CGamePlayState::GetInstance()->GetWorldCamY();

	RECT temp = { };

	CLayer* TempLayer = m_vMyLayers[layer];

	for(unsigned int i = 0; i < m_vMyLayers[layer]->GetSize(); i++)
	{
		int foo = i % GetWidth() * GetTileWidth();
		int fee = i / GetHeight() * GetTileHeight();
		if(foo > WorldCamX + GetTileWidth() && foo < WorldCamX + GetTileWidth() + CGame::GetInstance()->GetScreenWidth()) 
		{
			if( fee > WorldCamY - GetTileHeight() && fee < WorldCamY + GetTileHeight() + CGame::GetInstance()->GetScreenHeight())
			{
				temp.left = TempLayer->GetTile(i)->GetTileX() * GetTileWidth();
				temp.top = TempLayer->GetTile(i)->GetTileY() * GetTileHeight();
				temp.right = temp.left + GetTileWidth();
				temp.bottom = temp.top + GetTileHeight();


				pTM->Draw(GetID(), (i % GetWidth() ) * GetTileWidth() - WorldCamX, ( i / GetWidth() ) * GetTileHeight() - WorldCamY, 1.0f, 1.0f, &temp); 
			}
		}
	}


}
