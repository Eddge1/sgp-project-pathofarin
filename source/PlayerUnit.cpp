#include "PlayerUnit.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"

CPlayerUnit::CPlayerUnit(void)
{
	SetType(OBJ_PLAYER_UNIT);
	m_bInSubMenu = false;
	m_bSkillSelected = false;
	m_nMenuSelect = 0;
	m_nSkillSelect = 0;
}

CPlayerUnit::~CPlayerUnit(void)
{
	for(unsigned int i =0; i < m_vCommands.size(); i++)
	{
		delete m_vCommands[i];
		m_vCommands[i] = nullptr;
	}
	m_vCommands.clear();
}

void CPlayerUnit::HandleEvent( const CEvent* pEvent )
{


}

CMiniGames* CPlayerUnit::GetSkill(int nID)
{
	if(nID >= (int)m_vCommands.size())
		return nullptr;

	return m_vCommands[nID];

}

void CPlayerUnit::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(GetTurn())
	{
		



	}
}

