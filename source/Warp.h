#pragma once
#include "objects.h"
class CWarp : public CObjects
{
	int m_nX;
	int m_nY;
	std::string m_szMapName;
public:
	int GetWarpX() const {return m_nX;}
	int GetWarpY() const {return m_nY;}
	std::string GetMapName() const {return m_szMapName;}

	void SetWarpX( int nX )		 {m_nX = nX;}
	void SetWarpY( int nY )		 {m_nY = nY;}
	void SetMapName( std::string szName ) {m_szMapName = szName;}

	CWarp(void);
	virtual ~CWarp(void);
	virtual void HandleCollision(CObjects* col);

};

