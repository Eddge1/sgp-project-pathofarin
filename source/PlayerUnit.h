#pragma once
#include "units.h"
#include <vector>
using namespace std;
#include "Commands.h"
class CPlayer;

class CPlayerUnit :	public CUnits
{
	bool m_bInSubMenu;
	bool m_bSkillSelected;
	bool m_bCasting;
	int m_nMenuSelect;
	int m_nSkillSelect;
	vector<CCommands*> m_vCommands;
	CPlayer* m_pPlayer;
	bool m_bDodge;
	float timer;

	//Audio
	int m_nSelectionChange;
	int m_nSelectionConfirm;
	int m_nSelectionBack;

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
	void SetOwner(CPlayer* pPlayer);
	CPlayer* GetOwner(void) {return m_pPlayer;}

	void SetCasting(bool l) { m_bCasting = l; }
	bool GetCasting(void) { return m_bCasting; }
	void ModifyHealth(int nAmount, bool isCrit);

	void SetInSubMenu	(bool bValue)	{m_bInSubMenu = bValue;}
	void SetReady		(bool bValue)	{m_bSkillSelected = bValue;}
	void SetMenuID		(int nID)		{m_nMenuSelect = nID;}
	void SetSkillID		(int nID)		{m_nSkillSelect = nID;}
	void AddSkill		(CCommands* nSkill)	{m_vCommands.push_back(nSkill);}
	vector<CCommands*>* GetCommands(void) {return &m_vCommands;}
	CCommands* GetSkill(int nID);
	virtual void Update(float fElapsedTime) override;

};

