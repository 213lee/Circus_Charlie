#pragma once

#include <Windows.h>
#include<string>

#pragma comment(lib, "msimg32.lib")

enum class WINDOW_SIZE
{
	WIDTH = 910,
	HEIGHT = 440
};

enum class DISTANCE
{
	INITIAL = 0,					//게임 시작 위치
	TEN_METER = 1000,				//10M 거리
	GOAL = TEN_METER * 10 + INITIAL,			//골인지점 거리
	CHARACTER_MOVE = GOAL - 700		//골인지점 앞 캐릭터가 움직이기 시작하는 거리
	
};

enum class SPEED
{
	CHARACTER_MOVE = 200,		//캐릭터 이동 속도
	CHARACTER_JUMP = 250,		//캐릭터 점프 속도

	RING_MOVE = 100,				//불꽃링 이동 속도
	SMALL_RING_MOVE = 160			//작은 불꽃링 이동 속도
};

enum class CHARACTER_POS
{
	FIXED_X = 20,				//캐릭터가 직접 이동하기 이전에 캐릭터가 그려지는 X 고정좌표
		
	DEFAULT_Y = 280,			//바닥에 착지할때 Y좌표
	GOAL_Y = 240,				//단상에 착지할때 Y좌표
	TOP_Y = 175					//점프시 최대로 올라갔을 때 Y좌표
};

struct Position
{
	int m_ix, m_iy;
};
