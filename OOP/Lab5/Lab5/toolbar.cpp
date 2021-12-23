#include "framework.h"
#include "toolbar.h"
//#include "toolbar_resource.h"
#include "Lab5.h"

HWND hwndToolBar = NULL;
bool point, line, rect, ellipse, OLineO, cube = 0;
int whatPressed = ID_TOOL_POINT;

void Toolbar::OnCreate(HWND hWnd, HINSTANCE hInst) {
	TBBUTTON tbb[6];

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

	tbb[4].iBitmap = 4;
	tbb[4].fsState = TBSTATE_ENABLED;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = ID_TOOL_CUBE;

	tbb[5].iBitmap = 5;
	tbb[5].fsState = TBSTATE_ENABLED;
	tbb[5].fsStyle = TBSTYLE_BUTTON;
	tbb[5].idCommand = ID_TOOL_OLINEO;

	hwndToolBar = CreateToolbarEx(hWnd,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
		IDC_TOOLBAR,
		6,
		hInst,
		IDB_BITMAP_TOOL,
		tbb,
		6,
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
	offPressed(ID_TOOL_POINT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, 1);
}

void Toolbar::OnLinePressed() {
	offPressed(ID_TOOL_LINE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, 1);
}

void Toolbar::OnRectPressed() {
	offPressed(ID_TOOL_RECT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, 1);
}

void Toolbar::OnEllipsePressed() {
	offPressed(ID_TOOL_ELLIPSE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, 1);
}

void Toolbar::OnCubePressed() {
	offPressed(ID_TOOL_CUBE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_CUBE, 1);
}

void Toolbar::OnOLineOPressed() {
	offPressed(ID_TOOL_OLINEO);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_OLINEO, 1);
}

void Toolbar::OnNotify(HWND hWnd, LPARAM lParams) {
	LPNMHDR pnhm = (LPNMHDR)lParams;
	LPSTR pText;

	if (pnhm->code == TTN_NEEDTEXT)
	{
		LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParams;
		switch (lpttt->hdr.idFrom)
		{
		case ID_TOOL_POINT:
			pText = (LPSTR)"Режим вводу точок";
			break;
		case ID_TOOL_LINE:
			pText = (LPSTR)"Режим вводу ліній";
			break;
		case ID_TOOL_RECT:
			pText = (LPSTR)"Режим вводу прямокутників";
			break;
		case ID_TOOL_ELLIPSE:
			pText = (LPSTR)"Режим вводу еліпсів";
			break;
		case ID_TOOL_CUBE:
			pText = (LPSTR)"Режим вводу кубів";
			break;
		case ID_TOOL_OLINEO:
			pText = (LPSTR)"Режим вводу ліній з кружечками";
			break;
		default: pText = (LPSTR)"Невідомий режим вводу";
		}
		lstrcpy(lpttt->szText, pText);
	}
}
