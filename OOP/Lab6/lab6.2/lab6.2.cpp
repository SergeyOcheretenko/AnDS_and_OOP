// lab6.2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab6.2.h"
#include <vector>
using namespace std;

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int** mas;
vector<int> nums;
int n;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
long GetTextFromClipboard(HWND, char*, long);
void CreateMatrix(vector<int>);
int Determinant(int**, int);

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
    LoadStringW(hInstance, IDC_LAB62, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB62));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB62));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB62);
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
    char text[700] = {};
    string str;
    switch (message)
    {
    case WM_CREATE:
    {
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 340, 250, 200, SWP_DEFERERASE);
    }
    
    case IDR_RESTART:
    {
        nums.clear();
        GetTextFromClipboard(hWnd, text, 700);
        str = text;
        string num;
        int count = 0;
        while (str != "") {
            num = str.substr(0, str.find_first_of("\n"));
            char buffer[100] = {};
            nums.push_back(stod(num));
            //a[count] = stod(num);
            str = str.substr(str.find_first_of("\n") + 1);
        }
        n = (int)sqrt(nums.size());
        CreateMatrix(nums);
        InvalidateRect(hWnd, NULL, TRUE);
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
       
        int det = Determinant(mas, n);
        int count = det;
        int size = 0;
        if (det < 0) {
            count = -1 * det;
            ++size;
        }
        while (count) {
            count /= 10;
            size++;
        }
        char buffer[64] = {};
        sprintf_s(buffer, "%i", det);
        TextOut(hdc, 20, 20, buffer, size);

        EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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

long GetTextFromClipboard(HWND hWnd, char* dest, long maxsize) {
    HGLOBAL hglb;
    LPTSTR lptstr;
    long size, res;

    res = 0;
    if (!IsClipboardFormatAvailable(CF_TEXT) || !OpenClipboard(hWnd)) return 0;
    hglb = GetClipboardData(CF_TEXT);
    if (hglb != NULL) {
        lptstr = (char*)GlobalLock(hglb);
        if (lptstr != NULL)
        {
            size = strlen(lptstr);
            strcpy_s(dest, maxsize, lptstr);
            res = size;
            GlobalUnlock(hglb);
        }
    }
    CloseClipboard();
    return res;
}

void CreateMatrix(vector<int> vector) {
    int n = sqrt(vector.size());
    int count = 0;
    mas = new int* [n];
    for (int i = 0; i < n; i++) {
        mas[i] = new int[n];
        for (int j = 0; j < n; j++) {
            mas[i][j] = vector[count];
            ++count;
        }
    }
}

int Determinant(int** T, int N)
{
    double det;
    int sub_j, s;
    int** subT;
    switch (N)
    {
    case 1:
        return T[0][0];
    case 2:
        return T[0][0] * T[1][1] - T[0][1] * T[1][0];
    default:
        subT = new int* [N - 1];
        det = 0;
        s = 1;
        for (int i = 0; i < N; i++)
        {
            sub_j = 0;
            for (int j = 0; j < N; j++)
                if (i != j)
                    subT[sub_j++] = T[j] + 1;

            det = det + s * T[i][0] * Determinant(subT, N - 1);
            s = -s;
        };
        delete[] subT;
        return det;
    };
};
