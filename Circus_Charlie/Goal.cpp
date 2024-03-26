#include "Goal.h"

void Goal::Init()
{
	//BMP init
	m_Bmp = BitMapManager::GetInstance()->GetImage((int)IMAGE::GOAL);

	//Position, 히트박스 가로 세로크기 설정
	m_Position.m_iy = (int)GOAL::FIXD_Y;
	m_iWidth = m_Bmp->GetSize().cx;

	m_HitRect.top = m_Position.m_iy + (int)GOAL::HIT_ADD_Y;
	m_HitRect.bottom = m_HitRect.top + (int)GOAL::HIT_HEIGHT;
}

bool Goal::Update(float fDistance, RECT* character_rect)
{
	//그려질 x좌표 설정
	if (fDistance <= (float)DISTANCE::CHARACTER_MOVE)
		m_Position.m_ix = (int)DISTANCE::GOAL - fDistance;// +(int)CHARACTER_POS::FIXED_X;

	//히트박스 업데이트
	m_HitRect.left = m_Position.m_ix;
	m_HitRect.right = m_HitRect.left + m_iWidth;
	
	//업데이트에서 골인지점 들어올때 충돌체크
	RECT tmp;
	return IntersectRect(&tmp, &m_HitRect, character_rect);
}

void Goal::Draw(HDC hdc)
{
	m_Bmp->Draw(hdc, m_Position.m_ix, m_Position.m_iy);
	
	//Rectangle(hdc, m_HitRect.left, m_HitRect.top, m_HitRect.right, m_HitRect.bottom);
}