#include <windows.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "resource.h"

HINSTANCE hInst;
LPCTSTR szWindowClass = "WindowClass";
LPCTSTR szTitle = "Title";

void MyRegisterClass(HINSTANCE hInstance);
void InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

std::vector<std::string> LabPaths
{
    "exes\\SProLab1Var1.exe",
    "exes\\SProLab2Var1.exe",
    "exes\\SProLab3Var1.exe",
    "exes\\SProLab4Var1.exe",
    "exes\\SProLab5Var1.exe",
    "exes\\SProLab6Var9.exe",
    "exes\\SProLab7Var9.exe",
    "exes\\SProLab8Var9.exe",
    "exes\\SProLab9Var9.exe",
};
PROCESS_INFORMATION ProcessInfo { };

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MyRegisterClass(hInstance);
    InitInstance(hInstance, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
} 

void MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_HAND);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = NULL;

    RegisterClassEx(&wcex);
}

void InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;
    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
        {
            int index = -1;
            switch (wParam)
            {
                case ID_LABS_LAB1:
                {
                    index = 0;
                    break;
                }
                case ID_LABS_LAB2:
                {
                    index = 1;
                    break;
                }
                case ID_LABS_LAB3:
                {
                    index = 2;
                    break;
                }
                case ID_LABS_LAB4:
                {
                    index = 3;
                    break;
                }
                case ID_LABS_LAB5:
                {
                    index = 4;
                    break;
                }
                case ID_LABS_LAB6:
                {
                    index = 5;
                    break;
                }
                case ID_LABS_LAB7:
                {
                    index = 6;
                    break;
                }
                case ID_LABS_LAB8:
                {
                    index = 7;
                    break;
                }
                case ID_LABS_LAB9:
                {
                    index = 8;
                    break;
                }
            }

            if (index == -1)
            {
                break;
            }

            if (ProcessInfo.hProcess)
            {
                TerminateProcess(ProcessInfo.hProcess, 0);
                CloseHandle(ProcessInfo.hProcess);
                CloseHandle(ProcessInfo.hThread);
            }
            char cmd[256] { };
            STARTUPINFO startup_info { };
            CreateProcess(LabPaths[index].c_str(), cmd, NULL, NULL, TRUE, 0, NULL, NULL, &startup_info, &ProcessInfo);

            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

