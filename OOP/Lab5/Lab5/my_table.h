#pragma once
#include "resource1.h"
using namespace std;

class MyTable {
public:
	void Add(HWND, std::string);
	void SetCb(void(HWND));
	void SetCbDel(void(int));
	void SetDraw(void(HWND));
	static void(*Select) (HWND);
	static void(*DeleteObj) (int);
	static void(*Draw) (HWND);
	static void Delete(HWND, int);
};

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);