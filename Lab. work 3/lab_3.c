#include <windows.h>
#include <stdio.h>
#include <math.h>

//Создаём прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define PI 3.1415926
#define width 1920
#define height 1080

#define n 11
#define circleR 300
#define verticRadius 14
#define arrowSize 6
#define loopSize 8

POINT aroundMiddle(POINT from, POINT to) {
    float alpha = atan2(to.y - from.y, to.x - from.x);
    POINT result;
    result.x = (verticRadius * 2) * cos(PI / 2 - alpha);
    result.y = (verticRadius * 2) * sin(PI / 2 - alpha);
    return result;
}

POINT arrowCoords(POINT from, POINT to) {
    float alpha = atan2(to.y - from.y, to.x - from.x);
    float distance = sqrt(pow((to.x - from.x), 2) + pow((to.y - from.y), 2));
    POINT arrow;
    arrow.x = from.x + (distance - verticRadius - arrowSize) * cos(alpha);
    arrow.y = from.y + (distance - verticRadius - arrowSize) * sin(alpha);
    return arrow;
}

//объявляем строку-имя программы
char ProgName[] = "Lab 1";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName = ProgName; //имя программы - объявлено выше
    w.hInstance = hInstance; //идентификатор текущего приложения
    w.lpfnWndProc = WndProc; //указатель на функцию окна
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon = 0; //иконки у нас не будет пока
    w.lpszMenuName = 0; //и меню пока не будет
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// цвет фона окна
    w.style = CS_HREDRAW | CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    //Создадим окно в памяти, заполнив аргументы CreateWindow
    hWnd = CreateWindow(ProgName, //Имя программы
        L"Lab 1 Ocheretenko", //Заголовок окна
        WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
        0, //положение окна на экране по х
        0, //положение по у
        width, //ширина
        height, //висота
        (HWND)NULL, //идентификатор родительского окна
        (HMENU)NULL, //идентификатор меню
        (HINSTANCE)hInstance, //идентификатор экземпляра программы
        (HINSTANCE)NULL); //отсутствие дополнительных параметров

