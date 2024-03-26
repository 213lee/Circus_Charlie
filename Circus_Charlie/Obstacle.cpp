#include "Obstacle.h"

HITBOX_TYPE Obstacle::HitCheck(RECT* character_rect)
{
	RECT tmp;

	if (IntersectRect(&tmp, &m_HitRect, character_rect))
		return HITBOX_TYPE::OBSTACLE;
	else if (!m_bScore && IntersectRect(&tmp, &m_ScoreRect, character_rect))
	{
		m_bScore = true;
		return HITBOX_TYPE::PASS;
	}
	else
		return HITBOX_TYPE::NONE;
}

/*----------------------Fire----------------------*/
Fire::Fire() : m_eAnimation(FIRE::FIRE_1)
{
}

void Fire::Init()
{
	//항아리 BMP, Width Init
	m_Bmp = new BitMap*[(int)FIRE::COUNT];
	for (int i = (int)FIRE::START; i < (int)FIRE::COUNT; i++)
	{
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage(i + (int)IMAGE::FIRE_1);
	}
	m_iWidth = m_Bmp[(int)FIRE::FIRE_1]->GetSize().cx;
	m_iHeight = m_Bmp[(int)FIRE::FIRE_1]->GetSize().cy;

	//Y좌표 불변 Init
	m_Position.m_iy = (int)FIRE_POS::DRAW_Y;

	m_iCurX = (int)DISTANCE::INITIAL;

	//히트박스 y좌표는 불변으로 Init에서 고정
	m_HitRect.top = m_Position.m_iy + (int)FIRE_POS::HIT_TOP;
	m_HitRect.bottom = m_HitRect.top + m_iHeight;

	m_ScoreRect.top = m_Position.m_iy - m_iHeight;
	m_ScoreRect.bottom = m_ScoreRect.top + m_iHeight;
}


void Fire::Update(float deltaTime, float fDistance)
{
	m_fTimer += deltaTime;
	
	//캐릭터가 움직이기 이전까지만 그려지는 좌표 수정
	if (fDistance <= (int)DISTANCE::CHARACTER_MOVE)
	{
		m_Position.m_ix = m_iCurX + (int)DISTANCE::TEN_METER - (m_iWidth + (int)CHARACTER_POS::FIXED_X) - fDistance + (int)CHARACTER_POS::FIXED_X;

		//왼쪽으로 모두 넘어가면
		if (m_Position.m_ix + m_iWidth <= 0)
		{
			m_iCurX += (int)DISTANCE::TEN_METER;
			m_bScore = false;
		}
		//왼쪽이 다시 보이기 시작할 때
		else if (m_Position.m_ix > (int)DISTANCE::TEN_METER - m_iWidth)
		{
			m_iCurX -= (int)DISTANCE::TEN_METER;
		}
	}

	//HitRect 업데이트	
	UpdateHitRect();

	//애니메이션
	Animation();
}

void Fire::UpdateHitRect()
{
	//변하는 x 좌표만 Update
	m_HitRect.left = m_Position.m_ix + (int)FIRE_POS::HIT_LEFT;
	m_HitRect.right = m_HitRect.left + m_iWidth + (int)FIRE_POS::HIT_RIGHT;

	m_ScoreRect.left = m_HitRect.right + (int)FIRE_POS::SCORE_LEFT;
	m_ScoreRect.right = m_ScoreRect.left + (int)FIRE_POS::SCORE_RIGHT;
}

void Fire::Animation()
{
	if (m_fTimer > 0.05f)
	{
		m_fTimer = 0;
		switch (m_eAnimation)
		{
		case FIRE::FIRE_1:
			m_eAnimation = FIRE::FIRE_2;
			break;
		case FIRE::FIRE_2:
			m_eAnimation = FIRE::FIRE_1;
			break;
		}
	}
}

void Fire::Draw(HDC hdc)
{
	m_Bmp[(int)m_eAnimation]->Draw(hdc, m_Position.m_ix, m_Position.m_iy);
}

Fire::~Fire()
{
	delete[] m_Bmp;
}


/*----------------------Ring----------------------*/

void Ring::Init()
{
	//불꽃링 BMP, Width Init
	m_Bmp = new BitMap * [(int)RING::COUNT - 1];
	for (int i = (int)RING::START; i < (int)RING::COUNT - 1; i++)
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage((int)IMAGE::RING_1 + i);

	//불꽃링 원본 이미지 크기 Load
	m_iWidth = m_Bmp[(int)RING::LEFT_1]->GetSize().cx;
	m_iHeight = m_Bmp[(int)RING::LEFT_1]->GetSize().cy;

	//그려질 Y좌표 Init
	m_Position.m_iy = (int)RING_POS::DRAW_Y;

	//히트박스 Y좌표 불변 Init
	m_HitRect.top = m_Position.m_iy + m_iHeight + (int)RING_POS::HIT_TOP;
	m_HitRect.bottom = m_HitRect.top + (int)RING_POS::HIT_BOTTOM;

	m_ScoreRect.top = m_Position.m_iy + (int)RING_POS::SCORE_TOP;
	m_ScoreRect.bottom = m_ScoreRect.top + m_iHeight + (int)RING_POS::SCORE_BOTTOM;

	//일반 링의 속도 Init
	m_iSpeed = (int)SPEED::RING_MOVE;
}

