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

	void SetTurn(bool bTurn) {m_bTurn = bTurn;}
	virtual void EndTurn() {m_bTurn = false;}

	int GetSpeed			( void ) const			{return m_nSpeed;};
	int GetLevel			( void ) const			{return m_nLevel;}
	int GetAttack			( void ) const			{return m_nAttackPower;}
	int GetHealth			( void ) const			{return m_nHealth;}
	int GetAbilityPoints	( void ) const			{return m_nAbilityPoints;}
	bool GetTurn			( void ) const			{return m_bTurn;}

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

