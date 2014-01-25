#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "AnimationSystem.h"
#include "Animation.h"
#include "AnimationTimeStamp.h"
#include "Frame.h"
#include "..\TinyXML\tinyxml.h"
#include <sstream>

CAnimationSystem* CAnimationSystem::s_pInstance = nullptr;

// GetInstance
CAnimationSystem* CAnimationSystem::GetInstance( void ) // Remember these are static.
{

	// Allocate the static pointer if necessary
	if( s_pInstance == nullptr )
		s_pInstance = new CAnimationSystem;

	// Return the singleton
	return s_pInstance;
}

// DeleteInstance
void CAnimationSystem::DeleteInstance( void )
{
	delete s_pInstance;
	s_pInstance = nullptr;
}


CAnimationSystem::CAnimationSystem(void)
{

}


CAnimationSystem::~CAnimationSystem(void)
{
	for (auto i = loadedAnimation.begin(); i != loadedAnimation.end(); ++i)
	{
		delete i->second;
	}
}

void CAnimationSystem::LoadAnimations(std::string filePath)
{
	TiXmlDocument doc;

	if (doc.LoadFile(filePath.c_str()) == false)
		return;

	TiXmlElement* pRoot = doc.RootElement();
	if (pRoot == nullptr)
		return;

	std::string szTempName;
	int nFrames;

	TiXmlElement* pAnim = pRoot->FirstChildElement("Animation_Info");
	if (pAnim != nullptr)
	{
		CAnimation* pTempAnim = new CAnimation;
		szTempName = pAnim->Attribute("Name");
		pAnim->Attribute("Frames", &nFrames);
		pTempAnim->SetAnimationName(szTempName);

		int nRepeatValue;
		pAnim->Attribute("repeat", &nRepeatValue);
		if (nRepeatValue == 0)
			pTempAnim->SetLooping(false);
		else
			pTempAnim->SetLooping(true);
		std::wostringstream woss;
		std::string szFileName;
		szFileName = pAnim->Attribute("Texture");
		woss << "assets/graphics/sprites/" << szFileName.c_str();
		pTempAnim->SetImageID(CSGD_TextureManager::GetInstance()->LoadTexture(woss.str().c_str()));
		pAnim = pAnim->FirstChildElement("Frame_Data");
		if (pAnim != nullptr)
		{
			pAnim = pAnim->FirstChildElement("Render");
			if (pAnim != nullptr)
			{
				for (int i = 0; i < nFrames; i++)
				{

					RECT rTempRenderRect = { };
					int left, top, right, bottom;
					int nAnchorX, nAnchorY;
					double dDuration;
					pAnim->Attribute("posX", &left);
					pAnim->Attribute("posY", &top);
					pAnim->Attribute("Width", &right);
					pAnim->Attribute("Height", &bottom);
					pAnim->Attribute("anchorX", &nAnchorX);
					pAnim->Attribute("anchorY", &nAnchorY);
					pAnim->Attribute("Duration", &dDuration);

					rTempRenderRect.left = left;
					rTempRenderRect.top = top;
					rTempRenderRect.right = right;
					rTempRenderRect.bottom = bottom;

					pAnim = pAnim->NextSiblingElement("ActiveCollision");
					RECT rTempCollisionRect = { };
					if (pAnim != nullptr)
					{

						pAnim->Attribute("posX", &left);
						pAnim->Attribute("posY", &top);
						pAnim->Attribute("Width", &right);
						pAnim->Attribute("Height", &bottom);

						rTempCollisionRect.left = left;
						rTempCollisionRect.top = top;
						rTempCollisionRect.right = right;
						rTempCollisionRect.bottom = bottom;

					}
					CFrame* temp = new CFrame;
					temp->SetRenderRect(rTempRenderRect);
					temp->SetAnchor(nAnchorX, nAnchorY);
					temp->SetCollisionRect(rTempCollisionRect);
					temp->SetDuration(dDuration);
					pTempAnim->AddAnimation(temp);
					pAnim = pAnim->NextSiblingElement("Render");
				}
			}
		}
		loadedAnimation[szTempName] = pTempAnim;

	}

}

void CAnimationSystem::Render(CAnimationTimeStamp* aTimeStamp, float fPosX, float fPosY, float fScale, DWORD dwColor)
{
	RECT rFrame = loadedAnimation[aTimeStamp->GetCurrentAnimation()]->GetFrames()[aTimeStamp->GetCurrentFrame()]->GetRenderRect();
	int nAnchorX = loadedAnimation[aTimeStamp->GetCurrentAnimation()]->GetFrames()[aTimeStamp->GetCurrentFrame()]->GetAnchorX();
	int nAnchorY = loadedAnimation[aTimeStamp->GetCurrentAnimation()]->GetFrames()[aTimeStamp->GetCurrentFrame()]->GetAnchorY();

	CSGD_TextureManager::GetInstance()->Draw(
		loadedAnimation[aTimeStamp->GetCurrentAnimation()]->GetImageID(), 
		(int)(fPosX - (nAnchorX * fScale)),
		(int)(fPosY - (nAnchorY * fScale)), 
		fScale, fScale, &rFrame, 
		0.0f, 0.0f, 0.0f, dwColor);
}

void CAnimationSystem::Update(CAnimationTimeStamp* aTimeStamp, float fElapsedTime)
{
	CAnimation* pAnim = loadedAnimation[aTimeStamp->GetCurrentAnimation()];
	CFrame* pFrame = pAnim->GetIndividualFrame(aTimeStamp->GetCurrentFrame());
	float fDuration = pFrame->GetDuration();
	aTimeStamp->SetTimeOnStamp(aTimeStamp->GetTimeOnStamp() + fElapsedTime);
	if (aTimeStamp->GetTimeOnStamp() > fDuration)
	{
		aTimeStamp->AdvanceCurrentFrame();
		aTimeStamp->SetTimeOnStamp(0.0f);
	}
}