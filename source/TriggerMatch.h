#pragma once
#include "minigames.h"

class CBuff;

class CTriggerMatch :
	public CMiniGames
{
	std::vector<RECT*> m_vGameElements;
	RECT m_rTrigger;

	bool m_bAuraPlay;
	bool m_bSuccess;
	bool m_bCritical;
	bool m_bFailed;
	bool m_bLeft;
	float m_fMoveSpeed;
	int m_nSuccess;
	std::vector<CProjectile*> m_vSkills;
	CBuff* pBuff;

public:
	CTriggerMatch(void);
	virtual ~CTriggerMatch(void);
	virtual void Render() override;
	virtual void Update(float fElapsedTime) override;
	virtual void ResetSkill() override;
	virtual void HandleEvent( const CEvent* pEvent ) override { }
	virtual void DoAttack(void) override;
	virtual void InstantiateSkill();

};

