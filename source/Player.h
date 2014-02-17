#pragma once
#include "entity.h"
#include <vector>
#include "PlayerUnit.h"

class CPlayer : public CEntity
{
	CPlayerUnit* m_cBattle;
	std::string m_szName;
	std::string m_szZone;

	float m_fLastY;
	float m_fLastX;
	bool m_bIsWarping;
	bool m_bInteraction;
public:
	CPlayer(void);
	virtual ~CPlayer(void);
	void Update(float fElapsedTime) override;
	virtual void HandleCollision(CObjects* col) override;
	virtual void HandleEvent( const CEvent* pEvent ) override;

	void SetName(std::string szName);
	void SetZone(std::string szZone) {m_szZone = szZone;}
	void SetLastPositionX(float fPos) {m_fLastX = fPos;}
	void SetLastPositionY(float fPos) {m_fLastY = fPos;}
	void SetIsWarping(bool bWarp) {m_bIsWarping = bWarp;}
	void SetInteraction(bool bInter) {m_bInteraction = bInter;}
	void SetUnit	(CPlayerUnit* pUnit);

	bool GetInteraction() const {return m_bInteraction;}
	bool GetIsWarping(void) const{return m_bIsWarping;}
	std::string GetName(void) const {return m_szName;}
	std::string GetZone(void) const {return m_szZone;}
	CUnits* GetUnit	( void )				{ return m_cBattle; }
};