// lab6.1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab6.1.h"
using namespace std;
#include <time.h> 

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
long n, minValue, maxValue;
int** mas;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void OnCopyData(HWND, WPARAM, LPARAM);
void startThirdPart(HWND);
int PutTextToClipboard(HWND, const char*);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB61, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB61));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB61));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB61);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    srand(time(NULL));
    HWND hWndL2;
    switch (message)
    {
    case WM_CREATE:
    {
        SetWindowPos(hWnd, HWND_BOTTOM, 560, 40, 600, 600, SWP_DEFERERASE);
        break;
    }
    case WM_COPYDATA:
    {
        OnCopyData(hWnd, wParam, lParam);
        startThirdPart(hWnd);
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            int current, size;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    current = mas[i][j];
                    size = 0;
                    while (current) {
                        current /= 10;
                        size++;
                    }
                    char buffer[64] = {};
                    sprintf_s(buffer, "%i", mas[i][j]);
                    TextOut(hdc, 20 + i * 40, 20 + j * 40, buffer, size);
                }
            }
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        hWndL2 = FindWindow("LAB62", NULL);
        if (hWndL2) PostMessage(hWndL2, WM_DESTROY, (WPARAM)wParam, 0);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    COPYDATASTRUCT* cds;
    cds = (COPYDATASTRUCT*)lParam;
    long* p = (long*)cds->lpData;
    n = p[0];
    minValue = p[1];
    maxValue = p[2];
    mas = new int* [n];
    for (int i = 0; i < n; i++) {
        mas[i] = new int[n];
        for (int j = 0; j < n; j++) {
            mas[i][j] = rand() % (maxValue - minValue + 1) + minValue;
        }
    }
    InvalidateRect(hWnd, NULL, TRUE);
}


int PutTextToClipboard(HWND hWnd, const char* src) {
    HGLOBAL hglbCopy;
    BYTE* pTmp;
    long len;

    if (src == NULL || src[0] == 0) return 0;
    len = strlen(src);
    hglbCopy = GlobalAlloc(GHND, len + 1);
    if (hglbCopy == NULL) return 0;
    pTmp = (BYTE*)GlobalLock(hglbCopy);
    memcpy(pTmp, src, len + 1);
    GlobalUnlock(hglbCopy);
    if (!OpenClipboard(hWnd)) {
        GlobalFree(hglbCopy);
        return 0;
    }
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hglbCopy);
    CloseClipboard();
    return 1;
}

void startThirdPart(HWND hWnd) {
    HWND hWndDataCreator = FindWindow("LAB62", NULL);
    string str = "";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int current = mas[i][j];
            str += (to_string(current) + "\n");
        }
    }
    char* a = new char[str.size() + 1];
    a[str.size()] = 0;
    memcpy(a, str.c_str(), str.size());
    PutTextToClipboard(hWnd, a);
    if (hWndDataCreator == NULL) WinExec("lab6.2.exe", SW_SHOW);
    else  PostMessage(hWndDataCreator, IDB_RESTART, 0, 0);

}