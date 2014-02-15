#pragma once
#include "minigames.h"
class CSteadyShot :
	public CMiniGames
{
	float	m_fMoveSpeed;
	float	m_fTimer;
	float	m_fRadius;
	float	m_fCursorX;
	float	m_fCursorY;
	int		m_nImageID;
	int		m_nCursorImageID;
	bool	m_bCompleted;
public:
	CSteadyShot(void);
	virtual ~CSteadyShot(void);
	virtual void HandleEvent( const CEvent* pEvent ) override {}
	virtual void DoAttack(void) override;
	virtual void Update(float fElapsedTime);
	virtual void Render();
	virtual void ResetSkill() override;
};

