#include "Layer.h"


CLayer::CLayer(void)
{
}


CLayer::~CLayer(void)
{
	for(unsigned int i = 0; i < m_vMyTiles.size(); i++)
	{
		delete m_vMyTiles[i];
	}
}


void CLayer::AddTile( CTile* t )
{
	m_vMyTiles.push_back(t);
}


vector<CTile*> CLayer::GetTiles(void)
{
	return m_vMyTiles;
}

void CLayer::AddTiles(vector<CTile*> t)
{
	for(unsigned int i = 0; i < t.size(); i++)
	{
		AddTile(t[i]);
	}
}

