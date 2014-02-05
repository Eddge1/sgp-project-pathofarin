#pragma once
#include "entity.h"
#include <string>
using namespace std;
class CUnits :
	public CEntity
{

	enum UnitClass {UC_ENEMY, UC_NONE, UC_WARRIOR, UC_RANGER, UC_MAGE};
	int m_nHealth;
	int m_nMaxHealth;
	int m_nAbilityPoints;
	int m_nMaxAbilityPoints;
	int m_nAttackPower;
	int m_nLevel;
	int m_nSpeed;

	bool m_bTurn;
	int m_nExperience;
	int m_nAvailStats;
	UnitClass m_eClass;

	//int m_nGold;
	//std::map<string, CItem> m_mInventory

	string m_sName;
public:
	CUnits(void);
	virtual ~CUnits(void);

	virtual void ModifyHealth(int nAmount, bool isCrit);
	void ModifyAP(int nAmount);

	virtual void Update(float fElapsedTime) override;

	void SetTurn(bool bTurn) {m_bTurn = bTurn;}
	virtual void EndTurn() {m_bTurn = false;}

	int GetSpeed			( void ) const			{return m_nSpeed;};
	int GetLevel			( void ) const			{return m_nLevel;}
	int GetAttack			( void ) const			{return m_nAttackPower;}
	int GetHealth			( void ) const			{return m_nHealth;}
	int GetAbilityPoints	( void ) const			{return m_nAbilityPoints;}
	int GetExperience       ( void ) const			{return m_nExperience;}
	int GetStats			( void ) const			{return m_nAvailStats;}
	int GetMaxHealth		( void ) const			{return m_nMaxHealth;}
	int GetMaxAP			( void ) const			{return m_nMaxAbilityPoints;}
	bool GetTurn			( void ) const			{return m_bTurn;}
	string GetName			( void ) const			{ return m_sName; }

	void SetMaxHealth		( int nAmount )		{m_nHealth = m_nMaxHealth = nAmount;}
	void SetMaxAP			( int nAmount )		{m_nAbilityPoints = m_nMaxAbilityPoints = nAmount;}
	void SetSpeed			( int nAmount )		{m_nSpeed = nAmount; }
	void SetAttack			( int nAmount )		{m_nAttackPower = nAmount; }
	void GiveExperience		( int nAmount );
	void SetName( string input ) { m_sName = input; }
	void SetClass( UnitClass eClass ) {m_eClass = eClass;}

	virtual void HandleEvent( const CEvent* pEvent ) override;

	bool decrStat();
	bool incrStat();
	bool incrAttack();
	bool decrAttack();
	bool incrHealth();
	bool decrHealth();
	bool incrAbility();
	bool decrAbility();

	friend bool operator <(CUnits &l, CUnits  &r)
	{
		return l.GetSpeed() < r.GetSpeed();
	}

	friend bool operator >(CUnits &l, CUnits  &r)
	{
		return l.GetSpeed() > r.GetSpeed();
	}


};

