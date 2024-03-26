#pragma once
#include "BitMapManager.h"

enum class GOAL
{
	FIXD_Y = 300,		//�������� �׷����� Y��ǥ

	HIT_ADD_Y = -15,	//��Ʈ�ڽ� top��ġ ������ ���� �������� ��
	HIT_HEIGHT = 30		//��Ʈ�ڽ� ����
};

class Goal
{
private:
	BitMap* m_Bmp;			//BMP
	Position m_Position;	//�׷��� ��ǥ
	RECT m_HitRect;			//�������� ��Ʈ�ڽ�
	int m_iWidth;			//���� BMP ��Ʈ�ڽ� ���� ����
public:
	Goal() {};
	~Goal() {};
	void Init();
	bool Update(float fDistance, RECT* character_rect);	//���������� �����ϸ� true ��ȯ
	void Draw(HDC hdc);
};

