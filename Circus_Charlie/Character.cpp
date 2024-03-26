#include "Character.h"

void Character::Init()
{
	//ĳ���� BitMap Set
	for (int i = (int)CHARACTER::START; i < (int)CHARACTER::COUNT; i++)
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage(i + (int)IMAGE::PLAYER_1);

	m_iWidth = m_Bmp[0]->GetSize().cx + (int)CHARACTER_HIT_RECT::ADD_X;
	m_iHeight = m_Bmp[0]->GetSize().cy + (int)CHARACTER_HIT_RECT::ADD_Y;;
}

void Character::GameSet(int iStart_distance, int iLife)
{
	m_eAnimation = CHARACTER::DEFAULT;

	//ĳ���� ���۽� �׸� ��ǥ
	m_Position.m_ix = (int)CHARACTER_POS::FIXED_X;
	m_Position.m_iy = (int)CHARACTER_POS::DEFAULT_Y;

	//ĳ���� ���� ��ġ, Ÿ�̸� ����
	m_fDistance = iStart_distance;
	m_fTimer = 0;

	//�޸��� �ִϸ��̼� �ð����� ����
	m_fAnimationTime = 0.05f;

	//ĳ���� ���� ����
	m_bJump = false;
	m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::DEFAULT;
	m_eDir[(int)DIR_INDEX::JUMP] = DIRECTION::DEFAULT;

	m_iLife = iLife;
}

void Character::Update(float deltaTime, bool isGoal)
{
	m_fTimer += deltaTime;

	//���� �ӵ� x deltaTime x �������� �̵��� �Ÿ�����
	m_fDistance += (float)SPEED::CHARACTER_MOVE * deltaTime * (float)m_eDir[(int)DIR_INDEX::MOVE];
	
	//ĳ���Ͱ� ������ġ(100m) �ڷ� ���� ���ϰ�
	if (m_fDistance < (int)DISTANCE::INITIAL) m_fDistance = (int)DISTANCE::INITIAL;

	//�̵��� �Ÿ��� ���� ��ġ �̻��� ������ ĳ���� ������
	if (m_fDistance >= (float)DISTANCE::CHARACTER_MOVE)
	{
		m_Position.m_ix = m_fDistance - (int)DISTANCE::CHARACTER_MOVE + (int)CHARACTER_POS::FIXED_X;
	}

	//���������� �浹�߰� �ܻ� �߰��� �������� ��
	if (isGoal && m_fDistance > (float)DISTANCE::GOAL - 10)
	{
		m_fDistance = (float)DISTANCE::GOAL - 10;			//�ܻ� �߾� ����
		m_eAnimation = CHARACTER::CLEAR_1;					//Ŭ���� �ִϸ��̼�
		m_fAnimationTime = 0.5f;							//���� Ŭ���� �ִϸ��̼� �ӵ� ����
		m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::DEFAULT;	//ĳ���� ������ ���� �ʱ�ȭ
	}

	//��Ʈ�ڽ� ������Ʈ
	UpdateHitRect();

	//���������� �� Key Input, Animation X
	if (m_bJump)
		Jump(deltaTime, isGoal);
	else
	{
		Animation(isGoal);
		KeyInput(isGoal);
	}	
}

void Character::Draw(HDC hdc)
{
	m_Bmp[(int)m_eAnimation]->Draw(hdc, m_Position.m_ix, m_Position.m_iy);
}


void Character::Jump(float deltaTime, bool isGoal)
{
	m_Position.m_iy += (float)SPEED::CHARACTER_JUMP * deltaTime * (float)m_eDir[(int)DIR_INDEX::JUMP];

	int max_y;

	//PLAY �߿� �ٴڱ��� ����, GOAL ������ �ܻ� �� ���� ���� y��ǥ
	if (isGoal)
		max_y = (int)CHARACTER_POS::GOAL_Y;
	else
		max_y = (int)CHARACTER_POS::DEFAULT_Y;

	//������ �ְ� y�϶� �Ʒ��� ���� ��ȯ
	if (m_Position.m_iy <= (int)CHARACTER_POS::TOP_Y)
		m_eDir[(int)DIR_INDEX::JUMP] = DIRECTION::DOWN;
	//�������� ��
	else if (m_Position.m_iy > max_y)
	{
		m_Position.m_iy = max_y;
		m_eDir[(int)DIR_INDEX::JUMP] = DIRECTION::DEFAULT;
		m_bJump = false;
		m_eAnimation = CHARACTER::DEFAULT;
	}
}

void Character::Animation(bool isGoal)
{
	//�⺻ �޸��� �ִϸ��̼� time 0.05f, ���� �ִϸ��̼� 0.5f
	if (m_fTimer > m_fAnimationTime)
	{
		m_fTimer = 0;

		//�������� Animation
		if (isGoal)
		{
			if(m_eAnimation == CHARACTER::CLEAR_1)
				m_eAnimation = CHARACTER::CLEAR_2;
			else
				m_eAnimation = CHARACTER::CLEAR_1;
		}
		//�⺻ �޸��� Animation
		else
		{
			//���� �¿� �����ӿ� ����
			switch (m_eDir[(int)DIR_INDEX::MOVE])
			{
				//RUN
			case DIRECTION::RUN:
				if(m_eAnimation == CHARACTER::RUN_JUMP)
					m_eAnimation = CHARACTER::DEFAULT;
				else
					m_eAnimation = CHARACTER::RUN_JUMP;
				break;
				//BACK
			case DIRECTION::BACK:
				if(m_eAnimation == CHARACTER::BACKWARD)
					m_eAnimation = CHARACTER::DEFAULT;
				else
					m_eAnimation = CHARACTER::BACKWARD;
				break;
				//DEFUALT
			default:
				m_eAnimation = CHARACTER::DEFAULT;
				break;
			}
		}
	}
}

void Character::UpdateHitRect()
{
	m_HitRect.left = m_Position.m_ix + (int)CHARACTER_HIT_RECT::START_X;
	m_HitRect.top = m_Position.m_iy + (int)CHARACTER_HIT_RECT::START_Y;
	m_HitRect.right = m_HitRect.left + m_iWidth;
	m_HitRect.bottom = m_HitRect.top + m_iHeight;
}

void Character::KeyInput(bool isGoal)
{
	//���������� �������� �� Key Input X
	if (!isGoal)
	{
		//����
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_bJump = true;
			m_eDir[(int)DIR_INDEX::JUMP] = DIRECTION::UP;
			m_eAnimation = CHARACTER::RUN_JUMP;
		}
		//�ڷ� �ȱ�
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::BACK;
		}
		//������ �ٱ�
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::RUN;
		}
		//10m�� �̵�
		else if (GetAsyncKeyState(VK_TAB) & 0x8000)
		{
			m_fDistance = (int)DISTANCE::GOAL - (int)DISTANCE::TEN_METER;
		}
		else
			m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::DEFAULT;
	}
}

Character::~Character()
{
}