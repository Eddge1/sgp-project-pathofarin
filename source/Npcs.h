#pragma once
#include "entity.h"
class CNpcs :
	public CEntity
{
public:
	CNpcs(void);
	virtual ~CNpcs(void);

	virtual void HandleEvent( const CEvent* pEvent ) override;

};

