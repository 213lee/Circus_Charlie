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
	//�׾Ƹ� BMP, Width Init
	m_Bmp = new BitMap*[(int)FIRE::COUNT];
	for (int i = (int)FIRE::START; i < (int)FIRE::COUNT; i++)
	{
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage(i + (int)IMAGE::FIRE_1);
	}
	m_iWidth = m_Bmp[(int)FIRE::FIRE_1]->GetSize().cx;
	m_iHeight = m_Bmp[(int)FIRE::FIRE_1]->GetSize().cy;

	//Y��ǥ �Һ� Init
	m_Position.m_iy = (int)FIRE_POS::DRAW_Y;

	m_iCurX = (int)DISTANCE::INITIAL;

	//��Ʈ�ڽ� y��ǥ�� �Һ����� Init���� ����
	m_HitRect.top = m_Position.m_iy + (int)FIRE_POS::HIT_TOP;
	m_HitRect.bottom = m_HitRect.top + m_iHeight;

	m_ScoreRect.top = m_Position.m_iy - m_iHeight;
	m_ScoreRect.bottom = m_ScoreRect.top + m_iHeight;
}


void Fire::Update(float deltaTime, float fDistance)
{
	m_fTimer += deltaTime;
	
	//ĳ���Ͱ� �����̱� ���������� �׷����� ��ǥ ����
	if (fDistance <= (int)DISTANCE::CHARACTER_MOVE)
	{
		m_Position.m_ix = m_iCurX + (int)DISTANCE::TEN_METER - (m_iWidth + (int)CHARACTER_POS::FIXED_X) - fDistance + (int)CHARACTER_POS::FIXED_X;

		//�������� ��� �Ѿ��
		if (m_Position.m_ix + m_iWidth <= 0)
		{
			m_iCurX += (int)DISTANCE::TEN_METER;
			m_bScore = false;
		}
		//������ �ٽ� ���̱� ������ ��
		else if (m_Position.m_ix > (int)DISTANCE::TEN_METER - m_iWidth)
		{
			m_iCurX -= (int)DISTANCE::TEN_METER;
		}
	}

	//HitRect ������Ʈ	
	UpdateHitRect();

	//�ִϸ��̼�
	Animation();
}

void Fire::UpdateHitRect()
{
	//���ϴ� x ��ǥ�� Update
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
	//�Ҳɸ� BMP, Width Init
	m_Bmp = new BitMap * [(int)RING::COUNT - 1];
	for (int i = (int)RING::START; i < (int)RING::COUNT - 1; i++)
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage((int)IMAGE::RING_1 + i);

	//�Ҳɸ� ���� �̹��� ũ�� Load
	m_iWidth = m_Bmp[(int)RING::LEFT_1]->GetSize().cx;
	m_iHeight = m_Bmp[(int)RING::LEFT_1]->GetSize().cy;

	//�׷��� Y��ǥ Init
	m_Position.m_iy = (int)RING_POS::DRAW_Y;

	//��Ʈ�ڽ� Y��ǥ �Һ� Init
	m_HitRect.top = m_Position.m_iy + m_iHeight + (int)RING_POS::HIT_TOP;
	m_HitRect.bottom = m_HitRect.top + (int)RING_POS::HIT_BOTTOM;

	m_ScoreRect.top = m_Position.m_iy + (int)RING_POS::SCORE_TOP;
	m_ScoreRect.bottom = m_ScoreRect.top + m_iHeight + (int)RING_POS::SCORE_BOTTOM;

	//�Ϲ� ���� �ӵ� Init
	m_iSpeed = (int)SPEED::RING_MOVE;
}

