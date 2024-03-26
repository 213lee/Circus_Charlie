#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_parrBitMap = new BitMap[(int)IMAGE::END];
}


void BitMapManager::Init(HDC hdc)
{
	char buf[256];

	//TITLE BITMAP LOAD (TITLE, STAR)
	for (int i = (int)IMAGE::TITLE_1; i <= (int)IMAGE::TITLE_4; i++)
	{
		sprintf_s(buf, "RES//title_%d.bmp", i + 1);
		m_parrBitMap[i].Init(hdc, buf);
	}

	//TITLE BITMAP LOAD (MENU)
	for (int i = (int)IMAGE::MENU_1; i <= (int)IMAGE::MENU_5; i++)
	{
		sprintf_s(buf, "RES//menu_%d.bmp", i - (int)IMAGE::MENU_1 + 1);
		m_parrBitMap[i].Init(hdc, buf);
	}

	//TITLE BITMAP LOAD (POINT)
	sprintf_s(buf, "RES//point.bmp");
	m_parrBitMap[(int)IMAGE::POINT].Init(hdc, buf);

	//BACKGROUND BITMAP LOAD
	sprintf_s(buf, "RES//back_1.bmp");
	m_parrBitMap[(int)IMAGE::BACK_1].Init(hdc, buf, (int)WINDOW_SIZE::WIDTH, 190);

	for (int i = (int)IMAGE::BACK_2; i < (int)IMAGE::GOAL; i++)
	{
		sprintf_s(buf, "RES//back_%d.bmp", i - (int)IMAGE::BACK_1 + 1);
		m_parrBitMap[i].Init(hdc, buf);
	}

	//GOAL
	sprintf_s(buf, "RES//goal.bmp");
	m_parrBitMap[(int)IMAGE::GOAL].Init(hdc, buf);

	//CHARACTER(PLAYER) BITMAP LOAD
	for (int i = (int)IMAGE::PLAYER_1; i < (int)IMAGE::PLAYER_END; i++)
	{
		sprintf_s(buf, "RES//player_%d.bmp", i - (int)IMAGE::PLAYER_1 + 1);
		m_parrBitMap[i].Init(hdc, buf);
	}

	//FIRE BITMAP LOAD
	for (int i = (int)IMAGE::FIRE_1; i < (int)IMAGE::FIRE_END; i++)
	{
		sprintf_s(buf, "RES//fire_%d.bmp", i - (int)IMAGE::FIRE_1 + 1);
		m_parrBitMap[i].Init(hdc, buf);
	}

	//RING BITMAP LOAD
	for (int i = (int)IMAGE::RING_1; i <= (int)IMAGE::RING_4; i++)
	{
		sprintf_s(buf, "RES//ring_%d.bmp", i - (int)IMAGE::RING_1 + 1);
		m_parrBitMap[i].Init(hdc, buf);
	}

	//CASH BITMAP LOAD
	sprintf_s(buf, "RES//cash.bmp");
	m_parrBitMap[(int)IMAGE::CASH].Init(hdc, buf);

	//INTERFACE BITMAP LOAD
	for (int i = (int)IMAGE::INTER_1; i < (int)IMAGE::INTER_END; i++)
	{
		sprintf_s(buf, "RES//interface_%d.bmp", i - (int)IMAGE::INTER_1 + 1);
		m_parrBitMap[i].Init(hdc, buf);
	}


}

BitMapManager::~BitMapManager()
{
	delete[] m_parrBitMap;
}
