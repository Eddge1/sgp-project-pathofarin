#pragma once
#include "entity.h"
#include <vector>
#include "PlayerUnit.h"

class CPlayer : public CEntity
{
	CPlayerUnit* m_cBattle;
public:
	CPlayer(void);
	virtual ~CPlayer(void);
	void Update(float fElapsedTime) override;

	CUnits* GetUnit	( void )				{ return m_cBattle; }
	void SetUnit	(CPlayerUnit* pUnit)	{ m_cBattle = pUnit; }
	virtual void HandleCollision(CObjects* col) override;
};