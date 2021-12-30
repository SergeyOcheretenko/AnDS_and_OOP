#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "draw.h"

POINT aroundMiddle(POINT from, POINT to) 
{
    float alpha = atan2(to.y - from.y, to.x - from.x);
    POINT result;
    result.x = (verticeRadius * 2) * cos(PI / 2 - alpha);
    result.y = (verticeRadius * 2) * sin(PI / 2 - alpha);
    return result;
}

POINT arrowCoords(POINT from, POINT to) 
{
    float alpha = atan2(to.y - from.y, to.x - from.x);
    float distance = sqrt(pow((to.x - from.x), 2) + pow((to.y - from.y), 2));
    POINT arrow;
    arrow.x = from.x + (distance - verticeRadius - arrowSize) * cos(alpha);
    arrow.y = from.y + (distance - verticeRadius - arrowSize) * sin(alpha);
    return arrow;
}

void drawBackground(int width, int height, HDC hdc)
{
    POINT corners[] = { {0, 0}, {width, 0}, {width, height}, {0, height} };
    Polygon(hdc, corners, sizeof(corners) / sizeof(corners[0]));
}

void drawOrientedGraph(int posX, int posY, HDC hdc, HPEN pen1, HPEN pen2, int** matrix, int power)
{
    SelectObject(hdc, pen2);

    HPEN dashPen = CreatePen(PS_DASH, 1, RGB(20, 20, 5));
    SelectObject(hdc, dashPen);
    Ellipse(hdc, posX - circleR, posY - circleR, posX + circleR, posY + circleR);

    POINT verts[50]; // array of vertices coordinates

    {
        float newX = posX;
        float newY = posY;
        float alpha = 2 * PI / (power - 1);

        int i = 1;

        verts[0].x = posX;
        verts[0].y = posY;

        for (float angle = 0; i < power; angle += alpha) {
            float newX = posX + circleR * cos(angle);
            float newY = posY + circleR * sin(angle);
            verts[i].x = newX;
            verts[i].y = newY;
            i++;
        };
    }

    {
        SelectObject(hdc, pen2);

        POINT center;
        center.x = posX;
        center.y = posY;

        for (int i = 0; i < power; i++) {
            for (int j = 0; j < power; j++) {
                POINT from = verts[i];
                POINT to = verts[j];
                if (matrix[i][j] == 1) {
                    float alpha = atan2(to.y - from.y, to.x - from.x);
                    if (i == j) {
                        float alpha2 = atan2(to.y - center.y, to.x - center.x);
                        float distance = sqrt(pow((center.x - from.x), 2) + pow((center.y - from.y), 2));

                        POINT loop;
                        loop.x = center.x + (distance + verticeRadius) * cos(alpha2);
                        loop.y = center.y + (distance + verticeRadius) * sin(alpha2);
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
                        POINT move; // ñìåùåíèå îòíîñèòåëüíî öåíòðà âåðøèíû 
                        move.x = (verticeRadius / 2) * cos(PI / 2 - alpha);
                        move.y = (verticeRadius / 2) * sin(PI / 2 - alpha);
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

    SelectObject(hdc, pen1);

    for (int i = 0; i < power; i++) {
        char vertName[3];
        snprintf(vertName, 3, "%d", i + 1);

        Ellipse(hdc, verts[i].x - verticeRadius, verts[i].y - verticeRadius, verts[i].x + verticeRadius, verts[i].y + verticeRadius);
        TextOutA(hdc, verts[i].x - verticeRadius + 6, verts[i].y - verticeRadius / 2, vertName, i + 1 < 10 ? 1 : 2);
    }
}

void drawNonOrientedGraph(int posX, int posY, HDC hdc, HPEN pen1, HPEN pen2, int** matrix, int power)
{
    SelectObject(hdc, pen2);

    // draw circles
    HPEN dashPen = CreatePen(PS_DASH, 1, RGB(20, 20, 5));
    SelectObject(hdc, dashPen);
    Ellipse(hdc, posX - circleR, posY - circleR, posX + circleR, posY + circleR);

    POINT verts[50]; // array of vertices coordinates

    {
        float newX = posX;
        float newY = posY;
        float alpha = 2 * PI / (power - 1);

        int i = 1;

        verts[0].x = posX;
        verts[0].y = posY;

        for (float angle = 0; i < power; angle += alpha) {
            float newX = posX + circleR * cos(angle);
            float newY = posY + circleR * sin(angle);
            verts[i].x = newX;
            verts[i].y = newY;
            i++;
        };
    }

    POINT center;
    center.x = posX;
    center.y = posY;

    for (int i = 0; i < power; i++) {
        for (int j = 0; j < power; j++) {
            SelectObject(hdc, pen2);
            POINT from = verts[i];
            POINT to = verts[j];
            if (matrix[i][j] == 1 && to.x >= from.x) {
                if (i == j) {
                    float alpha2 = atan2(to.y - center.y, to.x - center.x);
                    float distance2 = sqrt(pow((to.x - center.x), 2) + pow((to.y - center.y), 2));

                    POINT loop;
                    loop.x = center.x + (distance2 + verticeRadius) * cos(alpha2);
                    loop.y = center.y + (distance2 + verticeRadius) * sin(alpha2);
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
                    LineTo(hdc, to.x, to.y); // ðèñóåì ïðÿìóþ ëèíèþ
                }

            }
        }
    }

    SelectObject(hdc, pen1);

    for (int i = 0; i < power; i++) {
        char vertName[3];
        snprintf(vertName, 3, "%d", i + 1);

        Ellipse(hdc, verts[i].x - verticeRadius, verts[i].y - verticeRadius, verts[i].x + verticeRadius, verts[i].y + verticeRadius);
        TextOutA(hdc, verts[i].x - verticeRadius + 6, verts[i].y - verticeRadius / 2, vertName, i + 1 < 10 ? 1 : 2);
    }
}
