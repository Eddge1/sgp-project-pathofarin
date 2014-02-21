#pragma once
#include "minigames.h"

struct TargetLocs
{
	float fX;
	float fY;
};

class CPrecisionStrike : public CMiniGames
{
	vector<TargetLocs> m_vTargets;
	float m_fTimer;
	float m_fCursorX;
	float m_fCursorY;
	int	m_nImageID;
	int m_nCursorImageID;
	bool m_bReady;
	CUnits* m_pTarget;

public:

	CPrecisionStrike(void);
	virtual ~CPrecisionStrike(void);
	virtual void HandleEvent( const CEvent* pEvent ) override { }
	virtual void DoAttack(void) override;
	virtual void Update(float fElapsedTime);
	virtual void Render();
	virtual void ResetSkill() override;
	virtual bool PointToRect(RECT&, int, int);
};

