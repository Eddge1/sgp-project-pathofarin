#include "Commands.h"


CCommands::CCommands(void)
{
	m_pMiniGame = nullptr;
	m_bIsGame = true;
}


CCommands::~CCommands(void)
{
	for(unsigned int i = 0; i < m_vCommands.size(); i++)
	{
		delete m_vCommands[i];
		m_vCommands[i] = nullptr;
	}

	m_vCommands.clear();
	if(m_pMiniGame != nullptr)
	{
		delete m_pMiniGame;
		m_pMiniGame = nullptr;
	}
}
