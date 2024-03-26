#include "Interface.h"


/*-----------------------SCORE-----------------------*/
void ScoreBox::Init()
{
	//Score ��Ʈ�� LOAD
	for (int i = 0; i < (int)SCOREBOX::COUNT; i++)
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage((int)IMAGE::INTER_1 + i);

	
	m_iLifeWidth = m_Bmp[(int)SCOREBOX::LIFE]->GetSize().cx;

	//����� ��Ʈ Create
	m_font = CreateFont((int)FONT_SIZE::SCORE, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�ü�"));
}

void ScoreBox::Update(int score, int bonus)
{
	//���ʽ� string ������Ʈ
	m_strScore = L"Score : " + std::to_wstring(score);
	m_strBonus = L"Bonus : " + std::to_wstring(bonus);
}

void ScoreBox::Draw(HDC hdc, int life)
{		
	//Score �ڽ�
	m_Bmp[(int)SCOREBOX::BOX]->Draw(hdc, (int)SCOREBOX_POS::BOX_X, (int)SCOREBOX_POS::BOX_Y);

	//Score, Bonus ���
	m_oldfont = (HFONT)SelectObject(hdc, m_font);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, (int)SCOREBOX_POS::SCORE_X, (int)SCOREBOX_POS::SCORE_Y, m_strScore.c_str(), m_strScore.length());
	

	//���� Ŭ����ÿ� message ���
	if (m_bMessage)
	{
		TextOut(hdc, (int)SCOREBOX_POS::BONUS_X, (int)SCOREBOX_POS::BONUS_Y, m_strMessage.c_str(), m_strMessage.length());
	}
	else
	{
		TextOut(hdc, (int)SCOREBOX_POS::BONUS_X, (int)SCOREBOX_POS::BONUS_Y, m_strBonus.c_str(), m_strBonus.length());
		
		//Life ������ġ���� ���� life��ŭ �׸���
		for (int i = 0; i < life; i++)
			m_Bmp[(int)SCOREBOX::LIFE]->Draw(hdc, (int)SCOREBOX_POS::LIFE_X - m_iLifeWidth * i, (int)SCOREBOX_POS::LIFE_Y);
	}
	SelectObject(hdc, m_oldfont);

	
}

ScoreBox::~ScoreBox()
{
	DeleteObject(m_font);
}



/*-----------------------DISTANCE-----------------------*/
void Distance::Init()
{
	//Distance ��Ʈ��, ��Ʈ�� width LOAD
	m_Bmp = BitMapManager::GetInstance()->GetImage((int)IMAGE::INTER_3);
	m_iWidth = m_Bmp->GetSize().cx;

	//�׷��� ��ġ Init
	m_Position.m_ix = (int)DISTANCE_POS::START_X;
	m_Position.m_iy = (int)DISTANCE_POS::FIXED_Y;

	//���� ���� ���� 10(0)
	m_iCurMeter = 10;

	//����� ��Ʈ Create
	m_font = CreateFont((int)FONT_SIZE::DISTANCE, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�ü�"));
}

void Distance::Update(float fDistance)
{
	if (fDistance <= (float)DISTANCE::CHARACTER_MOVE)
	{
		//100 0 / 90 1000 / 80 2000 / 70 3000
		m_Position.m_ix = (int)DISTANCE::TEN_METER * (10 - m_iCurMeter) - fDistance + (int)CHARACTER_POS::FIXED_X; //+ĳ���� ������ġ20
		
		//���Ͱ� �������� ��� �Ѿ�� ���� ���� 10m ����
		if (m_Position.m_ix + m_iWidth <= 0)
		{
			m_iCurMeter--;
		}
		//���Ͱ� �ڷΰ��鼭 ���̱� ������ �� ���� 10m ����
		else if (m_Position.m_ix >= (int)DISTANCE::TEN_METER - m_iWidth)
		{
			m_iCurMeter++;
		}
		m_strMeter = std::to_wstring(m_iCurMeter * 10);
	}	
	
}

void Distance::Draw(HDC hdc)
{
	if (m_iCurMeter > 0)
	{
		//Meter BMP
		m_Bmp->Draw(hdc, m_Position.m_ix, m_Position.m_iy);
		
		//���� Meter Text ���
		m_oldfont = (HFONT)SelectObject(hdc, m_font);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, m_Position.m_ix + (int)DISTANCE_POS::TEXT_ADD_X, (int)DISTANCE_POS::TEXT_FIXED_Y, m_strMeter.c_str(), m_strMeter.length());
		SelectObject(hdc, m_oldfont);
	}
}

Distance::~Distance()
{
	DeleteObject(m_font);
}

