#include "framework.h"
#include "Rect_Shape.h"

static COLORREF black = RGB(0, 0, 0);

void RectShape::Show(HDC hdc, bool isDash) {
	HPEN hPen, hPenOld;

	if (isDash) {
		hPen = CreatePen(PS_DOT, 1, black);
		hPenOld = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, xs1, ys1, NULL);
		LineTo(hdc, xs1, ys2);
		LineTo(hdc, xs2, ys2);
		LineTo(hdc, xs2, ys1);
		LineTo(hdc, xs1, ys1);
	}
	else {
		hPen = CreatePen(PS_SOLID, 1, color);
		hPenOld = (HPEN)SelectObject(hdc, hPen);

		MoveToEx(hdc, xs1, ys1, NULL);
		LineTo(hdc, xs1, ys2);
		LineTo(hdc, xs2, ys2);
		LineTo(hdc, xs2, ys1);
		LineTo(hdc, xs1, ys1);
	}

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* RectShape::Copy() {
	return new RectShape();
}

int RectShape::Popup() {
	return 2;
}

std::string RectShape::GetName() {
	return "  Прямокутник";
}