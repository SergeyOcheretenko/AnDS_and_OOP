#pragma once
#include "shape_editor_resource.h"
#include "editor.h"
#include "shape.h"

class ShapeEditor : public Editor
{
protected:
	int x1, y1, x2, y2;
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class ShapeObjectsEditor 
{
private:
	ShapeEditor* pse;
public:
	ShapeObjectsEditor();
	~ShapeObjectsEditor();
	void StartPointEditor();
	void StartLineEditor();
	void StartRectEditor();
	void StartEllipseEditor();
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class PointEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class LineEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class RectEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class EllipseEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};