void Ring::Update(float deltaTime, float fDistance, int iCharacterSpeed)
{
	m_fTimer += deltaTime;

	//ĳ���Ͱ� �̵��ϱ� �������� ���� �ӵ��� ĳ���� �ӵ��� ����(���������� �̵�+ �������� �̵�-)
	if(fDistance <= (float)DISTANCE::CHARACTER_MOVE && fDistance > 0)
		m_Position.m_ix -= deltaTime * (m_iSpeed + iCharacterSpeed);
	else
		m_Position.m_ix -= deltaTime * m_iSpeed;

	//���� ĳ���� �ڷ� ������� �� x��ǥ ����
	Reset_X();

	//HitRect ������Ʈ	
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
	//���ϴ� x ��ǥ�� Update
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
	//���� ��
	m_Bmp[(int)RING::LEFT_1 + (int)m_eAnimationIdx]->Draw(hdc, m_Position.m_ix - m_iWidth, m_Position.m_iy);
}

void Ring::Draw_Right(HDC hdc)
{
	//������ ��
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
	//�Ҳɸ�, CASH BMP, Width Init
	m_Bmp = new BitMap * [(int)RING::COUNT];
	for (int i = 0; i < (int)RING::COUNT; i++)
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage((int)IMAGE::RING_1 + i);

	//�Ҳɸ� ���� �̹��� ũ�� Load -> �׸� ũ�� ���� ���� height�� 80�ۼ�Ʈ ũ��� �׸�
	m_iWidth = m_Bmp[0]->GetSize().cx;
	m_iHeight = m_Bmp[0]->GetSize().cy * 0.8f;

	//���ٹ� ���� ũ�� Load
	m_iCashWidth = m_Bmp[(int)RING::CASH]->GetSize().cx;
	m_iCashHeight = m_Bmp[(int)RING::CASH]->GetSize().cy;

	//Y��ǥ �Һ� Init
	m_Position.m_iy = (int)RING_POS::DRAW_Y;

	//��Ʈ�ڽ� Y��ǥ �Һ� Init
	m_HitRect.top = m_Position.m_iy + m_iHeight + (int)RING_POS::HIT_TOP;
	m_HitRect.bottom = m_HitRect.top + (int)RING_POS::HIT_BOTTOM;

	m_ScoreRect.top = m_Position.m_iy + (int)CASH_POS::ADD_Y;
	m_ScoreRect.bottom = m_ScoreRect.top + m_iCashHeight;

	//���� ���� �ӵ� Init
	m_iSpeed = (int)SPEED::SMALL_RING_MOVE;
}

//��ֹ��� ��Ʈ�ڽ�, ���ٹ� ��Ʈ�ڽ� ��ǥ ������Ʈ
void SmallRing::UpdateHitRect()
{
	//��Ʈ�ڽ� ������Ʈ
	m_HitRect.left = m_Position.m_ix + (int)RING_POS::HIT_LEFT;
	m_HitRect.right = m_HitRect.left + (int)RING_POS::HIT_RIGHT;


	//���ٹ� ��Ʈ�ڽ� ������Ʈ
	m_ScoreRect.left = m_Position.m_ix + (int)CASH_POS::ADD_X;
	m_ScoreRect.right = m_ScoreRect.left + m_iCashWidth;

}

//���� �� �׸���
void SmallRing::Draw_Left(HDC hdc)
{
	//���� ��
	m_Bmp[(int)RING::LEFT_1 + (int)m_eAnimationIdx]->Draw(hdc, m_Position.m_ix - m_iWidth, m_Position.m_iy, m_iWidth, m_iHeight);
}


//������ �� �׸���
void SmallRing::Draw_Right(HDC hdc)
{
	//������ ��
	m_Bmp[(int)RING::RIGHT_1 + (int)m_eAnimationIdx]->Draw(hdc, m_Position.m_ix, m_Position.m_iy, m_iWidth, m_iHeight);
	
	//���ٹ��� ȹ������ �ʾ��� ������ �׸���
	if (!m_bScore)
	{
		//���ٹ�
		m_Bmp[(int)RING::CASH]->Draw(hdc, m_Position.m_ix + (int)CASH_POS::ADD_X, m_Position.m_iy + (int)CASH_POS::ADD_Y);
	}
}