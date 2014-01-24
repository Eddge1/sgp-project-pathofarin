#pragma once

#include "Tile.h"
#include "Layer.h"
#include <vector>
#include <string>
class CObjectManager;
class CObjects;

using namespace std;

class CWorld
{
	int m_nHeight;
	int m_nWidth;
	int m_nImageID;

	int m_nTileWidth;
	int m_nTileHeight;

	vector<CLayer*> m_vMyLayers;
	string m_sMapName;
	CObjectManager* m_pOM;
public:

	void Render(int layer);
	void Update(float fElapsedTime);
	void AddObject(CObjects* pObject, unsigned int nLayer);

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

	void AddLayers(CLayer* t) { m_vMyLayers.push_back(t); }


	CWorld(void);
	~CWorld(void);
};

