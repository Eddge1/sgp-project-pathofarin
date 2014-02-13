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

	int m_nUnusedSlotID;
	int m_nUsedSlotID;
	int m_nEquipmentCursorID;
	int m_nArmorSelection;
	int m_nWeaponSelection;
	int m_nAugmentSelection;
	int m_nItemSelection;
	int m_nGearSelection;
	bool m_bSubMenu;
public:
	static CEquipmentState* GetInstance( void );
	virtual void Activate( void )	override;					// load resources
	virtual void Sleep( void )	override;						// unload resources
	virtual void Update( float fElapsedTime )	override;		// update the state
	virtual void Render( void )	override;	
	virtual bool Input( void )	override;	
};

