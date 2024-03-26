#pragma once
#include "BitMapManager.h"

enum class DIRECTION
{
	DEFAULT = 0,			//기본

	//좌우 방향
	BACK = -1,			//왼쪽으로 뒷걸음질
	RUN = 1,			//오른쪽으로 뛸 때	
	
	//위 아래 방향
	UP = -1,			//점프 올라가는 상태
	DOWN = 1,			//점프 내려가는 상태
};

enum class DIR_INDEX
{
	MOVE = 0,			//움직임 좌우 방향 인덱스
	JUMP,				//점프 위 아래 방향 인덱스
	COUNT
};

enum class CHARACTER
{
	START = 0,
	DEFAULT = 0,		//기본, 가만히 있는
	BACKWARD,			//뒤로 걸을 때
	RUN_JUMP,			//앞으로 뛰거나 점프
	CLEAR_1,			//클리어 애니메이션
	CLEAR_2,			//클리어 애니메이션2
	OVER,				//장애물 부딪칠때
	COUNT				//CHARACTER 수
};

//HIT RECT 좌표
enum class CHARACTER_HIT_RECT
{
	START_X = 10,		//캐릭터 그리는 위치 + START_X
	START_Y = 5,		//캐릭터 그리는 위치 + START_Y
	
	ADD_X = -20,		//캐릭터 원본 BMP에서 히트박스 가로를 위해 더해지는 값		
	ADD_Y = -10			//캐릭터 원본 BMP에서 히트박스 세로를 위해 더해지는 값		
};

class Character
{
private:
	BitMap* m_Bmp[(int)CHARACTER::COUNT];
	Position m_Position;							//캐릭터가 그려지는 좌표
	CHARACTER m_eAnimation;							//Animation 인덱스로 사용	
	DIRECTION m_eDir[(int)DIR_INDEX::COUNT];		//캐릭터 방향 0(좌, 우), 1(위, 아래)
	RECT m_HitRect;									//캐릭터 히트박스
	int m_iWidth, m_iHeight;						//캐릭터 비트맵 히트박스 사이즈 저장
	float m_fDistance;								//캐릭터가 이동한 거리
	float m_fTimer;									//타이머
	float m_fAnimationTime;							//애니메이션 시간변수 기본 달리기 0.05f, 골인 0.5f
	bool m_bJump;									//캐릭터가 점프중일때 true
	int m_iLife;									//캐릭터가 가지는 목숨의 수

	void KeyInput(bool isGoal);							//키입력 처리 함수
	void Animation(bool isGoal);						//캐릭터 애니메이션 처리 함수
	void Jump(float deltaTime, bool isGoal);			//캐릭터 점프상태일 때 처리함수
	void UpdateHitRect();								//캐릭터 히트박스 업데이트 함수
public:
	Character() : m_fDistance((float)DISTANCE::INITIAL) {};
	~Character();
	void Init();
	void Update(float deltaTime, bool isGoal);
	void Draw(HDC hdc);

	void GameSet(int iStart_distance, int iLife);		//시작(첫시작, 장애물 부딪치고 다시 시작)될 때 캐릭터 위치 세팅

	inline float GetDistance()
	{
		return m_fDistance;
	}
	inline RECT* GetHitRect()
	{
		return &m_HitRect;
	}
	inline int GetSpeed()
	{
		return (int)m_eDir[(int)DIR_INDEX::MOVE] * (int)SPEED::CHARACTER_MOVE;
	}
	inline int GetLife()
	{
		return m_iLife;
	}
	void Collision()	//캐릭터가 장애물에 충돌시 캐릭터 내에서 처리 함수
	{
		m_eAnimation = CHARACTER::OVER;
		m_iLife--;
	}
	
};
