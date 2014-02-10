#pragma once

#include "Minigames.h"
#include "Projectile.h"
#include <vector>
#include <string>
using namespace std;

class CCommands
{

	vector<CCommands*> m_vCommands;
	string m_sName;
	CMiniGames* m_pMiniGame;
	bool m_bIsGame;
	
public:

	void SetSkill(CProjectile* l) { m_pMiniGame->SetSkill(l);}
	vector<CCommands*>* GetCommands(void) { return &m_vCommands; }
	void AddCommands(CCommands* l) { m_vCommands.push_back(l); }
	CCommands* GetCommand(int ID) { return m_vCommands[ID]; }

	string GetName(void) { return m_sName; }
	void SetName(string l) { m_sName = l; }

	bool GetIsGame(void) { return m_bIsGame; }
	void SetIsGame(bool l) { m_bIsGame = l; }

	CMiniGames* GetMiniGame(void) { return m_pMiniGame; }
	void SetMiniGame(CMiniGames* l) { m_pMiniGame = l; }

	CCommands(void);
	~CCommands(void);
};

