#pragma once
#include "units.h"
#include <vector>
using namespace std;
#include "Commands.h"

class CPlayerUnit :	public CUnits
{
	bool m_bInSubMenu;
	bool m_bSkillSelected;
	bool m_bCasting;
	int m_nMenuSelect;
	int m_nSkillSelect;
	vector<CCommands*> m_vCommands;

public:
	CPlayerUnit(void);
	virtual ~CPlayerUnit(void);
	virtual void HandleEvent( const CEvent* pEvent ) override;

	bool GetInSubMenu	(void) const	{return m_bInSubMenu;}
	bool GetReady		(void) const	{return m_bSkillSelected;}
	virtual void EndTurn() override;

	int  GetMenuID		(void) const	{return m_nMenuSelect;}
	int  GetSkillID		(void) const	{if(m_bInSubMenu) return m_nSkillSelect;
										else return m_nMenuSelect;}

	void GetInSubMenu	(bool bValue)	{m_bInSubMenu = bValue;}
	void GetReady		(bool bValue)	{m_bSkillSelected = bValue;}
	void GetMenuID		(int nID)		{m_nMenuSelect = nID;}
	void GetSkillID		(int nID)		{m_nSkillSelect = nID;}
	void AddSkill		(CCommands* nSkill)	{m_vCommands.push_back(nSkill);}
	vector<CCommands*>* GetCommands(void) {return &m_vCommands;}
	CCommands* GetSkill(int nID);
	virtual void Update(float fElapsedTime) override;

};

