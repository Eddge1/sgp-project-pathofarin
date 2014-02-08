#pragma once
#include "entity.h"
#include "EnemyUnit.h"
#include <vector>

class CNpcs : public CEntity
{
	struct SWaypoint
	{
		float locX;
		float locY;
	};
	std::vector<CEnemyUnit*> m_vUnitList;
	std::vector<std::string> m_szConversation;
	std::vector<SWaypoint*> m_vWaypoints;
	std::string m_szEventThrow; 
	std::string m_szName; 

	bool m_bContainsUnits;
	bool m_bIsHostile;
	bool m_bGameVictory;
	int m_nWaypoint;
	float m_fDelayChat;

public:

	CNpcs(void);
	virtual ~CNpcs(void);
	std::vector<CEnemyUnit*>& GetUnits(void) {return m_vUnitList;}
	std::string GetName() const {return m_szName;}
	void RegEvent(std::string szEvent)  {CSGD_EventSystem::GetInstance()->RegisterClient(szEvent.c_str(), this);}
	void SetEvent(std::string szEvent)	{m_szEventThrow = szEvent;}
	void SetHostile(bool bHostile)		{m_bIsHostile = bHostile;}
	void SetName(std::string szName)	{m_szName = szName;}

	void SetUnits(CEnemyUnit* l);
	void AddConversation(std::string szConvo);
	void AddWaypoint(float fX, float fY);
	CEnemyUnit* GetUnit(int nI);
	unsigned int GetUnitSize() {return m_vUnitList.size();}
	unsigned int GetConvoSize() {return m_szConversation.size();}

	virtual void Update(float fElapsedTime) override;
	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual void HandleCollision(CObjects* col) override;
};

