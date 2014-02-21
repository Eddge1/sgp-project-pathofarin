#pragma once
#include "minigames.h"
#include "BattleState.h"
#include "Units.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"

class CBasicAttack : public CMiniGames
{

	CUnits* m_pTarget;
	bool bAttacked;
	bool bhasPlayed;
	
	int m_nSound;
	int m_nOrcLeader;
	int m_nPathOrc;
	int m_nOrcSha;
	int m_nSnail;
	int m_nSpider;
	int m_nTree;
	int m_nOgre;
	int m_nBat;
	int m_nBandit;
	int m_nThornBiter;
	int m_nGolem;
	int m_nShade;
	int m_nBee;
	int m_nOrc;
	int m_nSnake;
	int m_nValrion;


public:

	virtual void Update(float fElapsedTime) override;

	virtual void DoAttack(void) override;

	CUnits* GetTarget(void) { return m_pTarget; }
	void SetTarget(CUnits* l) { m_pTarget = l; }
	virtual void ResetSkill() override;
	virtual void HandleEvent( const CEvent* pEvent ) override;

	CBasicAttack(void);
	virtual ~CBasicAttack(void);
};