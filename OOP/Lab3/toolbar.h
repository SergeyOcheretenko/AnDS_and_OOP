#pragma once
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

class Toolbar
{
public:
	void OnCreate(HWND, HINSTANCE);
	void OnSize(HWND);
	void OnPointPressed();
	void OnLinePressed();
	void OnRectPressed();
	void OnEllipsePressed();
	void OnNotify(HWND, LPARAM);
};
