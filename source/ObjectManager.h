#pragma once
#include <vector>

class CObjects;
class CAnimationSystem;

class CObjectManager
{
	typedef std::vector< CObjects* >	ObjectVector;
	typedef ObjectVector::iterator		ObjIterator;
	typedef std::vector< ObjectVector >	ObjectTable;
	ObjectTable m_vObjects;

	bool m_bIterating;
	CAnimationSystem* m_pDraw;

public:
	CObjectManager(void);
	~CObjectManager(void);

	void Update(float fElapsedTime);
	void Render(unsigned int nLayer);
	int FindItem(CObjects* pObject);
	void DeactiveObject(int nID, unsigned int nLayer);
	void ActivateAll(unsigned int nLayer);
	void AddObject(CObjects* pObject, unsigned int unLayer);
	void RemoveObject(CObjects* pObject);
	void HandleCollision(unsigned int unLayer1, unsigned int unLayer2);
	void RemoveAll();
};

