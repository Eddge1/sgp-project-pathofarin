#pragma once
#include "minigames.h"
class CTriggerMatch :
	public CMiniGames
{
	std::vector<RECT*> m_vGameElements;
	RECT m_rTrigger;

	bool m_bSuccess;
	bool m_bCritical;
	bool m_bFailed;
	bool m_bLeft;
	float m_fMoveSpeed;
	int m_nSuccess;
public:
	CTriggerMatch(void);
	virtual ~CTriggerMatch(void);
	virtual void Render() override;
	virtual void Update(float fElpasedTime) override;
	virtual void ResetSkill() override;
	virtual void HandleEvent( const CEvent* pEvent ) override { }

};

