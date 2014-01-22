#pragma once

#include <string>

class CAnimationTimeStamp
{
	std::string m_szCurrentAnimation;
	int m_nCurrFrame;
	float m_fTimeOnStamp;
public:
	CAnimationTimeStamp(void);
	virtual ~CAnimationTimeStamp(void);

	//Accessors:
	std::string GetCurrentAnimation() { return m_szCurrentAnimation; }
	int GetCurrentFrame() { return m_nCurrFrame; }
	float GetTimeOnStamp() { return m_fTimeOnStamp; }

	
};

