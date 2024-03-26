#pragma once
#include "BitMapManager.h"

enum class GREENBACK_POS
{
	FIXED_X = 0,		//�ʷϹ�濡 ������ X��
	FIXED_Y = 160		//�ʷϹ�濡 ������ Y��
};

//SCROLL�� ���Ǵ� BMP index
enum class BACKGROUND_IDX
{
	START = 0,
	GRENN = 0,					//�ʷϻ� ���
	ELEPHANT,			//�ڳ���
	AUDIENCE_1,				//�⺻ û��
	AUDIENCE_2,				//�ִϸ��̼� �ڼ�ġ�� ����
	COUNT
};

enum class SCROLL
{
	COUNT = 3,				//��ũ�Ѹ��� ����ϴ� ��ũ���� ����

	ELEPHANT = 2,			//��ũ�� �ϳ��� ���� �ڳ��� BMP ��
	AUDIENCE = 12,			//��ũ�� �ϳ��� ���� ���� BMP ��

	TOTAL_SCROLL = ELEPHANT + AUDIENCE	//�ϳ��� ��ũ�ѿ� ���� bmp ��
};


class BackGround
{
private:
	BitMap* m_arrBmp[(int)BACKGROUND_IDX::COUNT];					
	Position m_Position;			//��ũ���� �׷��� ��ǥ
	BACKGROUND_IDX m_eAudienceIdx;	//���� �� �ִϸ��̼ǿ��� SCROLL���� ������ �׸� �� ���� index
	int m_iBmpWidth;				//��ũ�� BMP �ϳ��� ���� ũ��
	int m_iScrollWidth;				//��ũ�� �ϳ��� ũ��
	int m_iCurStartX;				//���� ��ũ���� ���۵Ǵ� x��ǥ
	float m_fTimer;					//Scroll �ִϸ��̼��� ���� Ÿ�̸�
public:
	BackGround() {};
	~BackGround() {};
	void Init();
	void Update(float deltaTime, float fDistance, bool bIsGoal);
	void Draw(HDC hdc);
	void StartSet()		//���ӽ��۽� �⺻�������� ����
	{
		m_eAudienceIdx = BACKGROUND_IDX::AUDIENCE_1;
	}
};

