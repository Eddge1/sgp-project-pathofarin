#pragma once
#include "minigames.h"
#include "Units.h"
class CUseItem : public CMiniGames
{
	bool m_bGetInventory;
	map<string, InventoryItems>* m_mTemp;
	int m_nSelection;

public:

	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	CUseItem(void);
	virtual ~CUseItem(void);
	virtual void ResetSkill() override {m_bGetInventory = false; m_mTemp = nullptr; m_nSelection = 0;}
	virtual void HandleEvent( const CEvent* pEvent ) override{ }
};

