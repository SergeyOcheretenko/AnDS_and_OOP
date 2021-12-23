#include "framework.h"
#include "OLineO_Shape.h"

void OLineOShape::Show(HDC hdc, bool isDash) {
	long x1, y1, x2, y2;
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	LineShape::Show(hdc, isDash);

	EllipseShape::Set(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	EllipseShape::Show(hdc, isDash);

	EllipseShape::Set(x2 + 10, y2 + 10, x2 - 10, y2 - 10);
	EllipseShape::Show(hdc, isDash);

	LineShape::Set(x1, y1, x2, y2);

}

Shape* OLineOShape::Copy() {
	return new OLineOShape();
}

int OLineOShape::Popup() {
	return 5;
}

std::string OLineOShape::GetName() {
	return "  Îë³í³ÿÎ";
}