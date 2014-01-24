#pragma once
#include "Frame.h"
#include <vector>



class CAnimation
{
	int m_nImageID;
	std::vector<CFrame*> m_vFrames;
	std::string m_szAnimationName;
	bool m_bLooping;

public:
	CAnimation(void);
	virtual ~CAnimation(void);

	int GetImageID() const { return m_nImageID; }
	std::vector<CFrame*> GetFrames() const { return m_vFrames; }
	std::string GetAnimationName() const { return m_szAnimationName; }
	bool isLooping() const { return m_bLooping; }
	CFrame* GetIndividualFrame(int nID) { return m_vFrames[nID]; }
	unsigned int GetSize() { return m_vFrames.size(); }


	void SetImageID(int nID) { m_nImageID = nID; }
	//void SetFrames(std::vector<CFrame*> vFrames) { m_vFrames = vFrames; }
	void AddAnimation(CFrame* pFrame) { m_vFrames.push_back(pFrame); }
	void SetAnimationName(std::string szName) { m_szAnimationName = szName; }
	void SetLooping(bool bLooping) { m_bLooping = bLooping; }


};

