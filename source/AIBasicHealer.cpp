#include "AIBasicHealer.h"


CAIBasicHealer::CAIBasicHealer(void)
{
	m_pTarget = nullptr;
	m_nTurns = 0;
}


CAIBasicHealer::~CAIBasicHealer(void)
{
}

void CAIBasicHealer::Update(float fElapsedTime)
{
	m_vBattleUnits = CBattleState::GetInstance()->GetBattleUnits();

	if(m_nTurns > 3 && GetOwner()->GetHealth() < GetOwner()->GetMaxHealth() / 2)
	{
		int tempRestore = GetOwner()->GetMaxHealth() / 3; // TODO: add random values
		GetOwner()->ModifyHealth(-tempRestore, false);
		m_pTarget = nullptr;
		m_nTurns = 0;
		GetOwner()->EndTurn();
	}
	else
	{
		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_PLAYER_UNIT)
				m_pTarget = m_vBattleUnits[i];
		}
		if(m_pTarget != nullptr)
		{
			m_pTarget->ModifyHealth(GetOwner()->GetAttack(), false);
			m_pTarget = nullptr;
			m_nTurns += 1;
			GetOwner()->EndTurn();
		}
	}
}

void CAIBasicHealer::Render(void)
{

}
