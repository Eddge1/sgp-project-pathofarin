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
	int GetAnchorX() const { return m_nAnchorX; }
	int GetAnchorY() const { return m_nAnchorY; }
	float GetDuration() const { return m_fDuration; }
	RECT GetRenderRect() const { return m_rRender; }
	RECT GetCollisionRect() const { return m_rCollision; }
	std::string GetEventID() const { return m_szEvent; }

	//Mutators:
	void SetRenderRect(RECT rRect) { m_rRender = rRect; }
	void SetCollisionRect(RECT rRect) { m_rCollision = rRect; }
	void SetDuration(float fDuration) { m_fDuration = fDuration; }
	void SetAnchor(int anchorX, int anchorY) { m_nAnchorX = anchorX;
											   m_nAnchorY = anchorY;}
	void SetEventID(std::string szEvent) { m_szEvent = szEvent; }
};

