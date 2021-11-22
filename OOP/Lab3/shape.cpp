#include "framework.h"
#include "shape.h"

static COLORREF grey = RGB(192, 192, 192);
static COLORREF black = RGB(0, 0, 0);

void Shape::Set(long x1, long y1, long x2, long y2) {
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void PointShape::Show(HDC hdc) {
	SetPixel(hdc, xs1, ys1, black);
}


void LineShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;

	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}


void RectShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;

	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs1, ys2);
	LineTo(hdc, xs2, ys2);
	LineTo(hdc, xs2, ys1);
	LineTo(hdc, xs1, ys1);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void EllipseShape::Show(HDC hdc) {
	HBRUSH hBrush, hBrushOld;

	hBrush = CreateSolidBrush(grey);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	SelectObject(hdc, hBrush);
	Ellipse(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
};
