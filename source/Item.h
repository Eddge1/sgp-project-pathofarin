#pragma once
enum ItemTypes {IT_UNDEFINE, IT_CONSUMABLE, IT_ARMOR, IT_WEAPON};

class CItem
{
	ItemTypes m_eType;
public:

	CItem(void);
	virtual ~CItem(void);
	virtual ItemTypes GetItemType() const final {return m_eType;}
	virtual void SetItemType(ItemTypes eType) final {m_eType = eType;}
};

