#pragma once

#include <vector>

class CFrame;

class CAnimation
{
	int m_nImageID;
	std::vector<CFrame> m_vFrames;
	std::string m_szAnimationName;
	bool m_bLooping;

public:
	CAnimation(void);
	virtual ~CAnimation(void);

	int GetImageID() { return m_nImageID; }
	std::vector<CFrame> GetFrames() { return m_vFrames; }
	std::string GetAnimationName() { return m_szAnimationName; }
	bool isLooping() { return m_bLooping; }

	void SetImageID(int nID) { m_nImageID = nID; }
	void SetFrames(std::vector<CFrame> vFrames) { m_vFrames = vFrames; }
	void SetAnimationName(std::string szName) { m_szAnimationName = szName; }
	void SetLooping(bool bLooping) { m_bLooping = bLooping; }


};

