#include "framework.h"
#include "editor.h"

class ShapeEditor : public Editor
{
protected:
	int x1, y1, x2, y2;
public:
	void OnLBdown(HWND);
	void OnLBup(HWND, COLORREF, BOOL);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};
