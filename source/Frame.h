#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

class CFrame
{
	int m_nAnchorX;
	int m_nAnchorY;
	float m_fDuration;
	RECT m_rRender;
	RECT m_rCollision;
	std::string m_szEvent;

public:
	CFrame(void);
	virtual ~CFrame(void);

	//Accessors:
	int GetAnchorX() { return m_nAnchorX; }
	int GetAnchorY() { return m_nAnchorY; }
	float GetDuration() { return m_fDuration; }
	RECT GetRenderRect() { return m_rRender; }
	RECT GetCollisionRect() { return m_rCollision; }
	std::string GetEventID() { return m_szEvent; }

	//Mutators:
	RECT SetRenderRect(RECT rRect) { m_rRender = rRect; }
};

