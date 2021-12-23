#pragma once
#include "framework.h"
#include <string>


//extern COLORREF grey = RGB(192, 192, 192);
//extern COLORREF black = RGB(0, 0, 0);
//extern COLORREF red = RGB(255, 0, 0);

class Shape {
protected:
	long xs1, ys1, xs2, ys2;
public:
	COLORREF color;
	void SetColor(COLORREF);
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC, bool) = 0;
	virtual Shape* Copy() = 0;
	virtual int Popup() = 0;
	virtual std::string GetName() = 0;
};
