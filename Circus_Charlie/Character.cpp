#include "Character.h"

void Character::Init()
{
	//캐릭터 BitMap Set
	for (int i = (int)CHARACTER::START; i < (int)CHARACTER::COUNT; i++)
		m_Bmp[i] = BitMapManager::GetInstance()->GetImage(i + (int)IMAGE::PLAYER_1);

	m_iWidth = m_Bmp[0]->GetSize().cx + (int)CHARACTER_HIT_RECT::ADD_X;
	m_iHeight = m_Bmp[0]->GetSize().cy + (int)CHARACTER_HIT_RECT::ADD_Y;;
}

void Character::GameSet(int iStart_distance, int iLife)
{
	m_eAnimation = CHARACTER::DEFAULT;

	//캐릭터 시작시 그릴 좌표
	m_Position.m_ix = (int)CHARACTER_POS::FIXED_X;
	m_Position.m_iy = (int)CHARACTER_POS::DEFAULT_Y;

	//캐릭터 시작 위치, 타이머 설정
	m_fDistance = iStart_distance;
	m_fTimer = 0;

	//달리는 애니메이션 시간으로 설정
	m_fAnimationTime = 0.05f;

	//캐릭터 상태 설정
	m_bJump = false;
	m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::DEFAULT;
	m_eDir[(int)DIR_INDEX::JUMP] = DIRECTION::DEFAULT;

	m_iLife = iLife;
}

void Character::Update(float deltaTime, bool isGoal)
{
	m_fTimer += deltaTime;

	//일정 속도 x deltaTime x 방향으로 이동한 거리수정
	m_fDistance += (float)SPEED::CHARACTER_MOVE * deltaTime * (float)m_eDir[(int)DIR_INDEX::MOVE];
	
	//캐릭터가 시작위치(100m) 뒤로 가지 못하게
	if (m_fDistance < (int)DISTANCE::INITIAL) m_fDistance = (int)DISTANCE::INITIAL;

	//이동한 거리가 일정 위치 이상일 때부터 캐릭터 움직임
	if (m_fDistance >= (float)DISTANCE::CHARACTER_MOVE)
	{
		m_Position.m_ix = m_fDistance - (int)DISTANCE::CHARACTER_MOVE + (int)CHARACTER_POS::FIXED_X;
	}

	//골인지점과 충돌했고 단상 중간에 도착했을 때
	if (isGoal && m_fDistance > (float)DISTANCE::GOAL - 10)
	{
		m_fDistance = (float)DISTANCE::GOAL - 10;			//단상 중앙 고정
		m_eAnimation = CHARACTER::CLEAR_1;					//클리어 애니메이션
		m_fAnimationTime = 0.5f;							//게임 클리어 애니메이션 속도 감소
		m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::DEFAULT;	//캐릭터 움직임 방향 초기화
	}

	//히트박스 업데이트
	UpdateHitRect();

	//점프상태일 때 Key Input, Animation X
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

	//PLAY 중에 바닥까지 착지, GOAL 도착시 단상 위 까지 착지 y좌표
	if (isGoal)
		max_y = (int)CHARACTER_POS::GOAL_Y;
	else
		max_y = (int)CHARACTER_POS::DEFAULT_Y;

	//점프중 최고 y일때 아래로 방향 전환
	if (m_Position.m_iy <= (int)CHARACTER_POS::TOP_Y)
		m_eDir[(int)DIR_INDEX::JUMP] = DIRECTION::DOWN;
	//착지했을 때
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
	//기본 달리는 애니메이션 time 0.05f, 골인 애니메이션 0.5f
	if (m_fTimer > m_fAnimationTime)
	{
		m_fTimer = 0;

		//골인지점 Animation
		if (isGoal)
		{
			if(m_eAnimation == CHARACTER::CLEAR_1)
				m_eAnimation = CHARACTER::CLEAR_2;
			else
				m_eAnimation = CHARACTER::CLEAR_1;
		}
		//기본 달리기 Animation
		else
		{
			//현재 좌우 움직임에 따라
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
	//골인지점에 도착했을 때 Key Input X
	if (!isGoal)
	{
		//점프
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_bJump = true;
			m_eDir[(int)DIR_INDEX::JUMP] = DIRECTION::UP;
			m_eAnimation = CHARACTER::RUN_JUMP;
		}
		//뒤로 걷기
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::BACK;
		}
		//앞으로 뛰기
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_eDir[(int)DIR_INDEX::MOVE] = DIRECTION::RUN;
		}
		//10m로 이동
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