//Выводим окно из памяти на экран
    //Обновим содержимое окна
     //   UpdateWindow(hWnd);

    //Цикл одержання повідомлень

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) { //Получаем сообщение из очереди
        TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
        DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
    }

    return(lpMsg.wParam);
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
    WPARAM wParam, LPARAM lParam)
{
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

    int A[n][n] = {
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0 },
        {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
        {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
        {0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0 }
    };

    int simetricA[n][n] = {
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1},
        {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0}
    };

    float startX = (width) / 4;
    float startY = height / 2;

    float nonOrientedX = startX * 3;

    //Цикл обработки сообщений
    switch (messg) {
        //сообщение рисования
    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps);

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        SelectObject(hdc, KPen);

        // white BG
        POINT vertix[] = { {0, 0}, {width, 0}, {width, height}, {0, height} };
        Polygon(hdc, vertix, sizeof(vertix) / sizeof(vertix[0]));

        // draw circles
        HPEN dashPen = CreatePen(PS_DASH, 1, RGB(20, 20, 5));
        SelectObject(hdc, dashPen);
        Ellipse(hdc, startX - circleR, startY - circleR, startX + circleR, startY + circleR);
        Ellipse(hdc, (nonOrientedX)-circleR, startY - circleR, nonOrientedX + circleR, startY + circleR);

        POINT verts[n]; // array of vertices coordinates

        {
            float newX = startX;
            float newY = startY;
            float alpha = 2 * PI / (n - 1);

            int i = 1;

            verts[0].x = startX;
            verts[0].y = startY;

            for (float angle = 0; i < n; angle += alpha) {
                float newX = startX + circleR * cos(angle);
                float newY = startY + circleR * sin(angle);
                verts[i].x = newX;
                verts[i].y = newY;
                i++;
            };
        }

        {
            SelectObject(hdc, KPen);

            POINT center;
            center.x = startX;
            center.y = startY;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    POINT from = verts[i];
                    POINT to = verts[j];
                    if (A[i][j] == 1) {
                        float alpha = atan2(to.y - from.y, to.x - from.x);
                        if (i == j) {
                            float alpha2 = atan2(to.y - center.y, to.x - center.x);
                            float distance = sqrt(pow((center.x - from.x), 2) + pow((center.y - from.y), 2));

                            POINT loop;
                            loop.x = center.x + (distance + verticRadius) * cos(alpha2);
                            loop.y = center.y + (distance + verticRadius) * sin(alpha2);
                            Arc(hdc, loop.x - loopSize, loop.y - loopSize, loop.x + loopSize, loop.y + loopSize, loop.x - loopSize, loop.y - loopSize, loop.x - loopSize, loop.y - loopSize);
                        }
                        else if (abs(i - j) == 5 && i != 0 && j != 0) {
                            POINT move = aroundMiddle(from, to);
                            MoveToEx(hdc, from.x, from.y, NULL);
                            float middleX = (from.x + to.x) / 2;
                            float middleY = (from.y + to.y) / 2;
                            middleX += move.x;
                            middleY -= move.y;
                            POINT middle = { middleX, middleY };
                            LineTo(hdc, middleX, middleY);
                            LineTo(hdc, to.x, to.y);
                            POINT arrow = arrowCoords(middle, to);
                            POINT vertices[] = { {0, 0}, {0, 0}, {0, 0} };
                            for (int i = 0; i < 3; i++) {
                                vertices[i].x = arrowSize * cos(alpha) + arrow.x;
                                vertices[i].y = arrowSize * sin(alpha) + arrow.y;
                                alpha += (1.0 / 3.0) * (2 * PI);
                            }
                            Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
                        }
                        else {
                            POINT move; // смещение относительно центра вершины 
                            move.x = (verticRadius / 2) * cos(PI / 2 - alpha);
                            move.y = (verticRadius / 2) * sin(PI / 2 - alpha);
                            POINT newFrom = { from.x + move.x, from.y - move.y };
                            POINT newTo = { to.x + move.x, to.y - move.y };
                            MoveToEx(hdc, newFrom.x, newFrom.y, NULL);
                            LineTo(hdc, newTo.x, newTo.y);
                            POINT arrow = arrowCoords(newFrom, newTo);
                            POINT vertices[] = { {0, 0}, {0, 0}, {0, 0} };
                            for (int i = 0; i < 3; i++) {
                                vertices[i].x = arrowSize * cos(alpha) + arrow.x;
                                vertices[i].y = arrowSize * sin(alpha) + arrow.y;
                                alpha += (1.0 / 3.0) * (2 * PI);
                            }
                            Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
                        }
                    }
                }
            }

        }

        POINT nonOrientedVerts[n];
        for (int i = 0; i < n; i++) {
            nonOrientedVerts[i].x = verts[i].x + (nonOrientedX - startX);
            nonOrientedVerts[i].y = verts[i].y;
        }

        POINT nonCenter;
        nonCenter.x = nonOrientedX;
        nonCenter.y = startY;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                SelectObject(hdc, KPen);
                POINT from = nonOrientedVerts[i];
                POINT to = nonOrientedVerts[j];
                if (simetricA[i][j] == 1 && to.x >= from.x) {
                    if (i == j) {
                        float alpha2 = atan2(to.y - nonCenter.y, to.x - nonCenter.x);
                        float distance2 = sqrt(pow((to.x - nonCenter.x), 2) + pow((to.y - nonCenter.y), 2));

                        POINT loop;
                        loop.x = nonCenter.x + (distance2 + verticRadius) * cos(alpha2);
                        loop.y = nonCenter.y + (distance2 + verticRadius) * sin(alpha2);
                        Arc(hdc, loop.x - loopSize, loop.y - loopSize, loop.x + loopSize, loop.y + loopSize, loop.x - loopSize, loop.y - loopSize, loop.x - loopSize, loop.y - loopSize);
                    }
                    else if (abs(i - j) == 5 && i != 0 && j != 0) {
                        POINT move = aroundMiddle(from, to);
                        MoveToEx(hdc, from.x, from.y, NULL);
                        float middleX = (from.x + to.x) / 2;
                        float middleY = (from.y + to.y) / 2;
                        middleX += move.x;
                        middleY -= move.y;
                        POINT middle = { middleX, middleY };
                        LineTo(hdc, middleX, middleY);
                        LineTo(hdc, to.x, to.y);
                    }
                    else {
                        MoveToEx(hdc, from.x, from.y, NULL);
                        LineTo(hdc, to.x, to.y); // рисуем прямую линию
                    }

                }
            }
        }

        SelectObject(hdc, BPen);

        for (int i = 0; i < n; i++) {
            char vertName[3];
            snprintf(vertName, 3, "%d", i + 1);

            Ellipse(hdc, verts[i].x - verticRadius, verts[i].y - verticRadius, verts[i].x + verticRadius, verts[i].y + verticRadius);
            TextOutA(hdc, verts[i].x - verticRadius + 6, verts[i].y - verticRadius / 2, vertName, i + 1 < 10 ? 1 : 2);

            Ellipse(hdc, nonOrientedVerts[i].x - verticRadius, nonOrientedVerts[i].y - verticRadius, nonOrientedVerts[i].x + verticRadius, nonOrientedVerts[i].y + verticRadius);
            TextOutA(hdc, nonOrientedVerts[i].x - verticRadius + 6, nonOrientedVerts[i].y - verticRadius / 2, vertName, i + 1 < 10 ? 1 : 2);
        }

        EndPaint(hWnd, &ps);//малювання закінчене
        break;

        //сообщение выхода - разрушение окна
    case WM_DESTROY:
        PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
    }
    return 0;
}
