#pragma once
#include "entity.h"
#include "Units.h"
#include "Minigames.h"
class CProjectile :	public CEntity
{
	CUnits* m_pTarget;
	CMiniGames* m_pMaster;
	bool m_bCollided;
	bool m_bCrit;
public:
	void SetMasterGame(CMiniGames* pMini) {m_pMaster = pMini;}
	void SetTarget(CUnits* pUnit);

	void SetCritical(bool bCrit) {m_bCrit = bCrit;}
	bool GetCrit() const {return m_bCrit;}
	CMiniGames* GetMini() const {return m_pMaster;}
	CUnits* GetTarget() const {return m_pTarget;}
	bool GetCollided() const{return m_bCollided;}
	CProjectile(void);
	virtual ~CProjectile(void);
	virtual void Update(float fElapsedTime);
	virtual void HandleCollision(CObjects* col) {}
	virtual void HandleEvent( const CEvent* pEvent ) override {}
};

