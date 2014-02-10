#pragma once
#include "minigames.h"
class CChargeCrystal :
	public CMiniGames
{
	float	m_fMoveSpeed;
	float	m_fTimer;
	float	m_fRadius;
	float	m_fRotation;
	float	m_fCursorX;
	float	m_fCursorY;
	int		m_nSuccess;
	int		m_nChargeImgID;
public:
	CChargeCrystal(void);
	virtual ~CChargeCrystal(void);

	virtual void DoAttack(void) override {}

	virtual void Render() override;
	virtual void Update(float fElpasedTime) override;
	virtual void ResetSkill() override;
	virtual void HandleEvent( const CEvent* pEvent ) override { }
};

