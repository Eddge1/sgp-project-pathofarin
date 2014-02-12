#pragma once
#include "projectile.h"
class CBuff : public CProjectile
{
public:
	CBuff(void);
	virtual ~CBuff(void);
	virtual void Update(float fElapsedTime);
	virtual void HandleCollision(CObjects* col) {}
	virtual void HandleEvent( const CEvent* pEvent ) override;
};

