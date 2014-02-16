#include "../SGD Wrappers/CSGD_TextureManager.h"
#include "AnimationSystem.h"
#include "Animation.h"
#include "AnimationTimeStamp.h"
#include "Frame.h"
#include "..\TinyXML\tinyxml.h"
#include <sstream>
#include "../SGD Wrappers/CSGD_EventSystem.h"
#include "SplashScreen.h"
#include "Game.h"

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
	m_bEventThrown = false;
}


CAnimationSystem::~CAnimationSystem(void)
{
	for (auto i = loadedAnimation.begin(); i != loadedAnimation.end(); ++i)
	{
		delete i->second;
		i->second = nullptr;
	}
	loadedAnimation.clear();
}

void CAnimationSystem::LoadAnimations()
{
	//"assets/Data/Animations/"
	CAnimation* pTempAnim;
	CFrame* temp;
	WIN32_FIND_DATA fileSearch;
	HANDLE hFile;
	WCHAR cDirectory[] = L"assets/Data/Animations/*.xml";
	hFile = FindFirstFile(cDirectory,&fileSearch);
	std::string szLoadStatus = "";
	int nFileCount = 0;
	do
	{
		szLoadStatus = "";
		char cFile[128] = "assets/Data/Animations/";
		for(int i = 0; i < 128; i++)
		{
			cFile[i + 23] = char(fileSearch.cFileName[i]);
			szLoadStatus += char(fileSearch.cFileName[i]);
			if(fileSearch.cFileName[i] == '\0')
				break;
		}
		TiXmlDocument doc;
		CSplashScreen::GetInstance()->SetString(szLoadStatus);
		CSplashScreen::GetInstance()->SetPercentDone( nFileCount / 55.0f );
		CGame::GetInstance()->Render();
		if (doc.LoadFile(cFile) == false)
			return;

		TiXmlElement* pRoot = doc.RootElement();
		if (pRoot == nullptr)
			return;

		std::string szTempName;
		std::string szEvent;
		int nCount;
		int nFrames;
		TiXmlElement* pAnim = pRoot->FirstChildElement("Animation_Info");
		TiXmlElement* pBacktoRoot = pRoot->FirstChildElement("Animation_Info");
		if (pAnim != nullptr)
		{
			pRoot->Attribute("Count", &nCount);
			for (int i = 0; i < nCount; i++)
			{
				pTempAnim = new CAnimation;
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
							szEvent = pAnim->Attribute("Event");

							rTempRenderRect.left = left;
							rTempRenderRect.top = top;
							rTempRenderRect.right = left + right;
							rTempRenderRect.bottom = top + bottom;

							pAnim = pAnim->NextSiblingElement("ActiveCollision");
							RECT rTempCollisionRect = { };
							if (pAnim != nullptr)
							{
								pAnim->Attribute("posX", &left);
								pAnim->Attribute("posY", &top);
								pAnim->Attribute("Width", &right);
								pAnim->Attribute("Height", &bottom);

								rTempCollisionRect.left = left - nAnchorX;
								rTempCollisionRect.top = top - nAnchorY;
								rTempCollisionRect.right = right - nAnchorX;
								rTempCollisionRect.bottom = bottom - nAnchorY;
							}
							temp = new CFrame;
							temp->SetRenderRect(rTempRenderRect);
							temp->SetAnchor(nAnchorX, nAnchorY);
							temp->SetCollisionRect(rTempCollisionRect);
							temp->SetDuration((float)dDuration);
							temp->SetEventID(szEvent);
							pTempAnim->AddAnimation(temp);
							pAnim = pAnim->NextSiblingElement("Render");
						}
					}
				}
				loadedAnimation[szTempName] = pTempAnim;
				szTempName = "";
				pBacktoRoot = pBacktoRoot->NextSiblingElement("Animation_Info");
				pAnim = pBacktoRoot;
			}

		}
		nFileCount++;
	}while(FindNextFile(hFile, &fileSearch));

}

void CAnimationSystem::Render(CAnimationTimeStamp* aTimeStamp, float fPosX, float fPosY, float fScaleX, float fScaleY, DWORD dwColor)
{
	RECT rFrame = loadedAnimation[aTimeStamp->GetCurrentAnimation()]->GetFrames()[aTimeStamp->GetCurrentFrame()]->GetRenderRect();
	int nAnchorX = loadedAnimation[aTimeStamp->GetCurrentAnimation()]->GetFrames()[aTimeStamp->GetCurrentFrame()]->GetAnchorX();
	int nAnchorY = loadedAnimation[aTimeStamp->GetCurrentAnimation()]->GetFrames()[aTimeStamp->GetCurrentFrame()]->GetAnchorY();

	CSGD_TextureManager::GetInstance()->Draw(
		loadedAnimation[aTimeStamp->GetCurrentAnimation()]->GetImageID(), 
		(int)(fPosX - (nAnchorX * fScaleX)),
		(int)(fPosY - (nAnchorY * fScaleY)), 
		fScaleX, fScaleY, &rFrame, 
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
		m_bEventThrown = false;
		aTimeStamp->SetTimeOnStamp(0.0f);
	}

	if (pFrame->GetEventID() != "NULL" && m_bEventThrown == false)
	{
		m_bEventThrown = true;
		CSGD_EventSystem::GetInstance()->SendEventNow(pFrame->GetEventID(), nullptr, nullptr, aTimeStamp);
	}
}


