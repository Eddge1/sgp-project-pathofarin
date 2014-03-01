#pragma once
#include "minigames.h"
#include "Units.h"
class CUseItem : public CMiniGames
{
	bool m_bGetInventory;
	map<string, InventoryItems>* m_mTemp;
	int m_nSelection;
	int m_nItemTotal;
	int m_nItemCursor;
	bool m_bFirstDone;
public:

	virtual void Update(float fElapsedTime);
	virtual void Render(void);

	CUseItem(void);
	virtual ~CUseItem(void);
	virtual void ResetSkill() override {m_bGetInventory = false; m_mTemp = nullptr; m_nSelection = 0; m_bFirstDone = false;}
	virtual void HandleEvent( const CEvent* pEvent ) override{ }
	virtual void DoAttack(void) override {}

};

