#pragma once
class Shape {
protected:
	long xs1, ys1, xs2, ys2;
public:
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC) = 0;
};

class PointShape : public Shape
{
	void Show(HDC);
};

class LineShape : public Shape
{
	void Show(HDC);
};

class RectShape : public Shape
{
	void Show(HDC);
};

class EllipseShape : public Shape
{
	void Show(HDC);
};
