#include "framework.h"
#include "toolbar.h"
#include "lab2.h"

HWND hwndToolBar = NULL;
bool point, line, rect, rectF, ellipse, ellipseF = 0;
int whatPressed = NULL;

void Toolbar::OnCreate(HWND hWnd, HINSTANCE hInst) {
	TBBUTTON tbb[4];

	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = 0;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_TOOL_POINT;

	tbb[1].iBitmap = 1;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_TOOL_LINE;

	tbb[2].iBitmap = 2;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_TOOL_RECT;

	tbb[3].iBitmap = 3;
	tbb[3].fsState = TBSTATE_ENABLED;
	tbb[3].fsStyle = TBSTYLE_BUTTON;
	tbb[3].idCommand = ID_TOOL_ELLIPSE;

	hwndToolBar = CreateToolbarEx(hWnd,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
		IDC_TOOLBAR,
		4,
		hInst,
		IDB_BITMAP_TOOL,
		tbb,
		4,
		24, 24, 24, 24,
		sizeof(TBBUTTON));
}

void Toolbar::OnSize(HWND hWnd) {
	RECT rc, rw;

	if (hwndToolBar) {
		GetClientRect(hWnd, &rc);
		GetWindowRect(hwndToolBar, &rw);
		MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
	}
}

static void offPressed(int id) {
	SendMessage(hwndToolBar, TB_PRESSBUTTON, whatPressed, 0);

	whatPressed = id;
}

void Toolbar::OnPointPressed() {
	point = !point;
	line = rect = rectF = ellipse = ellipseF = 0;
	offPressed(ID_TOOL_POINT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, point);
}

void Toolbar::OnLinePressed() {
	line = !line;
	point = rect = rectF = ellipse = ellipseF = 0;
	offPressed(ID_TOOL_LINE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, line);
}

void Toolbar::OnRectPressed() {
	rect = !rect;
	point = line = rectF = ellipse = ellipseF = 0;
	offPressed(ID_TOOL_RECT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, rect);
}

void Toolbar::OnEllipsePressed() {
	ellipse = !ellipse;
	point = line = rect = rectF = ellipseF = 0;
	offPressed(ID_TOOL_ELLIPSE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, ellipse);
}

void Toolbar::OnNotify(HWND hWnd, LPARAM lParams) {
	LPNMHDR pnhm = (LPNMHDR)lParams;
	LPCSTR pText;

	if (pnhm->code == TTN_NEEDTEXT)
	{
		LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParams;
		switch (lpttt->hdr.idFrom)
		{
		case ID_TOOL_POINT:
			pText = (LPCSTR)"Режим вводу точок";
			break;
		case ID_TOOL_LINE:
			pText = (LPCSTR)"Режим вводу ліній";
			break;
		case ID_TOOL_RECT:
			pText = (LPCSTR)"Режим вводу прямокутників";
			break;
		case ID_TOOL_ELLIPSE:
			pText = (LPCSTR)"Режим вводу еліпсів";
			break;
		default: pText = (LPCSTR)"Невідомий режим вводу";
		}
		lstrcpy(lpttt->szText, pText);
	}
}

