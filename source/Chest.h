#pragma once
#include "objects.h"
#include <vector>
#include <string>
using namespace std;
class CChest :
	public CObjects
{
	vector<string> m_vItems;
	bool m_bOpened;
	string m_szBroadCast;

public:
	CChest(void);
	virtual ~CChest(void);
};

