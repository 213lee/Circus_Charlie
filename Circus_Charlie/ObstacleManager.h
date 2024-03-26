#pragma once
#include "Obstacle.h"


class ObstacleManager
{
private:
	Fire m_Fire;
	Ring m_Ring[RING_COUNT];
	SmallRing m_SmallRing;
public:
	ObstacleManager();
	~ObstacleManager();

	void Init();
	void Update(float deltaTime, float fDistance, int iCharacterDir);	//캐릭터와 장애물 부딪쳤을 때 true 반환
	void LeftDraw(HDC hdc);								//항아리, 왼쪽링 그리기
	void RightDraw(HDC hdc);							//오른쪽링 그리기
	void GameSet(int iStart_distance);					//시작되는 거리에 따라 링이 그려지는 위치 세팅

	HITBOX_TYPE HitCheck(RECT* character_rect);			//장애물과 충돌체크 (장애물, 장애물 통과, 돈다발)
};

