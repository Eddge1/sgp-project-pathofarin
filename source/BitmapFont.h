#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>


struct CharDescriptor
{
	int m_nX, m_nY;
	int m_nWidth, m_nHeight;
	int m_nXOffset, m_nYOffset;
	int m_nXAdvance;
	int m_nPage;

	CharDescriptor();
};

struct CharSet
{
	std::string m_szFileName; 
	int m_nLineHeight;
	int m_nBase;
	int m_nWidth, m_nHeight;
	int m_nPages;
	CharDescriptor Chars[256];
};

class CBitmapFont
{
	int m_nImageID;
	int m_nMaxCharWidth;
	int m_nMaxCharHeight;
	CharSet m_Font;
public:
	CBitmapFont(void);
	~CBitmapFont(void);

	//Initialize and Shutdown
	void Initialize(std::string filePath);
	void Shutdown();

	//Parse XML to load font
	CharSet FontParser(std::string fileName);
	//Draw Text
	void Draw(const TCHAR* szOutput, int nX, int nY, float fScale, DWORD dwColor) const;




};

