#pragma once

#include "Tile.h"
#include "Layer.h"
#include <vector>
#include <string>
#include "../SGD Wrappers/CSGD_EventSystem.h"
class CObjectManager;
class CObjects;

using namespace std;

class CWorld : public IListener
{
	int m_nHeight;
	int m_nWidth;
	int m_nImageID;

	int m_nTileWidth;
	int m_nTileHeight;
	int m_nMusic;

	vector<CLayer*> m_vMyLayers;
	vector<int> m_vClearNPC;
	string m_sMapName;
	CObjectManager* m_pOM;
public:

	void Render(int layer);
	void Update(float fElapsedTime);
	void AddObject(CObjects* pObject, unsigned int nLayer);
	void RemoveObject(CObjects* pObject);
	void SetMusic(int nID) {m_nMusic = nID;}

	int GetMusicID() const {return m_nMusic;}
	int GetTileHeight( void) { return m_nTileHeight; }
	void SetTileHeight(int t) { m_nTileHeight = t; }
	int GetTileWidth( void) { return m_nTileWidth; }
	void SetTileWidth(int t) { m_nTileWidth = t; }
	int GetID( void) { return m_nImageID; }
	void SetID(int t) { m_nImageID = t; }
	int GetHeight( void) { return m_nHeight; }
	void SetHeight(int t) { m_nHeight = t; }
	int GetWidth( void) { return m_nWidth; }
	void SetWidth(int t) { m_nWidth = t; }

	void SetMapName(string t) { m_sMapName = t; }
	string GetMapName(void) { return m_sMapName; }

	void ClearNPCList();
	void ActivateNPCs();

	void AddClear(int nID);
	vector<int>& GetClearedNpcs() {return m_vClearNPC;}

	void AddLayers(CLayer* t) { m_vMyLayers.push_back(t); }
	virtual void HandleEvent( const CEvent* pEvent ) override;

	CWorld(void);
	virtual ~CWorld(void);
};

