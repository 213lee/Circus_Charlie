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
	//�ڽ� �׷��� ��ǥ
	BOX_X = 40,
	BOX_Y = 10,

	//���ھ� �׷��� ��ǥ
	SCORE_X = 160,
	SCORE_Y = 25,

	//���ʽ� �׷��� ��ǥ
	BONUS_X = 450,
	BONUS_Y = 25,

	//Life �׷����� ���� ��ǥ
	LIFE_X = 800,
	LIFE_Y = 45
};

enum class DISTANCE_POS
{
	
	START_X = 20,		//DISTANCE �ʱ� X
	FIXED_Y = 360,		//DISTANCE ���� Y

	TEXT_ADD_X = 20,				//DISTANCE text �׸������� �������� ��
	TEXT_FIXED_Y = FIXED_Y + 5		//DISTANCE text �׸������� ������ Y��
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
	std::wstring m_strMessage;					//���� ����, Ŭ���� �� ��� �޼��� string
	bool m_bMessage;						//�޽����� ����ؾ��� �� true
	int m_iLifeWidth;						//Life BMP ���� ũ��
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
	std::wstring m_strMeter;	//����� ����
	int m_iCurMeter;			//���� �׸� Meter (10 = 100)
	int m_iWidth;				//Distance BMP ���� ũ��
public:
	Distance() {};
	~Distance();
	void Init();
	void Update(float fDistance);
	void Draw(HDC hdc);
};





