#pragma once
#include <string>
using namespace std;

class CTile
{

	int m_nX;
	int m_nY;
	bool m_bisEvent;
	string m_sEvent;

public:


	// Access/Muts
	int GetTileX( void) { return m_nX; }
	void SetTileX(int t) { m_nX = t; }
	int GetTileY(void) { return m_nY; }
	void SetTileY(int t) { m_nY = t; }
	bool IsEvent(void) { return m_bisEvent; }
	void SetEvent(bool t) { m_bisEvent = t; }
	void SetEventID(string t) { m_sEvent = t; }


	CTile(void);
	~CTile(void);
};

