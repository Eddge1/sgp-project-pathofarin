#pragma once

#include "Tile.h"
#include <vector>
using namespace std;


class CLayer
{
	vector<CTile*> m_vMyTiles;


public:

	void AddTile( CTile* t );
	void AddTiles(vector<CTile*> t);
	CTile* GetTile(int t) { return m_vMyTiles[t]; }
	vector<CTile*> GetTiles(void);

	unsigned int GetSize(void) { return m_vMyTiles.size(); }

	CLayer(void);
	~CLayer(void);
};

