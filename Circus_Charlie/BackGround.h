#pragma once
#include "BitMapManager.h"

enum class GREENBACK_POS
{
	FIXED_X = 0,		//초록배경에 고정된 X값
	FIXED_Y = 160		//초록배경에 고정된 Y값
};

//SCROLL에 사용되는 BMP index
enum class BACKGROUND_IDX
{
	START = 0,
	GRENN = 0,					//초록색 배경
	ELEPHANT,			//코끼리
	AUDIENCE_1,				//기본 청중
	AUDIENCE_2,				//애니메이션 박수치는 관중
	COUNT
};

enum class SCROLL
{
	COUNT = 3,				//스크롤링에 사용하는 스크롤의 갯수

	ELEPHANT = 2,			//스크롤 하나에 들어가는 코끼리 BMP 수
	AUDIENCE = 12,			//스크롤 하나에 들어가는 관중 BMP 수

	TOTAL_SCROLL = ELEPHANT + AUDIENCE	//하나의 스크롤에 들어가는 bmp 수
};


class BackGround
{
private:
	BitMap* m_arrBmp[(int)BACKGROUND_IDX::COUNT];					
	Position m_Position;			//스크롤이 그려질 좌표
	BACKGROUND_IDX m_eAudienceIdx;	//골인 후 애니메이션에서 SCROLL에서 관중을 그릴 때 사용될 index
	int m_iBmpWidth;				//스크롤 BMP 하나의 가로 크기
	int m_iScrollWidth;				//스크롤 하나의 크기
	int m_iCurStartX;				//현재 스크롤이 시작되는 x좌표
	float m_fTimer;					//Scroll 애니메이션을 위한 타이머
public:
	BackGround() {};
	~BackGround() {};
	void Init();
	void Update(float deltaTime, float fDistance, bool bIsGoal);
	void Draw(HDC hdc);
	void StartSet()		//게임시작시 기본관중으로 설정
	{
		m_eAudienceIdx = BACKGROUND_IDX::AUDIENCE_1;
	}
};

