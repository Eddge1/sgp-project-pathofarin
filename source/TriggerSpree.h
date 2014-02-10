#pragma once
#include "minigames.h"
#include <vector>
class CTriggerSpree : public CMiniGames
{
	std::vector<RECT*> m_vGameElements;
	std::vector<RECT*> m_vTriggers;

	bool m_bSuccess;
	bool m_bFailed;
	float m_fTimer;
	int m_nSuccess;

public:
	CTriggerSpree(void);
	virtual void Render() override;
	virtual void Update(float fElpasedTime) override;
	virtual ~CTriggerSpree(void);
	virtual void ResetSkill() override;
	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual void DoAttack(void) override {} 

};

