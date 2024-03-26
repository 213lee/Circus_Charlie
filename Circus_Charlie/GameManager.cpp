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
    
    //Game�� �ʿ��� ��ü�� Init
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
        //Ÿ��Ʋ ������ � �÷��̾�� ����(Enter)�ϸ� Play Scene���� ����
    case SCENE::TITLE:
        if (m_Title.Update(deltaTime))
            StartSet();
        break;
    case SCENE::PLAY:
        //ĳ���Ͱ� ��ֹ��� �ε��� ���� �����϶�
        if (m_bPause)
            PauseUpdate(deltaTime);
        //ĳ���Ͱ� ��ֹ��� �ε�ġ�� �ʾ��� ��
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

    m_BackGround.StartSet();     //���� ���۽� �⺻ ���� BMP�� ����
    m_ScoreBox.StartSet();       //���� ���۽� ���ھ�, ���ʽ��� ��µǴ� ���·� ����

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

        //ĳ���� ����� �������� �� ���������� ������ Meter(100, 90, 80 ..)�� ����
        if (m_Character.GetLife() > 0)
        {
            GameSet(((int)m_Character.GetDistance() / (int)DISTANCE::TEN_METER) * (int)DISTANCE::TEN_METER, m_Character.GetLife());
        }
        //ĳ���� ����� ��� ����� �ٽ� Ÿ��Ʋ ������ ���ư� ��
        else
        {
            m_eScene = SCENE::TITLE;
        }
        m_bPause = false;
    }
}

void GameManager::PlayUpdate(float deltaTime)
{
    //ĳ����, ��� ������Ʈ
    m_Character.Update(deltaTime, m_bGoal);
    m_BackGround.Update(deltaTime, m_Character.GetDistance(), m_bGoal);

    //���������� �������� ��
    if (m_bGoal)
    {
        m_fTimer += deltaTime;
        //���ʽ� ������ ������ ��ŭ ���ھ ���ϰ� bonus�� 0�� ���� ��
        if (m_fTimer >= 0.01f && m_iBonus > 0)
        {
            m_fTimer = 0;
            //���ʽ� ���� �����ϰ� ���ھ �ջ�
            m_iBonus -= (int)BONUS::GOAL_DECREASE;
            m_iScore += (int)BONUS::GOAL_DECREASE;
            if (m_iBonus <= 0)
            {
                m_iScore += m_iBonus;
                m_iBonus = 0;
                m_ScoreBox.SetClear();
            }
        }
        //�����ð� ���� �ٽ� Ÿ��Ʋ�� ����
        else if (m_fTimer >= 5.0f)
        {
            m_fTimer = 0;
            m_eScene = SCENE::TITLE;
        }
    }
    //���������� �����ϱ� ���� �÷������� ��
    else
    {
        m_fBonusTimer += deltaTime;

        //���� �ð����� ���ʽ� ���� ����
        if (m_fBonusTimer > 0.05f && m_iBonus > 0)
        {
            m_fBonusTimer = 0;
            if (m_iBonus < (int)BONUS::PLAY_DECREASE)
                m_iBonus = 0;
            else
                m_iBonus -= (int)BONUS::PLAY_DECREASE;
        }

        //���� ���� ��ֹ� Update
        m_ObstacleManager.Update(deltaTime, m_Character.GetDistance(), m_Character.GetSpeed());

        //��ֹ��� ĳ���� �浹 ����(��ֹ� �浹, ���, ���ٹ�)
        switch (m_ObstacleManager.HitCheck(m_Character.GetHitRect()))
        {
            //��ֹ��� �浹�� ĳ���� life�Ҹ�, �ε�ģ animation, ���� Pause ����
        case HITBOX_TYPE::OBSTACLE:
            m_Character.Collision();
            m_bPause = true;
            break;
            //��ֹ� ���
        case HITBOX_TYPE::PASS:
            m_iScore += (int)SCORE::PASS;
            break;
            //�� �ٹ� ȹ��
        case HITBOX_TYPE::CASH:
            m_iScore += (int)SCORE::CASH;
            break;
        default:
            break;
        }

        //���������� �������� �� true ��ȯ
        m_bGoal = m_Goal.Update(m_Character.GetDistance(), m_Character.GetHitRect());
    }

    //������ �������̽� ������Ʈ
    m_ScoreBox.Update(m_iScore, m_iBonus);
    m_Distance.Update(m_Character.GetDistance());
}

//���� ���۸��� ����� backDC�� ��� ��ü�� �׸��� ��ȯ
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
        //��� -> �������� -> ĳ���� �� ��ֹ� -> ĳ���� -> ĳ���� �� ��ֹ� -> �������̽�
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