#include "ObstacleManager.h"

ObstacleManager::ObstacleManager()
{
}

ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::Init()
{
	m_Fire.Init();

	for(int i=0; i< RING_COUNT; i++)
		m_Ring[i].Init();

	m_SmallRing.Init();

}

void ObstacleManager::Update(float deltaTime, float fDistance, int iCharacterDir)
{
	m_Fire.Update(deltaTime, fDistance);

	for (int i = 0; i < RING_COUNT; i++)
		m_Ring[i].Update(deltaTime, fDistance, iCharacterDir);

	m_SmallRing.Update(deltaTime, fDistance, iCharacterDir);
}

void ObstacleManager::LeftDraw(HDC hdc)
{
	m_Fire.Draw(hdc);

	for (int i = 0; i < RING_COUNT; i++)
		m_Ring[i].Draw_Left(hdc);

	m_SmallRing.Draw_Left(hdc);
}


void ObstacleManager::RightDraw(HDC hdc)
{
	for (int i = 0; i < RING_COUNT; i++)
		m_Ring[i].Draw_Right(hdc);

	m_SmallRing.Draw_Right(hdc);
}


void ObstacleManager::GameSet(int iStart_distance)
{
	for (int i = 0; i < RING_COUNT; i++)
		m_Ring[i].Set_StartX((int)RING_POS::GAP_X * (i + 1));

	m_SmallRing.Set_StartX((int)RING_POS::GAP_X * RING_COUNT);
}

HITBOX_TYPE ObstacleManager::HitCheck(RECT* character_rect)
{
	switch (m_Fire.HitCheck(character_rect))
	{
	case HITBOX_TYPE::OBSTACLE:
		return HITBOX_TYPE::OBSTACLE;
	case HITBOX_TYPE::PASS:
		return HITBOX_TYPE::PASS;
	default:
		break;
	}

	for (int i = 0; i < RING_COUNT; i++)
	{
		switch (m_Ring[i].HitCheck(character_rect))
		{
		case HITBOX_TYPE::OBSTACLE:
			return HITBOX_TYPE::OBSTACLE;
		case HITBOX_TYPE::PASS:
			return HITBOX_TYPE::PASS;
		default:
			break;
		}
	}

	switch (m_SmallRing.HitCheck(character_rect))
	{
	case HITBOX_TYPE::OBSTACLE:
		return HITBOX_TYPE::OBSTACLE;
	case HITBOX_TYPE::PASS:
		return HITBOX_TYPE::CASH;
	default:
		return HITBOX_TYPE::NONE;;
	}	
}
