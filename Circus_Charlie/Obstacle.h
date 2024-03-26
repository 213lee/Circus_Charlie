#pragma once
#include "BitMapManager.h"


enum class FIRE
{
	START = 0,
	FIRE_1 = 0,			//�׾Ƹ� 1
	FIRE_2,				//�׾Ƹ� 2
	COUNT
};

enum class FIRE_POS
{
	DRAW_Y = 295,			//�׾Ƹ��� �׷����� ���� Y��ǥ

	//��ֹ� ��Ʈ�ڽ�
	HIT_LEFT = 5,			//left�� �������� ��
	HIT_RIGHT = -10,		//right�� �������� ��
	HIT_TOP = 5,			//top�� �������� ��

	//���ھ� ��Ʈ�ڽ�
	SCORE_LEFT = 5,			//left�� �������� ��
	SCORE_RIGHT = 10,		//right�� �������� ��
};

enum class RING
{
	START = 0,
	LEFT_1 = 0,			//�Ҳɸ� ���� 1
	RIGHT_1,			//�Ҳɸ� ������ 1
	LEFT_2,				//�Ҳɸ� ���� 2
	RIGHT_2,			//�Ҳɸ� ������ 2
	CASH,
	COUNT
};

enum class RING_ANIMATION
{
	FIRST = 0,			//�� �ִϸ��̼�1�� �������� ��
	SECOND = 2			//�� �ִϸ��̼�2�� �������� ��
};

#define RING_COUNT 3	//���ӿ��� ����ϴ� �Ϲ� ���� ����

enum class RING_POS
{
	DRAW_Y = 160,			//�Ҳɸ��� �׷����� ���� Y��ǥ

	//��ֹ� ��Ʈ�ڽ�
	HIT_LEFT = -5,		//left�� �������� ��
	HIT_RIGHT = 10,		//right�� �������� ��
	HIT_TOP = -5,		//top�� �������� ��
	HIT_BOTTOM = 10,	//bottom�� �������� ��

	//���ھ� ��Ʈ�ڽ�
	SCORE_LEFT = -5,	//left�� �������� ��
	SCORE_RIGHT = 10,	//right�� �������� ��
	SCORE_TOP = 30,		//top�� �������� ��
	SCORE_BOTTOM = -50,	//bottom�� �������� �� 

	GAP_X = 700,						//�� �ϳ� ������ x ����
	RESET_ADD_X = GAP_X * RING_COUNT	//���� ĳ���� �ڷ� �������� �� �ٽ� ��ġ�� �����ϱ����� �������� ��
};

enum class CASH_POS
{
	ADD_X = -10,			//���ٹ��� �׸������� ���� �⺻ ��ǥ�� ������ x��
	ADD_Y = 20			//���ٹ��� �׸������� ���� �⺻ ��ǥ�� ������ y��
};

enum class HITBOX_TYPE
{
	OBSTACLE,		//��ֹ��� �ε����� ��
	PASS,			//��ֹ��� ������� ��
	NONE,			//�ƹ��͵� �ε�ġ�� �ʾ��� ��
	
	CASH			//���ٹ�
};

class Obstacle
{
protected:
	BitMap** m_Bmp;					//BitMap* ������ �迭 �����Ҵ��� ���� ���� ������
	Position m_Position;			//�׷��� ��ǥ
	RECT m_HitRect;					//��ֹ��� �浹������ ���� ��Ʈ�ڽ�
	RECT m_ScoreRect;				//��ֹ��� �Ѿ����� Ȯ���ϱ� ���� ��Ʈ�ڽ�
	bool m_bScore;					//���ھ� ��Ʈ�ڽ��� Ȱ��ȭ��Ű�� ���� flag
	float m_fTimer;					//Ÿ�̸�
	int m_iWidth, m_iHeight;		//BMP ����, ����ũ��

	virtual void Animation() abstract;
public:
	Obstacle() : m_bScore(false) {};
	virtual ~Obstacle() {};
	virtual void Init() abstract;
	HITBOX_TYPE HitCheck(RECT* character_rect);		//��ֹ��� �浹, ��� �˻�
};

//�� �׾Ƹ� ��ֹ�
class Fire : public Obstacle
{
private:
	int m_iCurX;				//���� �׸��� �����̵Ǵ� X 0, 1000, 2000, 3000 ...
	FIRE m_eAnimation;			//Animation �ε���
	
	void UpdateHitRect();
	void Animation() override;
public:
	Fire();
	~Fire();
	void Init() override;
	void Update(float deltaTime, float fDistance);
	void Draw(HDC hdc);
};

//�Ҳ� �� ��ֹ�
class Ring : public Obstacle
{
protected:
	int m_iSpeed;					//���� ������ ���ǵ�
	RING_ANIMATION m_eAnimationIdx;	//Animation �ε���
	
	virtual void UpdateHitRect();	//��ֹ��� ��Ʈ�ڽ� ��ǥ ������Ʈ
	void Reset_X();					//���� ĳ���� �ڷ� ������� �� X��ǥ�� ���� ��ġ �缳��
	void Animation() override;
public:
	Ring() : m_eAnimationIdx(RING_ANIMATION::FIRST) {};
	~Ring();
	void Init() override;
	void Update(float deltaTime, float fDistance, int iCharacterSpeed);
	void Draw_Left(HDC hdc);
	void Draw_Right(HDC hdc);
	void Set_StartX(int start_x);	//������ ���۵� �� �������� �������� �Ҳɸ� ����
};

//���ٹ��� �پ��ִ� ���� ��
class SmallRing : public Ring
{
private:
	int m_iCashWidth, m_iCashHeight;	//���ٹ� bmp ���� ���� ũ��

	void UpdateHitRect() override;	//��ֹ��� ��Ʈ�ڽ�, ���ٹ� ��Ʈ�ڽ� ��ǥ ������Ʈ
public:
	SmallRing() {};
	~SmallRing() {};
	void Init() override;
	void Draw_Left(HDC hdc);
	void Draw_Right(HDC hdc);
};