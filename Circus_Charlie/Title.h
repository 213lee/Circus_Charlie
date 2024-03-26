#pragma once
#include "BitMapManager.h"

enum class TITLE
{
	START,			//TITLE
	TITLE = 0,		//TITLE NAME
	STAR_1,			//STAR 1
	STAR_2,			//STAR 2
	STAR_3,			//STAR 3
	COUNT			//TITLE ����
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
	COUNT			//MENU ����
};

enum class TITLE_POS
{
	TITLE_NAME_Y = 70,				//TITLE NAME�� ���۵Ǵ� Y
	
	PLAYER_SELECT_MENU_Y = 180,		//Player Select Menu ���� Y

	PLAYER_AND_POINT_START_Y = 240,	//PLAYER 1, POINT�� �׷����� ���� Y

	//PLAYER SELECT MENU����
	POINT_ADD_X = -20,		//POINT�� �׷��� �� x�� �������� ��
	PLAYER_ADD_X = 60		//PLAYER 1�� �׷��� �� x�� �������� ��
};

enum class STAR_COUNT
{
	HORIZONTAL = 15,	//���� �� ����
	VERTICAL = 6		//���� �� ����
};

class Title
{
private:
	BitMap* m_arrTitle[(int)TITLE::COUNT];		//TITLE Bitmap arr
	BitMap* m_arrMenu[(int)MENU::COUNT];		//MENU Bitmap arr
	
	float m_fTimer;								//�� ���� idx �ٲܶ� ���Ǵ� timer
	int m_iStartidx;							//�� ���� idx
	int m_iCursorY;								//Cursor ��ġ(0 ~ 3)

	RECT m_StarDrawRect;						//���� �׷����� �ʱ� ��ġ�� �����ϴ� RECT

	int m_iTitle_Mid_X;							//TITLE NAME BMP�� �߾� ���� �ǵ��� �ϴ� X ��ǥ
	int m_iStarGap;								//Star Bmp�� �׷����� ����(�� Bmp width + n)
	int m_iPlaySelet_Mid_X;						//PlayerSelect BMP�� �߾ӿ� �׷����� X ��ǥ
	int m_iPlayer_Gap;							//�÷��̾� ���� �޴� ��(�÷��̾� BMP Height + n)

	void DrawStar(HDC hdc);	//���� �׸��� �Լ�
public:
	void Init();
	bool Update(float deltaTime);
	void Draw(HDC hdc);
	Title();
	~Title();
};

