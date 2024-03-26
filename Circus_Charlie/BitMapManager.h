#pragma once
#include"BitMap.h"

enum class IMAGE
{
	START,
	//TITLE
	TITLE_1 = 0,	//TITLE NAME
	TITLE_2,		//STAR 1
	TITLE_3,		//STAR 2
	TITLE_4,		//STAR 3

	MENU_1,			//PLAY SELECT	
	MENU_2,			//1 PLAYER A
	MENU_3,			//1 PLAYER B
	MENU_4,			//2 PLAYER A
	MENU_5,			//2 PLAYER B
	POINT,			//Cursor
	TITLE_END,

	//BACKGROUND
	BACK_1 = TITLE_END,
	BACK_2,
	BACK_3,
	BACK_4,
	GOAL,
	BACK_END,
	
	//PLAYER
	PLAYER_1 = BACK_END,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	PLAYER_5,
	PLAYER_6,
	PLAYER_END,

	//FIRE
	FIRE_1 = PLAYER_END,
	FIRE_2,
	FIRE_END,

	//RING
	RING_1 = FIRE_END,
	RING_2,
	RING_3,
	RING_4,
	CASH,
	RING_END,

	//INTERFACE
	INTER_1 = RING_END,
	INTER_2,
	INTER_3,
	INTER_END,

	END = INTER_END
};

class BitMapManager
{
private:
	BitMap* m_parrBitMap;
	static BitMapManager* m_hThis;
	BitMapManager();
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	BitMap* GetImage(int index)
	{
		return &m_parrBitMap[index];
	}
	
	void Init(HDC hdc);
	~BitMapManager();
};

