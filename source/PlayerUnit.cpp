#include "PlayerUnit.h"
#include "../SGD Wrappers/CSGD_DirectInput.h"
#include "../SGD Wrappers/CSGD_XAudio2.h"
#include "BattleState.h"
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "Player.h"
#include "TutorialBattle.h"

CPlayerUnit::CPlayerUnit(void)
{
	SetType(OBJ_PLAYER_UNIT);
	SetClass(UC_WARRIOR);
	m_bInSubMenu = false;
	m_bSkillSelected = false;
	m_bCasting = false;
	m_bDodge = false;
	m_nMenuSelect = 0;
	m_nSkillSelect = 0;
	m_pPlayer = nullptr;
	m_bDodge = false;
	timer = 0.0f;
	CSGD_EventSystem::GetInstance()->RegisterClient("DODGE", this);
	m_nSelectionChange = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_SelectionMove.wav"));
	m_nSelectionConfirm = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_SelectionConfirm.wav"));
	m_nSelectionBack = CSGD_XAudio2::GetInstance()->SFXLoadSound(_T("assets/Audio/SFX/POA_SelectionBack.wav"));

	m_pEquippedArmor	= nullptr;
	m_pEquippedWeapon	= nullptr;
	m_pEquippedAugment	= nullptr;

	m_nHealthMod = 0;
	m_nAttackMod = 0;
	m_nAPMod = 0;
	m_nSpeedMod = 0;
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
	m_pEquippedArmor	= nullptr;
	m_pEquippedWeapon	= nullptr;
	m_pEquippedAugment	= nullptr;
}

void CPlayerUnit::HandleEvent( const CEvent* pEvent )
{
	if(pEvent->GetEventID() == "DODGE")
	{
		m_bDodge = false;
		timer = 1.0f;
		std::wostringstream woss;
		woss << "Attempt ";
		if(!GetTutorial())
			CBattleState::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,255), woss);
		else
			CTutorialBattle::GetInstance()->AddFloatingText(GetPosX(), GetPosY(), D3DCOLOR_XRGB(0,255,255), woss);

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
					{
						if(GetAbilityPoints() >= m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->GetCost())
						{
							m_bSkillSelected = true;
						}

					}
					else
					{
						if(m_vCommands[m_nMenuSelect]->GetIsGame())
						{
							if(GetAbilityPoints() >= m_vCommands[m_nMenuSelect]->GetMiniGame()->GetCost())
							{
								if(m_nMenuSelect == 4)
									m_bCasting = true;

								m_bSkillSelected = true;
							}
						}
						else
							m_bInSubMenu = true;
					}
				}
				else if(pDI->KeyPressed(DIK_ESCAPE))
				{
					if(m_bInSubMenu == true)
					{
						m_bInSubMenu = false;
						CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionBack);

					}
				}
			}
			else
			{
				if(pDI->KeyPressed(DIK_RETURN))
				{
					CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionConfirm);
					if(m_bInSubMenu)
					{
						m_bCasting = true;
						ModifyAP(m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->GetCost());
					}
					else
					{
						m_bCasting = true;
						ModifyAP(m_vCommands[m_nMenuSelect]->GetMiniGame()->GetCost());
					}
				}
				else if(pDI->KeyPressed(DIK_ESCAPE))
				{
					m_bSkillSelected = false;
					CSGD_XAudio2::GetInstance()->SFXPlaySound(m_nSelectionBack);
				}

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
	if(timer <= -0.4f)
		m_bDodge = false;

	CEntity::Update(fElapsedTime);
}

