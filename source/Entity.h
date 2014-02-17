#pragma once
#include "objects.h"
class CEntity :	public CObjects
{
	float m_fVelX;
	float m_fVelY;
public:
	CEntity(void);
	virtual ~CEntity(void);
	virtual void Update(float fElapsedTime) override;

	void SetVelX	( float fVel )	{m_fVelX = fVel;}
	void SetVelY	( float fVel )	{m_fVelY = fVel;}

	float GetVelX	( void )		{return m_fVelX;}
	float GetVelY	( void )		{return m_fVelY;}

	virtual void HandleEvent( const CEvent* pEvent ) override;
	virtual RECT GetCollisionRect() final;
	virtual RECT GetCollisionRectNoCam();



};

