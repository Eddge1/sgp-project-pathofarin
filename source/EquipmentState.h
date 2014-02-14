#pragma once
#include "GameStates.h"
#include "PlayerUnit.h"
class CEquipmentState :	public CGameStates
{
	CEquipmentState(void);
	virtual ~CEquipmentState(void);
	CEquipmentState( const CEquipmentState& );
	CEquipmentState& operator= ( const CEquipmentState& );
	CPlayerUnit * m_pPlayer;

	int m_nWeapon1ID;
	int m_nWeapon2ID;
	int m_nWeapon3ID;
	int m_nArmor1ID;
	int m_nArmor2ID;
	int m_nArmor3ID;
	int m_nAugment1ID;
	int m_nAugment2ID;
	int m_nAugment3ID;
	int m_nAugment4ID;

	int m_nEquippedWeapon;
	int m_nEquippedArmor;
	int m_nEquippedAugment;

	int m_nUnusedSlotID;
	int m_nUsedSlotID;
	int m_nEquipmentCursorID;
	int m_nArmorSelection;
	int m_nWeaponSelection;
	int m_nAugmentSelection;
	int m_nItemSelection;
	int m_nGearSelection;
	int m_nTotalItems;
	int m_nHealthBar;
	int m_nHealthBarPlate;
	bool m_bSubMenu;
	map<string, InventoryItems>* m_vInventory;
public:
	static CEquipmentState* GetInstance( void );
	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;						// unload resources
	virtual void Update( float fElapsedTime )	override;		// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;	
};

