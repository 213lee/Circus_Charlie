#pragma once
#include "BitMapManager.h"


enum class FIRE
{
	START = 0,
	FIRE_1 = 0,			//항아리 1
	FIRE_2,				//항아리 2
	COUNT
};

enum class FIRE_POS
{
	DRAW_Y = 295,			//항아리가 그려지는 고정 Y좌표

	//장애물 히트박스
	HIT_LEFT = 5,			//left에 더해지는 값
	HIT_RIGHT = -10,		//right에 더해지는 값
	HIT_TOP = 5,			//top에 더해지는 값

	//스코어 히트박스
	SCORE_LEFT = 5,			//left에 더해지는 값
	SCORE_RIGHT = 10,		//right에 더해지는 값
};

enum class RING
{
	START = 0,
	LEFT_1 = 0,			//불꽃링 왼쪽 1
	RIGHT_1,			//불꽃링 오른쪽 1
	LEFT_2,				//불꽃링 왼쪽 2
	RIGHT_2,			//불꽃링 오른쪽 2
	CASH,
	COUNT
};

enum class RING_ANIMATION
{
	FIRST = 0,			//링 애니메이션1에 더해지는 값
	SECOND = 2			//링 애니메이션2에 더해지는 값
};

#define RING_COUNT 3	//게임에서 사용하는 일반 링의 개수

enum class RING_POS
{
	DRAW_Y = 160,			//불꽃링이 그려지는 고정 Y좌표

	//장애물 히트박스
	HIT_LEFT = -5,		//left에 더해지는 값
	HIT_RIGHT = 10,		//right에 더해지는 값
	HIT_TOP = -5,		//top에 더해지는 값
	HIT_BOTTOM = 10,	//bottom에 더해지는 값

	//스코어 히트박스
	SCORE_LEFT = -5,	//left에 더해지는 값
	SCORE_RIGHT = 10,	//right에 더해지는 값
	SCORE_TOP = 30,		//top에 더해지는 값
	SCORE_BOTTOM = -50,	//bottom에 더해지는 값 

	GAP_X = 700,						//링 하나 사이의 x 간격
	RESET_ADD_X = GAP_X * RING_COUNT	//링이 캐릭터 뒤로 지나갔을 때 다시 위치를 세팅하기위해 더해지는 값
};

enum class CASH_POS
{
	ADD_X = -10,			//돈다발을 그리기위해 링의 기본 좌표에 더해질 x값
	ADD_Y = 20			//돈다발을 그리기위해 링의 기본 좌표에 더해질 y값
};

enum class HITBOX_TYPE
{
	OBSTACLE,		//장애물에 부딪쳤을 때
	PASS,			//장애물을 통과했을 때
	NONE,			//아무것도 부딪치지 않았을 때
	
	CASH			//돈다발
};

class Obstacle
{
protected:
	BitMap** m_Bmp;					//BitMap* 포인터 배열 동적할당을 위한 더블 포인터
	Position m_Position;			//그려질 좌표
	RECT m_HitRect;					//장애물과 충돌감지를 위한 히트박스
	RECT m_ScoreRect;				//장애물을 넘었는지 확인하기 위한 히트박스
	bool m_bScore;					//스코어 히트박스를 활성화시키기 위한 flag
	float m_fTimer;					//타이머
	int m_iWidth, m_iHeight;		//BMP 가로, 세로크기

	virtual void Animation() abstract;
public:
	Obstacle() : m_bScore(false) {};
	virtual ~Obstacle() {};
	virtual void Init() abstract;
	HITBOX_TYPE HitCheck(RECT* character_rect);		//장애물과 충돌, 통과 검사
};

//불 항아리 장애물
class Fire : public Obstacle
{
private:
	int m_iCurX;				//현재 그리는 기준이되는 X 0, 1000, 2000, 3000 ...
	FIRE m_eAnimation;			//Animation 인덱스
	
	void UpdateHitRect();
	void Animation() override;
public:
	Fire();
	~Fire();
	void Init() override;
	void Update(float deltaTime, float fDistance);
	void Draw(HDC hdc);
};

//불꽃 링 장애물
class Ring : public Obstacle
{
protected:
	int m_iSpeed;					//링이 가지는 스피드
	RING_ANIMATION m_eAnimationIdx;	//Animation 인덱스
	
	virtual void UpdateHitRect();	//장애물의 히트박스 좌표 업데이트
	void Reset_X();					//링이 캐릭터 뒤로 사라졌을 때 X좌표를 더해 위치 재설정
	void Animation() override;
public:
	Ring() : m_eAnimationIdx(RING_ANIMATION::FIRST) {};
	~Ring();
	void Init() override;
	void Update(float deltaTime, float fDistance, int iCharacterSpeed);
	void Draw_Left(HDC hdc);
	void Draw_Right(HDC hdc);
	void Set_StartX(int start_x);	//게임이 시작될 때 시작점을 기준으로 불꽃링 세팅
};

//돈다발이 붙어있는 작은 링
class SmallRing : public Ring
{
private:
	int m_iCashWidth, m_iCashHeight;	//돈다발 bmp 가로 세로 크기

	void UpdateHitRect() override;	//장애물의 히트박스, 돈다발 히트박스 좌표 업데이트
public:
	SmallRing() {};
	~SmallRing() {};
	void Init() override;
	void Draw_Left(HDC hdc);
	void Draw_Right(HDC hdc);
};