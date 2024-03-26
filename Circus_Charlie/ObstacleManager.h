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
	void Update(float deltaTime, float fDistance, int iCharacterDir);	//ĳ���Ϳ� ��ֹ� �ε����� �� true ��ȯ
	void LeftDraw(HDC hdc);								//�׾Ƹ�, ���ʸ� �׸���
	void RightDraw(HDC hdc);							//�����ʸ� �׸���
	void GameSet(int iStart_distance);					//���۵Ǵ� �Ÿ��� ���� ���� �׷����� ��ġ ����

	HITBOX_TYPE HitCheck(RECT* character_rect);			//��ֹ��� �浹üũ (��ֹ�, ��ֹ� ���, ���ٹ�)
};

