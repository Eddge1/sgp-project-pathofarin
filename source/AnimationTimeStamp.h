#pragma once

#include <string>

class CAnimationTimeStamp
{
	std::string m_szCurrentAnimation;
	int m_nCurrFrame;
	float m_fTimeOnStamp;
	bool m_bIsPaused;
public:
	CAnimationTimeStamp(void);
	virtual ~CAnimationTimeStamp(void);

	//Accessors:
	std::string GetCurrentAnimation() const { return m_szCurrentAnimation; }
	int GetCurrentFrame() const { return m_nCurrFrame; }
	float GetTimeOnStamp() const { return m_fTimeOnStamp; }
	bool GetPaused() const { return m_bIsPaused; }

	//Mutator:
	void AdvanceCurrentFrame();
	void SetAnimation(std::string szAnimName);
	void SetCurrentFrame(int nCurrFrame) { m_nCurrFrame = nCurrFrame; }
	void SetTimeOnStamp(float fTime) { m_fTimeOnStamp = fTime; }
	void Pause(bool bPaused) { m_bIsPaused = bPaused; }
};

