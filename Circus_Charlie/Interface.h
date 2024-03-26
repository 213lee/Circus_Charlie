#pragma once
#include "BitMapManager.h"

enum class SCOREBOX
{
	START,
	BOX = 0,
	LIFE,
	COUNT
};

enum class SCOREBOX_POS
{
	//박스 그려질 좌표
	BOX_X = 40,
	BOX_Y = 10,

	//스코어 그려질 좌표
	SCORE_X = 160,
	SCORE_Y = 25,

	//보너스 그려질 좌표
	BONUS_X = 450,
	BONUS_Y = 25,

	//Life 그려지는 시작 좌표
	LIFE_X = 800,
	LIFE_Y = 45
};

enum class DISTANCE_POS
{
	
	START_X = 20,		//DISTANCE 초기 X
	FIXED_Y = 360,		//DISTANCE 고정 Y

	TEXT_ADD_X = 20,				//DISTANCE text 그리기위해 더해지는 값
	TEXT_FIXED_Y = FIXED_Y + 5		//DISTANCE text 그리기위해 고정된 Y값
};

enum class FONT_SIZE
{
	SCORE = 30,
	DISTANCE = 20
};

class ScoreBox
{
private:
	BitMap* m_Bmp[(int)SCOREBOX::COUNT];
	HFONT m_font, m_oldfont;				//Font
	std::wstring m_strScore, m_strBonus;	//Score, Bonus string
	std::wstring m_strMessage;					//게임 오버, 클리어 시 출력 메세지 string
	bool m_bMessage;						//메시지를 출력해야할 때 true
	int m_iLifeWidth;						//Life BMP 가로 크기
public:
	ScoreBox() {};
	~ScoreBox();
	void Init();
	void Update(int score, int bonus);
	void Draw(HDC hdc, int life);
	void StartSet()
	{
		m_bMessage = false;
	}
	void SetClear()
	{
		m_strMessage = L"CLEAR !";
		m_bMessage = true;
	}
};


class Distance
{
private:
	BitMap* m_Bmp;
	Position m_Position;
	HFONT m_font, m_oldfont;
	std::wstring m_strMeter;	//출력할 길이
	int m_iCurMeter;			//현재 그릴 Meter (10 = 100)
	int m_iWidth;				//Distance BMP 가로 크기
public:
	Distance() {};
	~Distance();
	void Init();
	void Update(float fDistance);
	void Draw(HDC hdc);
};





