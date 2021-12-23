#pragma once
#include "Rect_Shape.h"
#include "Line_Shape.h"

class CubeShape : public RectShape, public LineShape {
public:
	void Show(HDC, bool isDash);
	Shape* Copy();
	int Popup();
	std::string GetName();
};