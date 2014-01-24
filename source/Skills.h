#pragma once
#include "entity.h"
class CSkills :
	public CEntity
{
	CObjects* m_pTarget;
public:


	void SetTarget(CObjects* pTarget);
	CSkills(void);
	virtual ~CSkills(void);
	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual void Update(float fElapsedTime) override;

};

