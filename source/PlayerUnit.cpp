#include "PlayerUnit.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "BattleState.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "Player.h"

CPlayerUnit::CPlayerUnit(void)
{
	SetType(OBJ_PLAYER_UNIT);
	SetClass(UC_WARRIOR);
	m_bInSubMenu = false;
	m_bSkillSelected = false;
	m_bCasting = false;
	m_nMenuSelect = 0;
	m_nSkillSelect = 0;
	m_pPlayer = nullptr;
	m_bDodge = false;
	timer = 1.0f;
	CSGD_EventSystem::GetInstance()->RegisterClient("DODGE", this);
	m_nSelectionChange = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_SelectionMove.wav"));
	m_nSelectionConfirm = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_SelectionConfirm.wav"));
	m_nSelectionBack = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_SelectionBack.wav"));

}

CPlayerUnit::~CPlayerUnit(void)
{
	for(unsigned int i =0; i < m_vCommands.size(); i++)
	{
		delete m_vCommands[i];
		m_vCommands[i] = nullptr;
	}
	m_vCommands.clear();
	SetOwner(nullptr);
}

void CPlayerUnit::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "DODGE")
	{
		timer = 1.0f;
		std::wostringstream woss;
		woss << "Attempt ";
		CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,255), woss);

	}
}

CCommands* CPlayerUnit::GetSkill(int nID)
{
	if(nID >= (int)m_vCommands.size())
		return nullptr;

	return m_vCommands[nID];
}

void CPlayerUnit::Update(float fElapsedTime)
{
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	if(GetTurn() )
	{
		if(m_bCasting == false)
		{
			if(m_bSkillSelected == false)
			{
				if(m_bInSubMenu)
				{
					if(pDI->KeyPressed(DIK_W))
					{
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionChange);
						m_nSkillSelect--;
						if(m_nSkillSelect < 0)
							m_nSkillSelect = (int)m_vCommands[m_nMenuSelect]->GetCommands()->size() - 1;
					}
					else if(pDI->KeyPressed(DIK_S))
					{
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionChange);
						m_nSkillSelect++;
						if(m_nSkillSelect >= (int)m_vCommands[m_nMenuSelect]->GetCommands()->size())
							m_nSkillSelect = 0;
					}
				}
				else
				{
					if(pDI->KeyPressed(DIK_W))
					{
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionChange);
						m_nMenuSelect--;
						if(m_nMenuSelect < 0)
							m_nMenuSelect = (int)m_vCommands.size() - 1;
					}
					else if(pDI->KeyPressed(DIK_S))
					{
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionChange);
						m_nMenuSelect++;
						if(m_nMenuSelect >= (int)m_vCommands.size())
							m_nMenuSelect = 0;
					}
				}
				if(pDI->KeyPressed(DIK_RETURN))
				{
					CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionConfirm);
					if(m_bInSubMenu)
						m_bSkillSelected = true;
					else
					{
						if(m_vCommands[m_nMenuSelect]->GetIsGame())
						{
							if(m_nMenuSelect == 2)
								m_bCasting = true;

							m_bSkillSelected = true;
						}
						else
							m_bInSubMenu = true;
					}
				}
				else if(pDI->KeyPressed(DIK_ESCAPE))
				{
					if(m_bInSubMenu == true)
						m_bInSubMenu = false;
				}
			}
			else
			{
				if(pDI->KeyPressed(DIK_RETURN))
				{
					CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionConfirm);
					if(m_bInSubMenu)
					{
						if(GetAbilityPoints() >= m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->GetCost())
						{
							m_bCasting = true;
							ModifyAP(m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->GetCost());
						}
					}
					else
					{
						if(GetAbilityPoints() >= m_vCommands[m_nMenuSelect]->GetMiniGame()->GetCost())
						{
							m_bCasting = true;
							ModifyAP(m_vCommands[m_nMenuSelect]->GetMiniGame()->GetCost());
						}
					}
				}
				else if(pDI->KeyPressed(DIK_ESCAPE))
					m_bSkillSelected = false;
			}
		}
		else
		{
			if(m_bInSubMenu)
			{
				m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->SetOwner(this);
				m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->Update(fElapsedTime);
			}
			else
			{
				m_vCommands[m_nMenuSelect]->GetMiniGame()->SetOwner(this);
				m_vCommands[m_nMenuSelect]->GetMiniGame()->Update(fElapsedTime);
			}
		}
	}

	timer -= fElapsedTime;

	if(timer > 0)
	{
		if(pDI->KeyPressed(DIK_RETURN))
		{
			m_bDodge = true;
		}

	}
	CEntity::Update(fElapsedTime);
}

void CPlayerUnit::EndTurn()
{
	if(m_bInSubMenu)
	{
		m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->ResetSkill();
		m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->SetOwner(nullptr);
	}
	else
	{
		m_vCommands[m_nMenuSelect]->GetMiniGame()->ResetSkill();
		m_vCommands[m_nMenuSelect]->GetMiniGame()->SetOwner(nullptr);
	}
	SetTurn(false);
	m_bSkillSelected = false;
	m_bInSubMenu = false;
	m_bCasting = false;
}

void CPlayerUnit::SetOwner(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

void CPlayerUnit::ModifyHealth(int nAmount, bool isCrit)
{
	if(m_bDodge == true)
	{
		CUnits::ModifyHealth(0, false);
		m_bDodge = false;
	}
	else
	{
		this->GetAnimInfo()->SetAnimation("Warrior_Battle_Taking_Damage");
		CUnits::ModifyHealth(nAmount, isCrit);
		timer = 0.0f;
	}
}

