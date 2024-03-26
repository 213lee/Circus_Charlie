#pragma once
#include "BitMapManager.h"

enum class TITLE
{
	START,			//TITLE
	TITLE = 0,		//TITLE NAME
	STAR_1,			//STAR 1
	STAR_2,			//STAR 2
	STAR_3,			//STAR 3
	COUNT			//TITLE 갯수
};

enum class MENU
{
	START,
	MENU_1 = 0,		//PLAY SELECT	
	MENU_2,			//1 PLAYER A
	MENU_3,			//1 PLAYER B
	MENU_4,			//2 PLAYER A
	MENU_5,			//2 PLAYER B
	POINT,			//Cursor
	COUNT			//MENU 갯수
};

enum class TITLE_POS
{
	TITLE_NAME_Y = 70,				//TITLE NAME이 시작되는 Y
	
	PLAYER_SELECT_MENU_Y = 180,		//Player Select Menu 시작 Y

	PLAYER_AND_POINT_START_Y = 240,	//PLAYER 1, POINT가 그려지는 시작 Y

	//PLAYER SELECT MENU에서
	POINT_ADD_X = -20,		//POINT가 그려질 때 x에 더해지는 값
	PLAYER_ADD_X = 60		//PLAYER 1이 그려질 때 x에 더해지는 값
};

enum class STAR_COUNT
{
	HORIZONTAL = 15,	//가로 별 개수
	VERTICAL = 6		//세로 별 개수
};

class Title
{
private:
	BitMap* m_arrTitle[(int)TITLE::COUNT];		//TITLE Bitmap arr
	BitMap* m_arrMenu[(int)MENU::COUNT];		//MENU Bitmap arr
	
	float m_fTimer;								//별 시작 idx 바꿀때 사용되는 timer
	int m_iStartidx;							//별 시작 idx
	int m_iCursorY;								//Cursor 위치(0 ~ 3)

	RECT m_StarDrawRect;						//별이 그려지는 초기 위치를 저장하는 RECT

	int m_iTitle_Mid_X;							//TITLE NAME BMP가 중앙 정렬 되도록 하는 X 좌표
	int m_iStarGap;								//Star Bmp가 그려지는 간격(별 Bmp width + n)
	int m_iPlaySelet_Mid_X;						//PlayerSelect BMP가 중앙에 그려지는 X 좌표
	int m_iPlayer_Gap;							//플레이어 선택 메뉴 갭(플레이어 BMP Height + n)

	void DrawStar(HDC hdc);	//별만 그리는 함수
public:
	void Init();
	bool Update(float deltaTime);
	void Draw(HDC hdc);
	Title();
	~Title();
};

