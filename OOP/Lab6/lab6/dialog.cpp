#include "framework.h"
#include "dialog.h"

static INT_PTR CALLBACK DialogCb(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	char n[10];
	char min[10];
	char max[10];
	HWND hWndDataCreator;
	COPYDATASTRUCT cds;
	HWND hWndL1;


	int wmId = LOWORD(wParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_DESTROY: {
		hWndL1 = FindWindow("LAB61", NULL);
		if (hWndL1) PostMessage(hWndL1, WM_DESTROY, (WPARAM)wParam, 0);
		break;
	}
	case WM_COMMAND:
		switch (wmId) {
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
			break;
		case IDB_COUNT:
			GetWindowText(GetDlgItem(hDlg, IDC_N), n, sizeof(n));
			GetWindowText(GetDlgItem(hDlg, IDC_MIN), min, sizeof(min));
			GetWindowText(GetDlgItem(hDlg, IDC_MAX), max, sizeof(max));
			if (n[0] == '\0' || min[0] == '\0' || max[0] == '\0') MessageBox(GetParent(hDlg), (LPCSTR)"Введіть дані", (LPCSTR)"Помика", MB_OK);
			else if (atoi(min) >= atoi(max) || atoi(min) > 200 || atoi(max) > 200 || atoi(n) > 12)  MessageBox(GetParent(hDlg), (LPCSTR)"Введіть коректні дані", (LPCSTR)"Помика", MB_OK);
			else {
				long params[3] = { atoi(n), atoi(min), atoi(max) };
				cds.dwData = 1;
				cds.cbData = sizeof(params);
				cds.lpData = params;
				hWndDataCreator = FindWindow("LAB61", NULL);
				if (hWndDataCreator == NULL) {
					WinExec("lab6.1.exe", SW_SHOW);
					hWndDataCreator = FindWindow("LAB61", NULL);
				}
				SendMessage(hWndDataCreator, WM_COPYDATA, (WPARAM)GetParent(hDlg), (LPARAM)&cds);
			}
			break;
		}
	}

	return (INT_PTR)FALSE;
}

int Dialog(HINSTANCE hInst, HWND hWnd) {
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_LAB6_DIALOG), hWnd, DialogCb);
}