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
	INITIAL = 0,					//���� ���� ��ġ
	TEN_METER = 1000,				//10M �Ÿ�
	GOAL = TEN_METER * 10 + INITIAL,			//�������� �Ÿ�
	CHARACTER_MOVE = GOAL - 700		//�������� �� ĳ���Ͱ� �����̱� �����ϴ� �Ÿ�
	
};

enum class SPEED
{
	CHARACTER_MOVE = 200,		//ĳ���� �̵� �ӵ�
	CHARACTER_JUMP = 250,		//ĳ���� ���� �ӵ�

	RING_MOVE = 100,				//�Ҳɸ� �̵� �ӵ�
	SMALL_RING_MOVE = 160			//���� �Ҳɸ� �̵� �ӵ�
};

enum class CHARACTER_POS
{
	FIXED_X = 20,				//ĳ���Ͱ� ���� �̵��ϱ� ������ ĳ���Ͱ� �׷����� X ������ǥ
		
	DEFAULT_Y = 280,			//�ٴڿ� �����Ҷ� Y��ǥ
	GOAL_Y = 240,				//�ܻ� �����Ҷ� Y��ǥ
	TOP_Y = 175					//������ �ִ�� �ö��� �� Y��ǥ
};

struct Position
{
	int m_ix, m_iy;
};
