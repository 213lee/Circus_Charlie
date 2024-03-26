#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager() : m_eScene(SCENE::TITLE), m_bGoal(false) {}

GameManager::~GameManager() {}

void GameManager::Init(HWND hWnd, HDC hdc)
{
    m_backDC = CreateCompatibleDC(hdc);
    
    BitMapManager::GetInstance()->Init(hdc);
    
    m_fTimer = 0;
    m_fBonusTimer = 0;
    
    //Game에 필요한 객체들 Init
    m_Title.Init();
    m_Character.Init();
    m_Goal.Init();
    m_BackGround.Init();
    m_ObstacleManager.Init();
    m_ScoreBox.Init();
    m_Distance.Init();
}

void GameManager::Update(float deltaTime)
{
    switch (m_eScene)
    {
        //타이틀 씬에서 어떤 플레이어든 선택(Enter)하면 Play Scene으로 설정
    case SCENE::TITLE:
        if (m_Title.Update(deltaTime))
            StartSet();
        break;
    case SCENE::PLAY:
        //캐릭터가 장애물에 부딪쳐 멈춘 상태일때
        if (m_bPause)
            PauseUpdate(deltaTime);
        //캐릭터가 장애물에 부딪치지 않았을 때
        else
            PlayUpdate(deltaTime);
        break;
    }

    if (GetAsyncKeyState(VK_ESCAPE))
        PostQuitMessage(0);

}

void GameManager::StartSet()
{
    m_bGoal = false;
    m_eScene = SCENE::PLAY;
    m_iScore = (int)SCORE::INITIAL;
    m_iBonus = (int)BONUS::INITIAL;

    m_BackGround.StartSet();     //게임 시작시 기본 관중 BMP로 설정
    m_ScoreBox.StartSet();       //게임 시작시 스코어, 보너스가 출력되는 상태로 설정

    GameSet();
}

void GameManager::GameSet(int iStart_distance, int iLife)
{
    m_bPause = false;
    m_Character.GameSet(iStart_distance, iLife);
    m_ObstacleManager.GameSet(iStart_distance);
}

void GameManager::PauseUpdate(float deltaTime)
{
    m_fTimer += deltaTime;
    if (m_fTimer >= 1.5f)
    {
        m_fTimer = 0;

        //캐릭터 목숨이 남아있을 때 마지막으로 지나간 Meter(100, 90, 80 ..)로 세팅
        if (m_Character.GetLife() > 0)
        {
            GameSet(((int)m_Character.GetDistance() / (int)DISTANCE::TEN_METER) * (int)DISTANCE::TEN_METER, m_Character.GetLife());
        }
        //캐릭터 목숨을 모두 사용해 다시 타이틀 씬으로 돌아갈 때
        else
        {
            m_eScene = SCENE::TITLE;
        }
        m_bPause = false;
    }
}

void GameManager::PlayUpdate(float deltaTime)
{
    //캐릭터, 배경 업데이트
    m_Character.Update(deltaTime, m_bGoal);
    m_BackGround.Update(deltaTime, m_Character.GetDistance(), m_bGoal);

    //골인지점에 도착했을 때
    if (m_bGoal)
    {
        m_fTimer += deltaTime;
        //보너스 점수를 차감한 만큼 스코어에 더하고 bonus가 0이 됬을 때
        if (m_fTimer >= 0.01f && m_iBonus > 0)
        {
            m_fTimer = 0;
            //보너스 점수 차감하고 스코어에 합산
            m_iBonus -= (int)BONUS::GOAL_DECREASE;
            m_iScore += (int)BONUS::GOAL_DECREASE;
            if (m_iBonus <= 0)
            {
                m_iScore += m_iBonus;
                m_iBonus = 0;
                m_ScoreBox.SetClear();
            }
        }
        //일정시간 이후 다시 타이틀로 복귀
        else if (m_fTimer >= 5.0f)
        {
            m_fTimer = 0;
            m_eScene = SCENE::TITLE;
        }
    }
    //골인지점에 도착하기 이전 플레이중일 때
    else
    {
        m_fBonusTimer += deltaTime;

        //일정 시간마다 보너스 점수 감소
        if (m_fBonusTimer > 0.05f && m_iBonus > 0)
        {
            m_fBonusTimer = 0;
            if (m_iBonus < (int)BONUS::PLAY_DECREASE)
                m_iBonus = 0;
            else
                m_iBonus -= (int)BONUS::PLAY_DECREASE;
        }

        //게임 안의 장애물 Update
        m_ObstacleManager.Update(deltaTime, m_Character.GetDistance(), m_Character.GetSpeed());

        //장애물과 캐릭터 충돌 여부(장애물 충돌, 통과, 돈다발)
        switch (m_ObstacleManager.HitCheck(m_Character.GetHitRect()))
        {
            //장애물과 충돌시 캐릭터 life소모, 부딪친 animation, 게임 Pause 상태
        case HITBOX_TYPE::OBSTACLE:
            m_Character.Collision();
            m_bPause = true;
            break;
            //장애물 통과
        case HITBOX_TYPE::PASS:
            m_iScore += (int)SCORE::PASS;
            break;
            //돈 다발 획득
        case HITBOX_TYPE::CASH:
            m_iScore += (int)SCORE::CASH;
            break;
        default:
            break;
        }

        //골인지점에 도착했을 때 true 반환
        m_bGoal = m_Goal.Update(m_Character.GetDistance(), m_Character.GetHitRect());
    }

    //마지막 인터페이스 업데이트
    m_ScoreBox.Update(m_iScore, m_iBonus);
    m_Distance.Update(m_Character.GetDistance());
}

//더블 버퍼링을 사용해 backDC에 모든 객체를 그리고 전환
void GameManager::Draw(HDC hdc)
{
    HBITMAP backBitmap = CreateDIBSectionRe(hdc, (int)WINDOW_SIZE::WIDTH, (int)WINDOW_SIZE::HEIGHT);
    SelectObject(m_backDC, backBitmap);

    switch (m_eScene)
    {
    case SCENE::TITLE:
    {
        m_Title.Draw(m_backDC);
    }
        break;
    case SCENE::PLAY:
    {
        //배경 -> 골인지점 -> 캐릭터 뒤 장애물 -> 캐릭터 -> 캐릭터 앞 장애물 -> 인터페이스
        m_BackGround.Draw(m_backDC);
        
        m_Goal.Draw(m_backDC);
        
        m_ObstacleManager.LeftDraw(m_backDC);

        m_Character.Draw(m_backDC);        
        
        m_ObstacleManager.RightDraw(m_backDC);
        
        m_Distance.Draw(m_backDC);

        m_ScoreBox.Draw(m_backDC, m_Character.GetLife());
    }
        break;
    }
    
    BitBlt(hdc, 0, 0, (int)WINDOW_SIZE::WIDTH, (int)WINDOW_SIZE::HEIGHT, m_backDC, 0, 0, SRCCOPY);
    DeleteObject(backBitmap);
}

void GameManager::Release()
{
    DeleteObject(m_backDC);
	delete BitMapManager::GetInstance();
	if (m_hThis != NULL)
	{
		delete m_hThis;
		m_hThis = NULL;
	}
}

HBITMAP GameManager::CreateDIBSectionRe(HDC hdc, int width, int height)
{
    BITMAPINFO bm_info;
    ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
    bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bm_info.bmiHeader.biBitCount = 24;
    bm_info.bmiHeader.biWidth = width;
    bm_info.bmiHeader.biHeight = height;
    bm_info.bmiHeader.biPlanes = 1;

    LPVOID pBits;
    return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}