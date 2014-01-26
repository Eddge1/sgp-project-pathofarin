#include "Commands.h"


CCommands::CCommands(void)
{
}


CCommands::~CCommands(void)
{
	for(unsigned int i = 0; i < m_vCommands.size(); i++)
	{
		delete m_vCommands[i];
		m_vCommands[i] = nullptr;
	}

	m_vCommands.clear();
}
