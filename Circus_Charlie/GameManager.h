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

//SCORE, BONUS 점수 수치
enum class SCORE
{
	INITIAL = 0,	//게임 시작시 초기 점수값
	PASS = 100,		//장애물을 통과했을 때 획득 점수
	CASH = 300		//돈다발을 얻었을 때 획득 점수
};

enum class BONUS
{
	INITIAL = 10000,		//게임 시작시 보너스 점수 초기값
	PLAY_DECREASE = 5,		//일정시간마다 감소되는 값
	GOAL_DECREASE = 100		//골인 후 감소되는 값
};


class GameManager
{
private:
	static GameManager* m_hThis;

	HDC m_backDC;							//Duble buffering 사용되는 DC
	SCENE m_eScene;							//게임 씬(타이틀 or 인게임)
	
	//TITLE SCENE
	Title m_Title;							//Title Scene을 관리하는 Title class
	
	//PLAY SCENE
	Goal m_Goal;							//Goal class
	Character m_Character;					//캐릭터 class
	BackGround m_BackGround;				//게임 배경(초록, 스크롤) class

	ScoreBox m_ScoreBox;					//게임 상단에 그려지는 스코어 박스 class
	Distance m_Distance;					//배경 하단에 그려지는 Meter 거리 class
	ObstacleManager m_ObstacleManager;		//장애물(항아리, 불꽃링, 작은 불꽃링)을 관리하는 매니저 class

	bool m_bGoal;							//골인지점에 도착했는지 여부
	float m_fTimer;							//골인지점 도착, 장애물 부딪쳤을 때 사용할 타이머
	
	bool m_bPause;							//캐릭터가 장애물에 부딪쳐서 멈춰있을 때 true

	int m_iScore;							//게임 스코어 (장애물 하나 넘을때 +100, 돈다발 +300, 골인지점 도착시 Bonus 와 더함)
	int m_iBonus;							//보너스 스코어 (플레이중 지속적으로 감소하며 골인지점 도착시 남은 점수가 Score에 합산)
	float m_fBonusTimer;					//보너스 스코어 차감을 위한 타이머

	void StartSet();						//타이틀에서 플레이씬으로 넘어갈 때 처음 시작 세팅
	void GameSet(int iStart_distance = (int)DISTANCE::INITIAL, int iLife = 4);	//시작될 때 시작되는 거리, life 세팅
	
	//Play Scene에서 업데이트
	void PauseUpdate(float deltaTime);		//장애물에 부딪친 상태에서 Update
	void PlayUpdate(float deltaTime);		//부딪치지 않고 플레이중인 상태에서 Update

	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);		//더블버퍼링에 사용되는 함수
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

