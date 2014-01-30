#pragma once

#include "Tile.h"
#include <vector>
using namespace std;


class CLayer
{
	vector<CTile*> m_vMyTiles;
	int m_nSizeX;
	int m_nSizeY;
	int m_nXOffset;
	int m_nYOffset;

public:

	void AddTile( CTile* t );
	void AddTiles(vector<CTile*> t);
	CTile* GetTile(int t) { return m_vMyTiles[t]; }
	vector<CTile*> GetTiles(void);

	void SetSizeX(int nAmount) {m_nSizeX = nAmount;}
	void SetSizeY(int nAmount) { m_nSizeY= nAmount;}
	void SetOffsetX(int nAmount) { m_nXOffset= nAmount;}
	void SetOffsetY(int nAmount) { m_nYOffset= nAmount;}

	int GetSizeX()	 const { return m_nSizeX;}
	int GetSizeY()	 const { return m_nSizeY;}
	int GetOffsetX() const { return m_nXOffset;}
	int GetOffsetY() const { return m_nYOffset;}

	unsigned int GetSize(void) { return m_vMyTiles.size(); }

	CLayer(void);
	~CLayer(void);
};

