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
	std::string GetCurrentAnimation() const { return m_szCurrentAnimation; }
	int GetCurrentFrame() const { return m_nCurrFrame; }
	float GetTimeOnStamp() const { return m_fTimeOnStamp; }

	//Mutator:
	void AdvanceCurrentFrame() { m_nCurrFrame++; }
};

