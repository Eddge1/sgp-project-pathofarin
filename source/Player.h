#pragma once
#include "entity.h"
#include <vector>
#include "PlayerUnit.h"

class CPlayer : public CEntity
{
	CPlayerUnit* m_cBattle;
	std::string m_szName;
	std::string m_szZone;
	std::vector<std::string> m_szListen;
	std::vector<std::string> m_szHeard;;

	float m_fLastY;
	float m_fLastX;
	bool m_bIsWarping;
	bool m_bInteraction;
	bool m_bBroadcast;
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
	void AddListen (std::string szEvent);
	void AddHeard (std::string szEvent);

	void SetBroadcasting(bool bValue) {m_bBroadcast = bValue;}
	void BroadCastHeard();
	std::vector<std::string>& getHeard() {return m_szHeard;}

	bool isBroadcasting() const {return m_bBroadcast;}
	bool GetInteraction() const {return m_bInteraction;}
	bool GetIsWarping(void) const{return m_bIsWarping;}
	std::string GetName(void) const {return m_szName;}
	std::string GetZone(void) const {return m_szZone;}
	CUnits* GetUnit	( void )				{ return m_cBattle; }
};