#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "draw.h"
#include "generate.h"
#include "algo.h"

//������ �������� ������� ����, ������� ����� ���������� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void report1();
void report2();

#define width 1500
#define height 800

const int BUTTON_SWITCH_SCRIPT = 100;


//��������� ������-��� ���������
char ProgName[] = "Lab 4";
int** matrix;
int** symmetricMatrix;
int** modifiedMatrix;
int** condensedMatrix;
int condensedSize = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //������ ��������� ��������� WNDCLASS

    w.lpszClassName = ProgName; //��� ��������� - ��������� ����
    w.hInstance = hInstance; //������������� �������� ����������
    w.lpfnWndProc = WndProc; //��������� �� ������� ����
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //��������� ������
    w.hIcon = 0; //������ � ��� �� ����� ����
    w.lpszMenuName = 0; //� ���� ���� �� �����
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// ���� ���� ����
    w.style = CS_HREDRAW | CS_VREDRAW; //����� - ���������������� �� � � �� �
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    //�������� ���� � ������, �������� ��������� CreateWindow
    hWnd = CreateWindow(ProgName, //��� ���������
        L"Lab 4 Ocheretenko", //��������� ����
        WS_OVERLAPPEDWINDOW, //����� ���� - ���������������
        0, //��������� ���� �� ������ �� �
        0, //��������� �� �
        width, //������
        height, //������
        (HWND)NULL, //������������� ������������� ����
        (HMENU)NULL, //������������� ����
        (HINSTANCE)hInstance, //������������� ���������� ���������
        (HINSTANCE)NULL); //���������� �������������� ����������
    HWND hwndButton = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"������ ������",      // Button text 
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

    report1();
    report2();

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
//������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
    WPARAM wParam, LPARAM lParam)
{
    HDC hdc; //������ �������� ����������
    PAINTSTRUCT ps; //������ ��������� ��������� ������������ ������

    float startX = (width) / 4;
    float startY = height / 2;
    float secondX = startX * 3;
    //���� ��������� ���������
    switch (messg) {
        //��������� ���������
    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps);

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        drawBackground(width, height, hdc);
        if (script == 1)
        {
            drawOrientedGraph(startX, startY, hdc, BPen, KPen, matrix, n);
            drawNonOrientedGraph(secondX, startY, hdc, BPen, KPen, symmetricMatrix, n);
        }
        else if (script == 2)
        {
            drawOrientedGraph(startX, startY, hdc, BPen, KPen, modifiedMatrix, n);
            drawOrientedGraph(secondX, startY, hdc, BPen, KPen, condensedMatrix, condensedSize);
        }

        EndPaint(hWnd, &ps);//��������� ��������
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == BUTTON_SWITCH_SCRIPT) 
            script = (script == 1) ? 2 : 1;
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_DESTROY:
        PostQuitMessage(0); //�������� ��������� ������ � ����� 0 - ���������� ����������
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam)); //����������� ������� ���������� �� �������������
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

void report1()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    matrix = createMatrix(n, unique_seed, k1(unique_seed));
    printf("\n\n������� �������� ������� �����:\n\n");
    print2DArray(matrix, n);

    int** orientedDegrees = getOrientedDegrees(matrix, n);
    printf("\n\n������� ������ ������� �����:\n\n");
    printf("#\t�����\t������\n");
    for (int i = 0; i < n; i++)
    {
        printf("%i\t%i\t\t%i\n", i + 1, orientedDegrees[i][1], orientedDegrees[i][0]);
    }

    int orientedRegularityDegree = orientedRegularDegree(orientedDegrees, n);
    if (orientedRegularityDegree == -1)
        printf("������ ���� �� � ���������.");
    else
        printf("������ ���� %i-���������", orientedRegularityDegree);

    printf("\n\n������ ������ ������� �����:  ");
    for (int i = 0; i < n; i++)
    {
        if (orientedDegrees[i][1] == 0)
            printf("%i  ", i + 1);
    }
    printf("\n\n������ ����� ������� �����:  ");
    for (int i = 0; i < n; i++)
    {
        if (orientedDegrees[i][0] == 0)
            printf("%i  ", i + 1);
    }
    printf("\n\n������ ����������� ������ ������� �����:  ");
    for (int i = 0; i < n; i++)
    {
        if (orientedDegrees[i][0] == 0 && orientedDegrees[i][1] == 0)
            printf("%i  ", i + 1);
    }

    symmetricMatrix = createSymmetricMatrix(matrix, n);
    printf("\n\n������� �������� ������������� �����:\n\n");
    print2DArray(symmetricMatrix, n);

    int* nonOrientedDegrees = getNonOrientedDegrees(symmetricMatrix, n);
    printf("\n\n������� ������ ������������� �����:\n\n");
    printf("#\t������\n");
    for (int i = 0; i < n; i++)
    {
        printf("%i\t%i\n", i + 1, nonOrientedDegrees[i]);
    }

    int nonOrientedRegularityDegree = nonOrientedRegularDegree(nonOrientedDegrees, n);
    if (nonOrientedRegularityDegree == -1)
        printf("������������ ���� �� � ���������.");
    else
        printf("������������ ���� %i-���������", nonOrientedRegularityDegree);

    printf("\n\n������ ������� ������ ������������ �����:  ");
    for (int i = 0; i < n; i++)
    {
        if (nonOrientedDegrees[i] == 1)
            printf("%i  ", i + 1);
    }
    printf("\n\n������ ����������� ������ ������������� �����:  ");
    for (int i = 0; i < n; i++)
    {
        if (orientedDegrees[i] == 0)
            printf("%i  ", i + 1);
    }
}