void Ring::Update(float deltaTime, float fDistance, int iCharacterSpeed)
{
	m_fTimer += deltaTime;

	//캐릭터가 이동하기 이전까지 링의 속도에 캐릭터 속도를 더함(오른쪽으로 이동+ 왼쪽으로 이동-)
	if(fDistance <= (float)DISTANCE::CHARACTER_MOVE && fDistance > 0)
		m_Position.m_ix -= deltaTime * (m_iSpeed + iCharacterSpeed);
	else
		m_Position.m_ix -= deltaTime * m_iSpeed;

	//링이 캐릭터 뒤로 사라졌을 때 x좌표 세팅
	Reset_X();

	//HitRect 업데이트	
	UpdateHitRect();

	//Animation
	Animation();
}

void Ring::Reset_X()
{
	if (m_Position.m_ix + m_iWidth <= 0)
	{ 
		m_Position.m_ix += (int)RING_POS::RESET_ADD_X;
		m_bScore = false;
	}
}

void Ring::UpdateHitRect()
{
	//변하는 x 좌표만 Update
	m_HitRect.left = m_Position.m_ix + (int)RING_POS::HIT_LEFT;
	m_HitRect.right = m_HitRect.left + (int)RING_POS::HIT_RIGHT;

	m_ScoreRect.left = m_Position.m_ix + (int)RING_POS::SCORE_LEFT;
	m_ScoreRect.right = m_ScoreRect.left + (int)RING_POS::SCORE_RIGHT;
}

void Ring::Animation()
{
	//Animation +0 or +2
	if (m_fTimer > 0.05f)
	{
		m_fTimer = 0;
		switch (m_eAnimationIdx)
		{
		case RING_ANIMATION::FIRST:
			m_eAnimationIdx = RING_ANIMATION::SECOND;
			break;
		case RING_ANIMATION::SECOND:
			m_eAnimationIdx = RING_ANIMATION::FIRST;
			break;
		}
	}
}

void Ring::Draw_Left(HDC hdc)
{
	//왼쪽 링
	m_Bmp[(int)RING::LEFT_1 + (int)m_eAnimationIdx]->Draw(hdc, m_Position.m_ix - m_iWidth, m_Position.m_iy);
}

void Ring::Draw_Right(HDC hdc)
{
	//오른쪽 링
	m_Bmp[(int)RING::RIGHT_1 + (int)m_eAnimationIdx]->Draw(hdc, m_Position.m_ix, m_Position.m_iy);
}

void Ring::Set_StartX(int start_x)
{
	m_Position.m_ix = start_x;
	m_bScore = false;
}

Ring::~Ring()
{
	delete[] m_Bmp;
}


/*----------------------Small Ring----------------------*/
void SmallRing::Init()
{
	//불꽃링, CASH BMP, Width Init
	m_Bmp = new BitMap * [(int)RING::COUNT];
	for (int i = 0; i < (int)RING::COUNT; i++)
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage((int)IMAGE::RING_1 + i);

	//불꽃링 원본 이미지 크기 Load -> 그릴 크기 설정 원본 height에 80퍼센트 크기로 그림
	m_iWidth = m_Bmp[0]->GetSize().cx;
	m_iHeight = m_Bmp[0]->GetSize().cy * 0.8f;

	//돈다발 원본 크기 Load
	m_iCashWidth = m_Bmp[(int)RING::CASH]->GetSize().cx;
	m_iCashHeight = m_Bmp[(int)RING::CASH]->GetSize().cy;

	//Y좌표 불변 Init
	m_Position.m_iy = (int)RING_POS::DRAW_Y;

	//히트박스 Y좌표 불변 Init
	m_HitRect.top = m_Position.m_iy + m_iHeight + (int)RING_POS::HIT_TOP;
	m_HitRect.bottom = m_HitRect.top + (int)RING_POS::HIT_BOTTOM;

	m_ScoreRect.top = m_Position.m_iy + (int)CASH_POS::ADD_Y;
	m_ScoreRect.bottom = m_ScoreRect.top + m_iCashHeight;

	//작은 링의 속도 Init
	m_iSpeed = (int)SPEED::SMALL_RING_MOVE;
}

//장애물의 히트박스, 돈다발 히트박스 좌표 업데이트
void SmallRing::UpdateHitRect()
{
	//히트박스 업데이트
	m_HitRect.left = m_Position.m_ix + (int)RING_POS::HIT_LEFT;
	m_HitRect.right = m_HitRect.left + (int)RING_POS::HIT_RIGHT;


	//돈다발 히트박스 업데이트
	m_ScoreRect.left = m_Position.m_ix + (int)CASH_POS::ADD_X;
	m_ScoreRect.right = m_ScoreRect.left + m_iCashWidth;

}

//왼쪽 링 그리기
void SmallRing::Draw_Left(HDC hdc)
{
	//왼쪽 링
	m_Bmp[(int)RING::LEFT_1 + (int)m_eAnimationIdx]->Draw(hdc, m_Position.m_ix - m_iWidth, m_Position.m_iy, m_iWidth, m_iHeight);
}


//오른쪽 링 그리기
void SmallRing::Draw_Right(HDC hdc)
{
	//오른쪽 링
	m_Bmp[(int)RING::RIGHT_1 + (int)m_eAnimationIdx]->Draw(hdc, m_Position.m_ix, m_Position.m_iy, m_iWidth, m_iHeight);
	
	//돈다발을 획득하지 않았을 때에만 그리기
	if (!m_bScore)
	{
		//돈다발
		m_Bmp[(int)RING::CASH]->Draw(hdc, m_Position.m_ix + (int)CASH_POS::ADD_X, m_Position.m_iy + (int)CASH_POS::ADD_Y);
	}
}