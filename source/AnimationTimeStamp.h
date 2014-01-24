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
	void AdvanceCurrentFrame();
	void SetAnimation(std::string szAnimName) { m_szCurrentAnimation = szAnimName; }
	void SetCurrentFrame(int nCurrFrame) { m_nCurrFrame = nCurrFrame; }
	void SetTimeOnStamp(float fTime) { m_fTimeOnStamp = fTime; }

};