void CPlayerUnit::EndTurn()
{
	if(m_bInSubMenu)
	{
		m_vCommands[m_nMenuSelect]->GetCommand(m_nSkillSelect)->GetMiniGame()->ResetSkill();
	}
	else
	{
		m_vCommands[m_nMenuSelect]->GetMiniGame()->ResetSkill();
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

void CPlayerUnit::ModifyHealth(int nAmount, bool isCrit, bool inMenu)
{
	if(!inMenu)
	{
		if(m_bDodge == true)
		{
			m_bDodge = false;
			this->GetAnimInfo()->SetAnimation("Dodge");
			CUnits::ModifyHealth(0, false);
		}
		else
		{

			if(nAmount > 0)
				this->GetAnimInfo()->SetAnimation("Warrior_Battle_Taking_Damage");
			CUnits::ModifyHealth(nAmount, isCrit, inMenu);
			timer = 0.0f;
		}
	}
	else
		CUnits::ModifyHealth(nAmount, isCrit, inMenu);
}

void CPlayerUnit::EquipArmor(CArmor* pArmor)
{
	if(pArmor == nullptr)
		return;
	if(m_pEquippedArmor != nullptr && pArmor->GetName() == m_pEquippedArmor->GetName())
	{
		m_nHealthMod -= int(pArmor->GetHpStat());
		m_nAttackMod -= int(pArmor->GetAttkStat());
		m_nSpeedMod -=  int(pArmor->GetSpeedStat());

		m_pEquippedArmor = nullptr;
	}
	else
	{
		if(m_pEquippedArmor != nullptr)
		{
			m_nHealthMod -= int(m_pEquippedArmor->GetHpStat());
			m_nAttackMod -= int(m_pEquippedArmor->GetAttkStat());
			m_nSpeedMod  -= int(m_pEquippedArmor->GetSpeedStat());
		}
		m_pEquippedArmor = pArmor;

		m_nHealthMod += int(pArmor->GetHpStat());
		m_nAttackMod += int(pArmor->GetAttkStat());
		m_nSpeedMod  += int(pArmor->GetSpeedStat());
	}
}

void CPlayerUnit::EquipWeapon(CWeapon* pWeapon)
{
	if(pWeapon == nullptr)
		return;

	if(m_pEquippedWeapon != nullptr && pWeapon->GetName() == m_pEquippedWeapon->GetName())
	{
		m_nAttackMod -= int(pWeapon->GetAttack());
		m_pEquippedWeapon = nullptr;
	}
	else
	{
		if(m_pEquippedWeapon != nullptr)
			m_nAttackMod -= int(m_pEquippedWeapon->GetAttack());
		m_pEquippedWeapon = pWeapon;
		m_nAttackMod += int(m_pEquippedWeapon->GetAttack());
	}
}

void CPlayerUnit::EquipAugment(CAugment* pAugment)
{
	if(pAugment == nullptr)
		return;
	if(m_pEquippedAugment != nullptr && pAugment->GetName() == m_pEquippedAugment->GetName())
	{
		if(pAugment->GetAugType() == "HP")
			m_nHealthMod -= int(pAugment->GetEffect());
		else if(pAugment->GetAugType() == "ATTK")
			m_nAttackMod -= int(pAugment->GetEffect());
		else if(pAugment->GetAugType() == "AP")
			m_nAPMod -= int(pAugment->GetEffect());
		else if(pAugment->GetAugType() == "SPEED")
			m_nSpeedMod -= int(pAugment->GetEffect());


		m_pEquippedAugment = nullptr;
	}
	else
	{
		if(m_pEquippedAugment != nullptr)
		{
			if(m_pEquippedAugment->GetAugType() == "HP")
				m_nHealthMod -= int(m_pEquippedAugment->GetEffect());
			else if(m_pEquippedAugment->GetAugType() == "ATTK")
				m_nAttackMod -= int(m_pEquippedAugment->GetEffect());
			else if(m_pEquippedAugment->GetAugType() == "AP")
				m_nAPMod -= int(m_pEquippedAugment->GetEffect());
			else if(m_pEquippedAugment->GetAugType() == "SPEED")
				m_nSpeedMod -= int(m_pEquippedAugment->GetEffect());

		}
		m_pEquippedAugment = pAugment;

		if(m_pEquippedAugment->GetAugType() == "HP")
			m_nHealthMod += int(m_pEquippedAugment->GetEffect());
		else if(m_pEquippedAugment->GetAugType() == "ATTK")
			m_nAttackMod += int(m_pEquippedAugment->GetEffect());
		else if(m_pEquippedAugment->GetAugType() == "AP")
			m_nAPMod += int(m_pEquippedAugment->GetEffect());
		else if(m_pEquippedAugment->GetAugType() == "SPEED")
			m_nSpeedMod += int(m_pEquippedAugment->GetEffect());
	}
}


