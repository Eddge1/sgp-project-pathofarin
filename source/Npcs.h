#pragma once
#include "entity.h"
#include <vector>

class CNpcs : public CEntity
{
	std::vector<std::string> m_szConversation;
	std::string m_szEventThrow; 
	bool m_bContainsUnits;
	bool m_bIsHostile;

	std::vector<std::string> m_vUnitList;
public:
	CNpcs(void);
	virtual ~CNpcs(void);
	std::vector<std::string> GetUnits(void) {return m_vUnitList;}
	void SetEvent(std::string szEvent) {m_szEventThrow = szEvent;}
	void SetHostile(bool bHostile)		{m_bIsHostile = bHostile;}

	void SetUnits(std::string szName);
	void AddConversation(std::string szConvo);
	virtual void Update(float fElapsedTime) override;
	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual void HandleCollision(CObjects* col) override;
};

