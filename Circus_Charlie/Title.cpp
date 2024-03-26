#include "Title.h"

Title::Title() : m_iCursorY(0), m_fTimer(0), m_iStartidx(1)
{
}

Title::~Title()
{
}

void Title::Init()
{
    //TITLE Bitmap Load
    for (int i = (int)TITLE::START; i < (int)TITLE::COUNT; i++)
        m_arrTitle[i] = BitMapManager::GetInstance()->GetImage((int)IMAGE::TITLE_1 + i);

    //MENU Bitmap Load
    for (int i = (int)MENU::START; i < (int)MENU::COUNT; i++)
        m_arrMenu[i] = BitMapManager::GetInstance()->GetImage((int)IMAGE::MENU_1 + i);

    
    m_iTitle_Mid_X = ((int)WINDOW_SIZE::WIDTH - m_arrTitle[(int)TITLE::TITLE]->GetSize().cx) * 0.5f;
    m_iStarGap = m_arrTitle[(int)TITLE::STAR_1]->GetSize().cy + 2;
    
    m_iPlaySelet_Mid_X = ((int)WINDOW_SIZE::WIDTH - m_arrMenu[(int)MENU::MENU_1]->GetSize().cx) * 0.5f;
    m_iPlayer_Gap = m_arrMenu[(int)MENU::MENU_2]->GetSize().cy + 10;

    //별이 그려지는 시작 left right top bottom 좌표 Init
    m_StarDrawRect.left = m_iTitle_Mid_X;
    m_StarDrawRect.top = (int)TITLE_POS::TITLE_NAME_Y - m_iStarGap * 2;
    m_StarDrawRect.right = m_StarDrawRect.left + m_iStarGap * ((int)STAR_COUNT::HORIZONTAL - 1);
    m_StarDrawRect.bottom = m_StarDrawRect.top + m_iStarGap * ((int)STAR_COUNT::VERTICAL + 1);
}

void Title::Draw(HDC hdc)
{
    //TITLE NAME
    m_arrTitle[(int)TITLE::TITLE]->Draw(hdc, m_iTitle_Mid_X, (int)TITLE_POS::TITLE_NAME_Y);
    
    //Star
    DrawStar(hdc);

    //PLAY SELECT MENU
    m_arrMenu[(int)MENU::MENU_1]->Draw(hdc, m_iPlaySelet_Mid_X, (int)TITLE_POS::PLAYER_SELECT_MENU_Y);
    
    //POINT = Cursor
    m_arrMenu[(int)MENU::POINT]->Draw(hdc, m_iPlaySelet_Mid_X + (int)TITLE_POS::POINT_ADD_X, (int)TITLE_POS::PLAYER_AND_POINT_START_Y + m_iCursorY * m_iPlayer_Gap);
    
    //PLAYER 1 ~ 4 MENU
    for (int i = (int)MENU::MENU_2; i <= (int)MENU::MENU_5; i++)
        m_arrMenu[i]->Draw(hdc, m_iPlaySelet_Mid_X + (int)TITLE_POS::PLAYER_ADD_X, (int)TITLE_POS::PLAYER_AND_POINT_START_Y + m_iPlayer_Gap * (i - 1));
}

void Title::DrawStar(HDC hdc)
{    
    int star_idx = m_iStartidx;
    int tmpCol;

    //위(왼쪽->오른쪽) 아래(오른쪽->왼쪽) 별 그리기 
    for (int i = 0; i < (int)STAR_COUNT::HORIZONTAL; i++, star_idx++)
    {
        if (star_idx > (int)TITLE::STAR_3)
            star_idx = (int)TITLE::STAR_1;

        tmpCol = m_iStarGap * i;

        //위 1 - 2 - 3
        m_arrTitle[star_idx]->Draw(hdc, m_StarDrawRect.left + tmpCol, m_StarDrawRect.top);
        //아래 3 - 2 - 1
        m_arrTitle[star_idx]->Draw(hdc, m_StarDrawRect.right - tmpCol, m_StarDrawRect.bottom);
    }
    
    star_idx = m_iStartidx;

    //오른쪽(위->아래) 왼쪽(아래->위) 별 그리기
    for (int i = 1; i <= (int)STAR_COUNT::VERTICAL; i++, star_idx++)
    {
        if (star_idx > (int)TITLE::STAR_3)
            star_idx = (int)TITLE::STAR_1;

        tmpCol = m_iStarGap * i;

        //오른쪽 1 - 2 - 3
        m_arrTitle[star_idx]->Draw(hdc, m_StarDrawRect.right + m_iStarGap, m_StarDrawRect.top + tmpCol);
        //왼쪽 3 - 2 - 1
        m_arrTitle[star_idx]->Draw(hdc, m_StarDrawRect.left - m_iStarGap, m_StarDrawRect.bottom - tmpCol);
    }
}

bool Title::Update(float deltaTime)
{
    m_fTimer += deltaTime;
    
    //일정 시간마다 별 시작 인덱스 바꾸기
    if (m_fTimer > 0.05f)
    {
        m_fTimer = 0;

        m_iStartidx++;

        if (m_iStartidx > (int)TITLE::STAR_3)
            m_iStartidx = (int)TITLE::STAR_1;
    }

    //Key Input
    if ((GetAsyncKeyState(VK_UP) & 0x0001) && m_iCursorY > 0)
    {
        m_iCursorY--;
    }
    else if ((GetAsyncKeyState(VK_DOWN) & 0x0001) && m_iCursorY < 3)
    {
        m_iCursorY++;
    }
    else if (GetAsyncKeyState(VK_RETURN))
    {
        m_iCursorY = 0;
        return true;
    }

    return false;
}
