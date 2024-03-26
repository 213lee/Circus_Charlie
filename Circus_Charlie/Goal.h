#pragma once
#include "BitMapManager.h"

enum class GOAL
{
	FIXD_Y = 300,		//고정으로 그려지는 Y좌표

	HIT_ADD_Y = -15,	//히트박스 top위치 설정을 위해 더해지는 값
	HIT_HEIGHT = 30		//히트박스 높이
};

class Goal
{
private:
	BitMap* m_Bmp;			//BMP
	Position m_Position;	//그려질 좌표
	RECT m_HitRect;			//골인지점 히트박스
	int m_iWidth;			//골인 BMP 히트박스 가로 세로
public:
	Goal() {};
	~Goal() {};
	void Init();
	bool Update(float fDistance, RECT* character_rect);	//골인지점에 도착하면 true 반환
	void Draw(HDC hdc);
};

