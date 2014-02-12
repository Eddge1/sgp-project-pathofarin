#include "World.h"
#include "Game.h"
#include "GamePlayState.h"
#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "ObjectManager.h"
#include "Objects.h"

CWorld::CWorld(void)
{
	m_pOM = new CObjectManager();
	CSGD_EventSystem::GetInstance()->RegisterClient("INIT_BATTLE", this);
}

CWorld::~CWorld(void)
{
	CSGD_EventSystem::GetInstance()->UnregisterClientAll(this);
	for(unsigned int i = 0; i < m_vMyLayers.size(); i++)
	{
		delete m_vMyLayers[i];
	}
	m_pOM->RemoveAll();
	delete m_pOM;
	m_pOM = nullptr;
}

void CWorld::Render(int layer)
{
	CSGD_TextureManager* pTM = CSGD_TextureManager::GetInstance();
	m_pOM->Render(layer);

	if(GetID() == -1 || layer >= int(m_vMyLayers.size()))
		return;

	int WorldCamX = CGamePlayState::GetInstance()->GetWorldCamX();
	int WorldCamY = CGamePlayState::GetInstance()->GetWorldCamY();

	RECT temp = { };

	CLayer* TempLayer = m_vMyLayers[layer];
	int nXOffset = TempLayer->GetOffsetX();
	int nYOffset = TempLayer->GetOffsetY();

	for(unsigned int i = 0; i < m_vMyLayers[layer]->GetSize(); i++)
	{
		int foo = i % TempLayer->GetSizeX() * GetTileWidth() + nXOffset;
		int fee = i / TempLayer->GetSizeX() * GetTileHeight() + nYOffset;
		if(foo > WorldCamX - GetTileWidth() && foo < WorldCamX + GetTileWidth() + CGame::GetInstance()->GetScreenWidth()) 
		{
			if( fee > WorldCamY - GetTileHeight() && fee < WorldCamY + GetTileHeight() + CGame::GetInstance()->GetScreenHeight())
			{
				if(TempLayer->GetTile(i)->GetTileX() != -1 && TempLayer->GetTile(i)->GetTileY() != -1)
				{
					temp.left = TempLayer->GetTile(i)->GetTileX() * GetTileWidth();
					temp.top = TempLayer->GetTile(i)->GetTileY() * GetTileHeight();
					temp.right = temp.left + GetTileWidth();
					temp.bottom = temp.top + GetTileHeight();

					pTM->Draw(GetID(), (i % TempLayer->GetSizeX() ) * GetTileWidth() - (WorldCamX - nXOffset), ( i / TempLayer->GetSizeX() ) * GetTileHeight() - (WorldCamY - nYOffset), 1.0f, 1.0f, &temp); 
				}
			}
		}
	}
}

void CWorld::Update(float fElapsedTime)
{
	m_pOM->Update(fElapsedTime);
	m_pOM->HandleCollision(2,2);
}

void CWorld::AddObject(CObjects* pObject, unsigned int nLayer)
{
	m_pOM->AddObject(pObject, nLayer);
}

void CWorld::RemoveObject(CObjects* pObject)
{
	m_pOM->RemoveObject(pObject);
}

void CWorld::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "INIT_BATTLE")
	{
		CObjects* pTemp = reinterpret_cast<CObjects*>(pEvent->GetSender());
		if(pTemp != nullptr)
		{
			m_vClearNPC.push_back(m_pOM->FindItem(pTemp));

		}
	}
}

void CWorld::ClearNPCList()
{
	m_vClearNPC.clear();
}

void CWorld::ActivateNPCs()
{
	m_pOM->ActivateAll(2);
}

void CWorld::AddClear(int nID)
{
	m_pOM->DeactiveObject(nID, 2);
	m_vClearNPC.push_back(nID);
}

