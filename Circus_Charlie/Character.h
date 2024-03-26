#pragma once
#include "BitMapManager.h"

enum class DIRECTION
{
	DEFAULT = 0,			//�⺻

	//�¿� ����
	BACK = -1,			//�������� �ް�����
	RUN = 1,			//���������� �� ��	
	
	//�� �Ʒ� ����
	UP = -1,			//���� �ö󰡴� ����
	DOWN = 1,			//���� �������� ����
};

enum class DIR_INDEX
{
	MOVE = 0,			//������ �¿� ���� �ε���
	JUMP,				//���� �� �Ʒ� ���� �ε���
	COUNT
};

enum class CHARACTER
{
	START = 0,
	DEFAULT = 0,		//�⺻, ������ �ִ�
	BACKWARD,			//�ڷ� ���� ��
	RUN_JUMP,			//������ �ٰų� ����
	CLEAR_1,			//Ŭ���� �ִϸ��̼�
	CLEAR_2,			//Ŭ���� �ִϸ��̼�2
	OVER,				//��ֹ� �ε�ĥ��
	COUNT				//CHARACTER ��
};

//HIT RECT ��ǥ
enum class CHARACTER_HIT_RECT
{
	START_X = 10,		//ĳ���� �׸��� ��ġ + START_X
	START_Y = 5,		//ĳ���� �׸��� ��ġ + START_Y
	
	ADD_X = -20,		//ĳ���� ���� BMP���� ��Ʈ�ڽ� ���θ� ���� �������� ��		
	ADD_Y = -10			//ĳ���� ���� BMP���� ��Ʈ�ڽ� ���θ� ���� �������� ��		
};

class Character
{
private:
	BitMap* m_Bmp[(int)CHARACTER::COUNT];
	Position m_Position;							//ĳ���Ͱ� �׷����� ��ǥ
	CHARACTER m_eAnimation;							//Animation �ε����� ���	
	DIRECTION m_eDir[(int)DIR_INDEX::COUNT];		//ĳ���� ���� 0(��, ��), 1(��, �Ʒ�)
	RECT m_HitRect;									//ĳ���� ��Ʈ�ڽ�
	int m_iWidth, m_iHeight;						//ĳ���� ��Ʈ�� ��Ʈ�ڽ� ������ ����
	float m_fDistance;								//ĳ���Ͱ� �̵��� �Ÿ�
	float m_fTimer;									//Ÿ�̸�
	float m_fAnimationTime;							//�ִϸ��̼� �ð����� �⺻ �޸��� 0.05f, ���� 0.5f
	bool m_bJump;									//ĳ���Ͱ� �������϶� true
	int m_iLife;									//ĳ���Ͱ� ������ ����� ��

	void KeyInput(bool isGoal);							//Ű�Է� ó�� �Լ�
	void Animation(bool isGoal);						//ĳ���� �ִϸ��̼� ó�� �Լ�
	void Jump(float deltaTime, bool isGoal);			//ĳ���� ���������� �� ó���Լ�
	void UpdateHitRect();								//ĳ���� ��Ʈ�ڽ� ������Ʈ �Լ�
public:
	Character() : m_fDistance((float)DISTANCE::INITIAL) {};
	~Character();
	void Init();
	void Update(float deltaTime, bool isGoal);
	void Draw(HDC hdc);

	void GameSet(int iStart_distance, int iLife);		//����(ù����, ��ֹ� �ε�ġ�� �ٽ� ����)�� �� ĳ���� ��ġ ����

	inline float GetDistance()
	{
		return m_fDistance;
	}
	inline RECT* GetHitRect()
	{
		return &m_HitRect;
	}
	inline int GetSpeed()
	{
		return (int)m_eDir[(int)DIR_INDEX::MOVE] * (int)SPEED::CHARACTER_MOVE;
	}
	inline int GetLife()
	{
		return m_iLife;
	}
	void Collision()	//ĳ���Ͱ� ��ֹ��� �浹�� ĳ���� ������ ó�� �Լ�
	{
		m_eAnimation = CHARACTER::OVER;
		m_iLife--;
	}
	
};
