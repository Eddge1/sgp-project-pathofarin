#pragma once
#include "minigames.h"
class CComboGame :	public CMiniGames
{
	std::vector<int> m_vMoveList;
	std::vector<int> m_vMovesMade;
	int m_nCombArrowImgID;
	float m_fTimer;
	bool m_bSuccess;
	int m_nCurr;
public:
	CComboGame(void);
	virtual ~CComboGame(void);
	virtual void Render() override;
	virtual void Update(float fElpasedTime) override;
	virtual void ResetSkill() override;
	virtual void HandleEvent( const CEvent* pEvent ) override { }
};

