#include "BackGround.h"

void BackGround::Init()
{
	//�ʷϻ���� ,��ũ�� BMP SET
	for (int i = (int)BACKGROUND_IDX::START; i < (int)BACKGROUND_IDX::COUNT; i++)
		m_arrBmp[i] = BitMapManager::GetInstance()->GetImage(i + (int)IMAGE::BACK_1);
	m_Position.m_ix = (int)DISTANCE::INITIAL;
	m_Position.m_iy = (int)GREENBACK_POS::FIXED_Y - m_arrBmp[(int)BACKGROUND_IDX::ELEPHANT]->GetSize().cy;
	
	StartSet();

	m_iBmpWidth = m_arrBmp[(int)BACKGROUND_IDX::ELEPHANT]->GetSize().cx;
	m_iScrollWidth = m_iBmpWidth * (int)SCROLL::TOTAL_SCROLL;
}

void BackGround::Update(float deltaTime, float fDistance, bool bIsGoal)
{
	//ĳ���Ͱ� �����̱� �������� Update
	if (fDistance <= (float)DISTANCE::CHARACTER_MOVE)
	{
		m_Position.m_ix = m_iCurStartX - fDistance;

		//x1 <= -w : x1 + w <= 0 �߰� ��ũ���� �������� �� �Ѿ�� ��
		if (m_Position.m_ix + m_iScrollWidth <= 0)
		{
			m_Position.m_ix += m_iScrollWidth;
			m_iCurStartX += m_iScrollWidth;
		}
		//x1 > w �߰� ��ũ���� ���������� �� �Ѿ�� ��
		else if (m_Position.m_ix > m_iScrollWidth)
		{
			m_Position.m_ix -= m_iScrollWidth;
			m_iCurStartX -= m_iScrollWidth;
		}
	}

	//���������� �������� �� �ڼ�ġ�� ���� �ִϸ��̼� ����
	if (bIsGoal)
	{
		m_fTimer += deltaTime;

		if (m_fTimer > 0.05f)
		{
			m_fTimer = 0;
			switch (m_eAudienceIdx)
			{
			case BACKGROUND_IDX::AUDIENCE_1:
				m_eAudienceIdx = BACKGROUND_IDX::AUDIENCE_2;
				break;
			case BACKGROUND_IDX::AUDIENCE_2:
				m_eAudienceIdx = BACKGROUND_IDX::AUDIENCE_1;
				break;
			}
		}
	}
}

void BackGround::Draw(HDC hdc)
{
	//Scroll Draw
	int pos_x = m_Position.m_ix;
	int idx;
	for (int i = 0; i < (int)SCROLL::TOTAL_SCROLL; i++)
	{
		//1, 7��°�� �ڳ��� ���
		switch (i % 7)
		{
		case 0:
			idx = (int)BACKGROUND_IDX::ELEPHANT;
			break;
		default:
			idx = (int)m_eAudienceIdx;
			break;
		}
		//����, �߰�, ������ ��ũ�� Draw
		m_arrBmp[idx]->Draw(hdc, pos_x - m_iScrollWidth, m_Position.m_iy);
		m_arrBmp[idx]->Draw(hdc, pos_x, m_Position.m_iy);
		m_arrBmp[idx]->Draw(hdc, pos_x + m_iScrollWidth, m_Position.m_iy);
		pos_x += m_iBmpWidth;
	}
	
	//GREEN Draw
	m_arrBmp[(int)BACKGROUND_IDX::GRENN]->Draw(hdc, (int)GREENBACK_POS::FIXED_X, (int)GREENBACK_POS::FIXED_Y);

}