void report2()
{
    modifiedMatrix = createMatrix(n, unique_seed, k2(unique_seed));
    printf("\n\n������� �������� �������������� �����:\n\n\t");
    print2DArray(modifiedMatrix, n);

    int** modifiedDegrees = getOrientedDegrees(modifiedMatrix, n);
    printf("\n\n������� ������ �������������� �����:\n\n");
    printf("#\t�����\t������\n");
    for (int i = 0; i < n; i++)
    {
        printf("%i\t%i\t\t%i\n", i + 1, modifiedDegrees[i][1], modifiedDegrees[i][0]);
    }

    int pathesOfLength2Amount;
    int** pathesOfLength2 = getAllPath2(modifiedMatrix, &pathesOfLength2Amount, 1);
    printf("\n\n����� �������� 2 � �������������� �����:\n");
    for (int i = 0; i < pathesOfLength2Amount; i++)
    {
        printf("[%i-%i-%i]\t",
            pathesOfLength2[i][0] + 1,
            pathesOfLength2[i][1] + 1,
            pathesOfLength2[i][2] + 1);
    }

    int pathesOfLength3Amount;
    int** pathesOfLength3 = getAllPath3(modifiedMatrix, &pathesOfLength3Amount, 1);
    printf("\n\n����� �������� 2 � �������������� �����:\n");
    for (int i = 0; i < pathesOfLength3Amount; i++)
    {
        printf("[%i-%i-%i-%i]\t",
            pathesOfLength3[i][0] + 1,
            pathesOfLength3[i][1] + 1,
            pathesOfLength3[i][2] + 1,
            pathesOfLength3[i][3] + 1);
    }

    int** modifiedAccessibility = getAccessibilityMatrix(modifiedMatrix, n);
    printf("\n\n������� ��������� �������������� �����:\n\n");
    print2DArray(modifiedAccessibility, n);

    int** modifiedStrongConnectionMatrix = getStrongConnectionMatrix(modifiedAccessibility, n);
    printf("\n\n������� ������ ��'������ �������������� �����:\n\n");
    print2DArray(modifiedStrongConnectionMatrix, n);

    int componentsAmount;
    int** modifiedGraphStrongConnectionComponents = getComponents(
        modifiedStrongConnectionMatrix,
        &componentsAmount);
    printf("\n\n������ ��������� ������ ��'������ �������������� �����:\n");
    for (int i = 0; modifiedGraphStrongConnectionComponents[i][0] != -1; i++)
    {
        printf("\n���������� #%i:   ", i + 1);
        for (int j = 0; modifiedGraphStrongConnectionComponents[i][j] != -1; j++)
        {
            printf("%i  ", modifiedGraphStrongConnectionComponents[i][j] + 1);
        }
    }

    condensedMatrix = condense(
        modifiedGraphStrongConnectionComponents,
        componentsAmount,
        modifiedAccessibility);
    condensedSize = componentsAmount;
    printf("\n\n������� �������� ����� ����������� �������������� �����:\n");
    print2DArray(condensedMatrix, componentsAmount);
}