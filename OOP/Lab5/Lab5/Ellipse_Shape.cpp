#include "framework.h"
#include "Ellipse_Shape.h"

static COLORREF black = RGB(0, 0, 0);
static COLORREF grey = RGB(192, 192, 192);

void EllipseShape::Show(HDC hdc, bool isDash) {
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;

	if (isDash) {
		hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		hPenOld = (HPEN)SelectObject(hdc, hPen);
		Arc(hdc, xs1, ys1, xs2, ys2, 0, 0, 0, 0);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);
	}
	else {
		hBrush = CreateSolidBrush(grey);
		hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, xs1, ys1, xs2, ys2);
		SelectObject(hdc, hBrushOld);
		DeleteObject(hBrush);

		hPen = CreatePen(PS_SOLID, 1, color);
		hPenOld = (HPEN)SelectObject(hdc, hPen);
		Arc(hdc, xs1, ys1, xs2, ys2, 0, 0, 0, 0);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);
	}
};

Shape* EllipseShape::Copy() {
	return new EllipseShape();
}

int EllipseShape::Popup() {
	return 3;
}

std::string EllipseShape::GetName() {
	return "  Ελ³ορ";
}