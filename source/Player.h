#pragma once
#include "entity.h"
#include <vector>
#include "PlayerUnit.h"

class CPlayer : public CEntity
{
	CPlayerUnit* m_cBattle;
	std::string m_szName;
public:
	CPlayer(void);
	virtual ~CPlayer(void);
	void Update(float fElapsedTime) override;
	
	void SetName(std::string szName);
	std::string GetName(void) const {return m_szName;}

	CUnits* GetUnit	( void )				{ return m_cBattle; }
	void SetUnit	(CPlayerUnit* pUnit);
	virtual void HandleCollision(CObjects* col) override;
	virtual void HandleEvent( const CEvent* pEvent ) override;
};