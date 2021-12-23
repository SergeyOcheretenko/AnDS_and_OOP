#include "framework.h"
#include "my_editor.h"

int c = 0;
static bool isPressed = false;
static const int MY_SHAPE_ARRAY_SIZE = 118;
Shape** pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE];

MyEditor::~MyEditor() {
	for (int i = 0; i < c; i++) delete pcshape[i];
	delete pcshape;
}

void MyEditor::Start(Shape* shape) {
	pcshape[c] = shape;
}

void MyEditor::OnLBdown(HWND hWnd) {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
	isPressed = true;
}

void MyEditor::OnLBup(HWND hWnd) {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;
	pcshape[c]->Set(x1, y1, x2, y2);

	c++;
	InvalidateRect(hWnd, NULL, TRUE);
	pcshape[c] = pcshape[c - 1]->Copy();
}

void MyEditor::OnMouseMove(HWND hWnd) {
	if (isPressed) {
		POINT pt;
		HDC hdc = GetDC(hWnd);

		SetROP2(hdc, R2_NOTXORPEN);

		MoveToEx(hdc, x1, y1, NULL);
		pcshape[c]->Set(x1, y1, x2, y2);
		pcshape[c]->Show(hdc, 1);

		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);

		x2 = pt.x;
		y2 = pt.y;

		MoveToEx(hdc, x1, y1, NULL);
		pcshape[c]->Set(x1, y1, x2, y2);
		pcshape[c]->Show(hdc, 1);

		ReleaseDC(hWnd, hdc);
	}
}

void MyEditor::OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < c; i++) {
		if (pcshape[i]) pcshape[i]->Show(hdc, 0);
	}
	EndPaint(hWnd, &ps);
}

void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_OLINEO, MF_UNCHECKED);
		int id = pcshape[c]->Popup();
		switch (id) {
		case 0:
			CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
			break;
		case 1:
			CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
			break;
		case 2:
			CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_CHECKED);
			break;
		case 3:
			CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
			break;
		case 4:
			CheckMenuItem(hSubMenu, IDM_CUBE, MF_CHECKED);
			break;
		case 5:
			CheckMenuItem(hSubMenu, IDM_OLINEO, MF_CHECKED);
			break;
		}
	}
}

std::string MyEditor::GetString() {
	std::string str = pcshape[c]->GetName() + "\t" + "\t"
		+ std::to_string(x1) + "\t"
		+ std::to_string(y1) + "\t"
		+ std::to_string(x2) + "\t"
		+ std::to_string(y2);
	return str;
}