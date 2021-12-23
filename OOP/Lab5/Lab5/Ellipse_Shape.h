#pragma once
#include "shape.h"

class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC, bool isDash);
	virtual Shape* Copy();
	int Popup();
	virtual std::string GetName();
};