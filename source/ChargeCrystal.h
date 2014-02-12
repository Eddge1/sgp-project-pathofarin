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
	int m_nCursorImageID;
	float m_fScale;
	bool m_bDamage;
	bool m_bFailed;
	bool m_bHeal;
public:
	CChargeCrystal(void);
	virtual ~CChargeCrystal(void);
	virtual void DoAttack(void) override;
	void SetDamageSkill(bool bValue) {m_bDamage = bValue;}
	bool DamageSkill(void) {return m_bDamage;}
	void SetHeal(bool bValue) {m_bHeal = bValue;}
	void InstantiateSkill();
	virtual void Render() override;
	virtual void Update(float fElpasedTime) override;
	virtual void ResetSkill() override;
	virtual void HandleEvent( const CEvent* pEvent ) override { }
};

