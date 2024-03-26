// Circus_Charlie.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Circus_Charlie.h"
#include "GameManager.h"


HINSTANCE hInst;
LPCTSTR lpszClass = TEXT("Circus Charlie");

ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    MyRegisterClass(hInstance);

    HWND hWnd = CreateWindowW(lpszClass, lpszClass, WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, 0, (int)WINDOW_SIZE::WIDTH, (int)WINDOW_SIZE::HEIGHT, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    HDC hdc = GetDC(hWnd);

    ULONGLONG curTime, limitTime = GetTickCount64();

    //FPS 설정
    int fps = 60;
    int frameRate = 1000 / fps;

    //msg 초기화
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    GameManager::GetInstance()->Init(hWnd, hdc);

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            curTime = GetTickCount64();
            if (limitTime <= curTime)
            {
                float deltaTime = (curTime - limitTime + frameRate) * 0.001f;
                limitTime = curTime + frameRate;

                //UPDATE
                GameManager::GetInstance()->Update(deltaTime);

                //DRAW
                GameManager::GetInstance()->Draw(hdc);
            }
        }
    }

    GameManager::GetInstance()->Release();

    ReleaseDC(hWnd, hdc);

    return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = lpszClass;
    wcex.hIconSm = NULL;

    return RegisterClassExW(&wcex);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
