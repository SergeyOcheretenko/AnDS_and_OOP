#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "draw.h"
#include "generate.h"
#include "traverse.h"

//Ñîçäà¸ì ïðîòîòèï ôóíêöèè îêíà, êîòîðàÿ áóäåò îïðåäåëåíà íèæå
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI report(LPVOID lpParam);

#define width 1500
#define height 800

const int BUTTON_SWITCH_SCRIPT = 100;

typedef struct {
    HWND* hWnd;
} Params;

//îáúÿâëÿåì ñòðîêó-èìÿ ïðîãðàììû
char ProgName[] = "Lab 6";
int** dfsMatrix = NULL;
int* dfsVisited = NULL;
int** dfsTreeMatrix = NULL;
int** bfsMatrix = NULL;
int* bfsVisited = NULL;
int** bfsTreeMatrix = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //ñîçäà¸ì ýêçåìïëÿð ñòðóêòóðû WNDCLASS

    w.lpszClassName = ProgName; //èìÿ ïðîãðàììû - îáúÿâëåíî âûøå
    w.hInstance = hInstance; //èäåíòèôèêàòîð òåêóùåãî ïðèëîæåíèÿ
    w.lpfnWndProc = WndProc; //óêàçàòåëü íà ôóíêöèþ îêíà
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //çàãðóæàåì êóðñîð
    w.hIcon = 0; //èêîíêè ó íàñ íå áóäåò ïîêà
    w.lpszMenuName = 0; //è ìåíþ ïîêà íå áóäåò
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// öâåò ôîíà îêíà
    w.style = CS_HREDRAW | CS_VREDRAW; //ñòèëü - ïåðåðèñîâûâàåìîå ïî õ è ïî ó
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    //Ñîçäàäèì îêíî â ïàìÿòè, çàïîëíèâ àðãóìåíòû CreateWindow
    hWnd = CreateWindow(ProgName, //Èìÿ ïðîãðàììû
        L"Lab 6 Ocheretenko", //Çàãîëîâîê îêíà
        WS_OVERLAPPEDWINDOW, //Ñòèëü îêíà - ïåðåêðûâàþùååñÿ
        0, //ïîëîæåíèå îêíà íà ýêðàíå ïî õ
        0, //ïîëîæåíèå ïî ó
        width, //øèðèíà
        height, //âèñîòà
        (HWND)NULL, //èäåíòèôèêàòîð ðîäèòåëüñêîãî îêíà
        (HMENU)NULL, //èäåíòèôèêàòîð ìåíþ
        (HINSTANCE)hInstance, //èäåíòèôèêàòîð ýêçåìïëÿðà ïðîãðàììû
        (HINSTANCE)NULL); //îòñóòñòâèå äîïîëíèòåëüíûõ ïàðàìåòðîâ
    HWND hwndButton = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed
        L"Çì³íèòè ñêðèïò",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        10,         // x position
        10,         // y position
        150,        // Button width
        40,        // Button height
        hWnd,
        (HMENU)BUTTON_SWITCH_SCRIPT,       // No menu.
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    if (AllocConsole()) {
        FILE* pCout;
        freopen_s(&pCout, "CONOUT$", "w", stdout);
        SetConsoleTitle(L"LAB REPORT");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    }

    Params* params = malloc(sizeof(Params));
    params->hWnd = &hWnd;
    HANDLE scriptThread = CreateThread(NULL, 0, report, params, 0, NULL);

    ShowWindow(hWnd, nCmdShow);

    BOOL bRet;
    while ((bRet = GetMessage(&lpMsg, hWnd, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            return(lpMsg.wParam);
        }
        else
        {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    }

    return(lpMsg.wParam);
}

int script = 1;
//Ôóíêöèÿ îêíà
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
    WPARAM wParam, LPARAM lParam)
{
    HDC hdc; //ñîçäà¸ì êîíòåêñò óñòðîéñòâà
    PAINTSTRUCT ps; //ñîçäà¸ì ýêçåìïëÿð ñòðóêòóðû ãðàôè÷åñêîãî âûâîäà

    float startX = (width) / 4;
    float startY = height / 2;
    float secondX = startX * 3;
    //Öèêë îáðàáîòêè ñîîáùåíèé
    switch (messg) {
        //ñîîáùåíèå ðèñîâàíèÿ
    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps);

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        HPEN RPen = CreatePen(PS_SOLID, 3, RGB(255, 20, 5));
        drawBackground(width, height, hdc);
        if (dfsMatrix != NULL)
            drawOrientedGraph(startX, startY, hdc, BPen, KPen, RPen, dfsMatrix, dfsVisited, n);
        if (dfsTreeMatrix != NULL)
            drawOrientedGraph(secondX, startY, hdc, BPen, KPen, RPen, dfsTreeMatrix, NULL, n);


        EndPaint(hWnd, &ps);//ìàëþâàííÿ çàê³í÷åíå
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == BUTTON_SWITCH_SCRIPT)
            script = (script == 1) ? 2 : 1;
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_DESTROY:
        PostQuitMessage(0); //Ïîñûëàåì ñîîáùåíèå âûõîäà ñ êîäîì 0 - íîðìàëüíîå çàâåðøåíèå
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam)); //îñâîáîæäàåì î÷åðåäü ïðèëîæåíèÿ îò íåðàñïîçíàíûõ
    }
    return 0;
}

void print2DArray(int** array, int size)
{
    printf("\t");
    for (int i = 0; i < size; i++)
    {
        printf("%i\t", i + 1);
    }
    printf("\n\n");
    for (int i = 0; i < size; i++)
    {
        printf("%i\t", i + 1);
        for (int j = 0; j < size; j++)
        {
            printf("%i\t", array[i][j]);
        }
        printf("\n");
    }
}

DWORD WINAPI report(LPVOID lpParam)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Params* args = lpParam;

    dfsMatrix = createMatrix(n, unique_seed, k(unique_seed));
    dfsVisited = createArray(n);
    for (int i = 0; i < n; i++)
    {
        dfsVisited[i] = 0;
    }
    printf("\n\nÌàòðèöÿ ñóì³æíîñò³ ãðàôó:\n\n");
    print2DArray(dfsMatrix, n);

    printf("\nÂèêîíóºòüñÿ îáõ³ä äëÿ ñòâîðåííÿ ì³í³ìàëüíîãî ê³ñòÿêó ãðàôó. Äëÿ ïåðåõîäó äî íàñòóïíîãî êðîêó, íàòèñí³òü áóäü-ÿêó êëàâ³øó. Ïðîãðåñ áóäå â³äîáðàæåíî ó ãðàô³÷íîìó â³êí³");
    dfsTreeMatrix = dfs(args->hWnd, dfsVisited, dfsMatrix, n);
    printf("\nÎáõ³ä çàâåðøåíî.\n");
}
