#include "AITigerlily.h"


CAITigerlily::CAITigerlily(void)
{
	m_nTurns = 0;
	m_nAoeHeal = 0;
}


CAITigerlily::~CAITigerlily(void)
{
}


void CAITigerlily::Update(float fElapsedTime)
{

	m_vBattleUnits = CBattleState::GetInstance()->GetBattleUnits();
	vector<CUnits*> temp;

	if(m_nTurns >= 2)
	{

		int comrades = 0;



		for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
		{
			if(m_vBattleUnits[i]->GetType() == OBJ_ENEMY_UNIT)
			{
				comrades++;
				temp.push_back(m_vBattleUnits[i]);
			}
		}

		if(m_nAoeHeal >= 3)
		{
			if(comrades > 0)
			{
				bool hurt = false;

				for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
				{
					if(m_vBattleUnits[i]->GetType() == OBJ_ENEMY_UNIT)
					{
						if(m_vBattleUnits[i]->GetHealth() <= m_vBattleUnits[i]->GetMaxHealth() * 0.75)
						{
							hurt = true;
							break;
						}
						else if(GetOwner()->GetHealth() <= GetOwner()->GetMaxHealth() * 0.75)
						{
							hurt = true;
							break;
						}
					}
				}

				if(hurt)
				{

					for(unsigned int i = 0; i < m_vBattleUnits.size(); i++)
					{
						if(m_vBattleUnits[i]->GetType() == OBJ_ENEMY_UNIT)
						{
							m_vBattleUnits[i]->ModifyHealth(-m_vBattleUnits[i]->GetMaxHealth() / 3, false);
						}
					}
					GetOwner()->ModifyHealth(-GetOwner()->GetMaxHealth() / 3, false);
					wostringstream woss;
					woss << "AOE Heal";
					CBattleState::GetInstance()->AddFloatingText(GetOwner()->GetPosX(), GetOwner()->GetPosY(), D3DCOLOR_XRGB(250,0,0), woss);
					comrades = 0;
					m_nAoeHeal = 0;
					m_nTurns = 0;
					GetOwner()->EndTurn();
					return;
				}
				else
				{
					m_nAoeHeal++;
					m_nTurns++;
					GetMinigame()->SetOwner(GetOwner());
					GetMinigame()->Update(fElapsedTime);
					m_pTarget = nullptr;
					GetOwner()->EndTurn();
					return;
				}
			}
			else
			{
				if(GetOwner()->GetHealth() <= GetOwner()->GetMaxHealth() * 0.75)
				{
					GetOwner()->ModifyHealth(-GetOwner()->GetMaxHealth() / 3, false);
					comrades = 0;
					m_nTurns = 0;
					m_nAoeHeal++;
					GetOwner()->EndTurn();
					return;
				}
				else
				{
					m_nAoeHeal++;
					m_nTurns++;
					GetMinigame()->SetOwner(GetOwner());
					GetMinigame()->Update(fElapsedTime);
					m_pTarget = nullptr;
					GetOwner()->EndTurn();
					return;

				}
			}

		}
		else if(comrades > 0)
		{
			if(temp.size() > 0)
			{
				for(unsigned int i = 0; i < temp.size(); i++)
				{
					if(GetOwner()->GetHealth() < temp[i]->GetHealth())
					{
						GetOwner()->ModifyHealth(-GetOwner()->GetMaxHealth() / 3 , false);
						m_nTurns = 0;
						comrades = 0;
						m_nAoeHeal++;
						GetOwner()->EndTurn();
						return;
					}
				}

				if(comrades > 1)
				{


					if(temp.size() > 1)
					{
						if(temp[0]->GetHealth() > temp[1]->GetHealth())
						{
							temp[1]->ModifyHealth(-temp[1]->GetMaxHealth() / 3, false);
							m_nTurns = 0;
							comrades = 0;
							m_nAoeHeal++;
							GetOwner()->EndTurn();
							return;
						}
						else if(temp[0]->GetHealth() < temp[1]->GetHealth())
						{
							temp[0]->ModifyHealth(-temp[0]->GetMaxHealth() / 3, false);
							m_nTurns = 0;
							comrades = 0;
							m_nAoeHeal++;
							GetOwner()->EndTurn();
							return;
						}
						else
						{

							m_nAoeHeal++;
							m_nTurns++;
							GetMinigame()->SetOwner(GetOwner());
							GetMinigame()->Update(fElapsedTime);
							m_pTarget = nullptr;
							GetOwner()->EndTurn();
							return;


						}
					}
				}
				else if( comrades > 0)
				{
					temp[0]->ModifyHealth(-temp[0]->GetMaxHealth() / 3, false);
					m_nTurns = 0;
					comrades = 0;
					m_nAoeHeal++;
					GetOwner()->EndTurn();
					return;
				}
			}
		}
		else
		{
			if(GetOwner()->GetHealth() <= GetOwner()->GetMaxHealth() * 0.75)
			{
				GetOwner()->ModifyHealth(-GetOwner()->GetMaxHealth() / 3 , false);
				m_nTurns = 0;
				comrades = 0;
				m_nAoeHeal++;
				GetOwner()->EndTurn();
				return;
			}
			else
			{
				m_nAoeHeal++;
				m_nTurns++;
				GetMinigame()->SetOwner(GetOwner());
				GetMinigame()->Update(fElapsedTime);
				m_pTarget = nullptr;
				GetOwner()->EndTurn();
			}
		}
	}
	else
	{
		GetMinigame()->SetOwner(GetOwner());
		GetMinigame()->Update(fElapsedTime);
		m_nAoeHeal++;
		m_nTurns++;
		m_pTarget = nullptr;
		GetOwner()->EndTurn();
	}
}


void CAITigerlily::Render(void)
{

}