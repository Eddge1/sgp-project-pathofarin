#pragma once
#include "entity.h"
#include <vector>

class CNpcs : public CEntity
{
	std::vector<std::string> m_vUnitList;
	std::vector<std::string> m_szConversation;
	std::string m_szEventThrow; 
	bool m_bContainsUnits;
	bool m_bIsHostile;

public:
	CNpcs(void);
	virtual ~CNpcs(void);
	std::vector<std::string> GetUnits(void) {return m_vUnitList;}
	void SetEvent(std::string szEvent) {m_szEventThrow = szEvent;}
	void SetHostile(bool bHostile)		{m_bIsHostile = bHostile;}

	void SetUnits(std::string szName);
	void AddConversation(std::string szConvo);
	std::string GetUnit(int nI);
	unsigned int GetUnitSize() {return m_vUnitList.size();}
	unsigned int GetConvoSize() {return m_szConversation.size();}

	virtual void Update(float fElapsedTime) override;
	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual void HandleCollision(CObjects* col) override;
};

