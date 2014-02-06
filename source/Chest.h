#pragma once
#include "objects.h"
#include <vector>
#include <string>
#include "Units.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
using namespace std;
class CChest : public CObjects
{
	map<string, InventoryItems> m_vItems;
	bool m_bOpened;
	bool m_bCollided;
	string m_szBroadCast;
public:
	void RegEvent(string szEvent) {m_szBroadCast = szEvent;}
	void AddConsumableItem(CConsumable* input, int nAmount = 1, float fChance = 1.0f);

	CChest(void);
	virtual ~CChest(void);
	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual void HandleCollision(CObjects* col) override;
	virtual RECT GetCollisionRect() override;
	virtual void Update(float fElapsedTime) override;

};

