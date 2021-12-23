#include "framework.h"
#include "Point_Shape.h"


void PointShape::Show(HDC hdc, bool isDash) {
	SetPixel(hdc, xs1, ys1, color);
}

Shape* PointShape::Copy() {
	return new PointShape();
}

int PointShape::Popup() {
	return 0;
}

std::string PointShape::GetName() {
	return "  Точка";
}