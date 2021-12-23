// lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab5.h"
#include "my_editor.h"
#include "toolbar.h"
#include "my_table.h"
#include <fstream>

#include "Point_Shape.h"
#include "Cube_Shape.h"
#include "OLineO_Shape.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
MyEditor& editor = editor.getInstance();
Toolbar toolbar;
HWND hWndDlg = NULL;
MyTable* Table = new MyTable;
int prevIndx = 0;
static COLORREF black = RGB(0, 0, 0);
static COLORREF red = RGB(255, 0, 0);
COLORREF prevColor = black;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void selectObj(HWND);
void deleteObj(int);
void drawObj(HWND);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    InitCommonControls();
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB5);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
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
    std::string str = "";
    switch (message)
    {
    case WM_CREATE:
        hWndDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TABLE), hWnd, DlgProc);
        ShowWindow(hWndDlg, SW_SHOW);
        Table->SetCb(selectObj);
        Table->SetCbDel(deleteObj);
        Table->SetDraw(drawObj);
        SetWindowTextW(hWnd, (LPCWSTR)"Режим вводу точок");
        editor.Start(new PointShape);
        toolbar.OnCreate(hWnd, hInst);
        toolbar.OnPointPressed();
        break;
    case WM_SIZE:
        toolbar.OnSize(hWnd);
        break;
    case WM_LBUTTONDOWN:
        editor.OnLBdown(hWnd);
        break;
    case WM_LBUTTONUP:
        editor.OnLBup(hWnd);
        str = editor.GetString();
        Table->Add(hWndDlg, str);
        break;
    case WM_MOUSEMOVE:
        editor.OnMouseMove(hWnd);
        break;
    case WM_INITMENUPOPUP:
        editor.OnInitMenuPopup(hWnd, wParam);
        break;
    case WM_NOTIFY:
        toolbar.OnNotify(hWnd, lParam);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_TABLE:
                ShowWindow(hWndDlg, SW_SHOW);
                break;
            case ID_TOOL_POINT:
            case IDM_POINT:
                toolbar.OnPointPressed();
                SetWindowTextW(hWnd, (LPCWSTR)"Режим вводу точок");
                editor.Start(new PointShape);
                break;
            case ID_TOOL_LINE:
            case IDM_LINE:
                toolbar.OnLinePressed();
                SetWindowTextW(hWnd, (LPCWSTR)"Режим вводу ліній");
                editor.Start(new LineShape);
                break;
            case ID_TOOL_RECT:
            case IDM_RECTANGLE:
                toolbar.OnRectPressed();
                SetWindowTextW(hWnd, (LPCWSTR)"Режим вводу прямокутників");
                editor.Start(new RectShape);
                break;
            case ID_TOOL_ELLIPSE:
            case IDM_ELLIPSE:
                toolbar.OnEllipsePressed();
                SetWindowTextW(hWnd, (LPCWSTR)"Режим вводу еліпсів");
                editor.Start(new EllipseShape);
                break;
            case ID_TOOL_CUBE:
            case IDM_CUBE:
                toolbar.OnCubePressed();
                SetWindowTextW(hWnd, (LPCWSTR)"Режим вводу кубів");
                editor.Start(new CubeShape);
                break;
            case ID_TOOL_OLINEO:
            case IDM_OLINEO:
                toolbar.OnOLineOPressed();
                SetWindowTextW(hWnd, (LPCWSTR)"Режим вводу ліній з кружечками");
                editor.Start(new OLineOShape);
                break;
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
        editor.OnPaint(hWnd);
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

void selectObj(HWND hWnd) {
    int indx = SendDlgItemMessage(hWndDlg, IDC_LIST, LB_GETCURSEL, 0, 0) - 1;
    if (indx > -1 && indx < SendDlgItemMessage(hWndDlg, IDC_LIST, LB_GETCOUNT, 0, 0)) {
        if (prevIndx != NULL || prevIndx == 0) pcshape[prevIndx]->SetColor(prevColor);
        prevColor = pcshape[indx]->color;
        prevIndx = indx;
        pcshape[indx]->SetColor(red);
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void deleteObj(int indx) {
    if (indx > 0 || indx < SendDlgItemMessage(hWndDlg, IDC_LIST, LB_GETCOUNT, 0, 0)) {
        c--;
        for (int i = indx - 1; i < SendDlgItemMessage(hWndDlg, IDC_LIST, LB_GETCOUNT, 0, 0) - 1; i++) pcshape[i] = pcshape[i + 1];
        InvalidateRect(GetParent(hWndDlg), NULL, TRUE);
    }
}

void drawObj(HWND hWnd) {
    string path = "./Objects.txt";
    ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        throw new exception("can't open file");
    }
    else {
        string str;
        string name, x1, y1, x2, y2, col, fill;
        Shape* sh = NULL;
        while (!fin.eof()) {
            str = "";
            getline(fin, str);
            if (str != "" && str != "  Назва		x1	y1	x2	y2") {
                name = str.substr(2, str.find_first_of("\t\t") - 2);
                str = str.substr(str.find_first_of("\t\t") + 2);
                x1 = str.substr(0, str.find_first_of("\t"));
                str = str.substr(str.find_first_of("\t") + 1);
                y1 = str.substr(0, str.find_first_of("\t"));
                str = str.substr(str.find_first_of("\t") + 1);
                x2 = str.substr(0, str.find_first_of("\t"));
                str = str.substr(str.find_first_of("\t") + 1);
                y2 = str.substr(0, str.find_first_of("\t"));
                if (name == "Точка") sh = new PointShape();
                if (name == "Лінія") sh = new LineShape();
                if (name == "Прямокутник") sh = new RectShape();
                if (name == "Еліпс") sh = new EllipseShape();
                if (name == "Куб") sh = new CubeShape();
                if (name == "ОлініяО") sh = new OLineOShape();
                sh->SetColor(black);
                sh->Set((long)stoi(x1), (long)stoi(y1), (long)stoi(x2), (long)stoi(y2));
                pcshape[c] = sh;
                c++;
                name = x1 = y1 = x2 = y2 = col = "";
            }
        }
    }
    fin.close();
    InvalidateRect(hWnd, NULL, TRUE);
}
