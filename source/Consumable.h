#pragma once
#include "item.h"
#include <string>
using namespace std;
class CConsumable :
	public CItem
{

	string m_sName;
	string m_sDes;
	string m_sType;
	int m_nAmount;

public:

	void SetName(string input) { m_sName = input; }
	void SetDes(string input) { m_sDes = input; }
	void SetType(string input) { m_sType = input; }
	void SetAmount(int input) { m_nAmount = input;}

	string GetName(void) { return m_sName; }
	string GetDes(void) { return m_sDes;}
	string GetType(void) { return m_sType;}
	int GetAmount(void) { return m_nAmount;}


	CConsumable(void);
	~CConsumable(void);
	CConsumable( const CConsumable& );
	CConsumable& operator= ( const CConsumable& );
};

