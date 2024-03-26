#pragma once
#include "Title.h"
#include "Character.h"
#include "Goal.h"
#include "BackGround.h"
#include "ObstacleManager.h"
#include "Interface.h"

enum class SCENE
{
	TITLE,
	PLAY
};

//SCORE, BONUS ���� ��ġ
enum class SCORE
{
	INITIAL = 0,	//���� ���۽� �ʱ� ������
	PASS = 100,		//��ֹ��� ������� �� ȹ�� ����
	CASH = 300		//���ٹ��� ����� �� ȹ�� ����
};

enum class BONUS
{
	INITIAL = 10000,		//���� ���۽� ���ʽ� ���� �ʱⰪ
	PLAY_DECREASE = 5,		//�����ð����� ���ҵǴ� ��
	GOAL_DECREASE = 100		//���� �� ���ҵǴ� ��
};


class GameManager
{
private:
	static GameManager* m_hThis;

	HDC m_backDC;							//Duble buffering ���Ǵ� DC
	SCENE m_eScene;							//���� ��(Ÿ��Ʋ or �ΰ���)
	
	//TITLE SCENE
	Title m_Title;							//Title Scene�� �����ϴ� Title class
	
	//PLAY SCENE
	Goal m_Goal;							//Goal class
	Character m_Character;					//ĳ���� class
	BackGround m_BackGround;				//���� ���(�ʷ�, ��ũ��) class

	ScoreBox m_ScoreBox;					//���� ��ܿ� �׷����� ���ھ� �ڽ� class
	Distance m_Distance;					//��� �ϴܿ� �׷����� Meter �Ÿ� class
	ObstacleManager m_ObstacleManager;		//��ֹ�(�׾Ƹ�, �Ҳɸ�, ���� �Ҳɸ�)�� �����ϴ� �Ŵ��� class

	bool m_bGoal;							//���������� �����ߴ��� ����
	float m_fTimer;							//�������� ����, ��ֹ� �ε����� �� ����� Ÿ�̸�
	
	bool m_bPause;							//ĳ���Ͱ� ��ֹ��� �ε��ļ� �������� �� true

	int m_iScore;							//���� ���ھ� (��ֹ� �ϳ� ������ +100, ���ٹ� +300, �������� ������ Bonus �� ����)
	int m_iBonus;							//���ʽ� ���ھ� (�÷����� ���������� �����ϸ� �������� ������ ���� ������ Score�� �ջ�)
	float m_fBonusTimer;					//���ʽ� ���ھ� ������ ���� Ÿ�̸�

	void StartSet();						//Ÿ��Ʋ���� �÷��̾����� �Ѿ �� ó�� ���� ����
	void GameSet(int iStart_distance = (int)DISTANCE::INITIAL, int iLife = 4);	//���۵� �� ���۵Ǵ� �Ÿ�, life ����
	
	//Play Scene���� ������Ʈ
	void PauseUpdate(float deltaTime);		//��ֹ��� �ε�ģ ���¿��� Update
	void PlayUpdate(float deltaTime);		//�ε�ġ�� �ʰ� �÷������� ���¿��� Update

	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);		//������۸��� ���Ǵ� �Լ�
	GameManager();
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	~GameManager();

	void Init(HWND hWnd, HDC hdc);

	void Update(float deltatime);

	void Draw(HDC hdc);

	void Release();
};

