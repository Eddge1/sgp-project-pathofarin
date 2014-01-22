#pragma once
#include "entity.h"
#include <string>
using namespace std;
class CUnits :
	public CEntity
{
	int m_nHealth;
	int m_nMaxHealth;
	int m_nAbilityPoints;
	int m_nMaxAbilityPoints;
	int m_nAttackPower;
	int m_nLevel;
	int m_nSpeed;

	bool m_bTurn;
	int m_nSkillSelection;
	//int m_nExperience;
	//int m_nGold;
	//int m_nAvailStats;
	//std::map<string, CItem> m_mInventory


	string m_sName;



public:






	CUnits(void);
	virtual ~CUnits(void);

	string GetName() { return m_sName; }
	void SetName( string input ) { m_sName = input; }

	void ModifyHealth(int nAmount, bool isCrit);
	void ModifyAP(int nAmount);

	virtual void Update(float fElapsedTime) override;

	void SetTurn() {m_bTurn = true;}
	void EndTurn() {m_bTurn = false;}

	int GetSkillSelection	( void )			{return m_nSkillSelection;};
	int GetSpeed			( void )			{return m_nSpeed;};
	int GetLevel			( void )			{return m_nLevel;}
	int GetAttack			( void )			{return m_nAttackPower;}
	int GetHealth			( void )			{return m_nHealth;}
	int GetAbilityPoints	( void )			{return m_nAbilityPoints;}

	void SetMaxHealth		( int nAmount )		{m_nHealth = m_nMaxHealth = nAmount;}
	void SetMaxAP			( int nAmount )		{m_nAbilityPoints = m_nMaxAbilityPoints = nAmount;}
	void SetSpeed			( int nAmount )		{m_nSpeed = nAmount; }

	virtual void HandleEvent( const CEvent* pEvent ) override;


	/*
	bool incrAttack();
	bool incrHealth();
	bool incrAbility();
	*/



	friend bool operator <(CUnits &l, CUnits  &r)
	{
		return l.GetSpeed() < r.GetSpeed();
	}

	friend bool operator >(CUnits &l, CUnits  &r)
	{
		return l.GetSpeed() > r.GetSpeed();
	}


};

