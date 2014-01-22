#pragma once
#include "entity.h"
class CSkills :
	public CEntity
{
public:
	CSkills(void);
	virtual ~CSkills(void);
	virtual void HandleEvent( const CEvent* pEvent ) override;

};

