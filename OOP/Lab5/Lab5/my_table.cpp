#include "framework.h"
#include "my_table.h"
#include <fstream>
#include <string>

using namespace std;

void (*MyTable::Select)(HWND) = NULL;
void (*MyTable::DeleteObj)(int) = NULL;
void (*MyTable::Draw)(HWND) = NULL;

void MyTable::Add(HWND hWndDlg, string str) {
	ofstream fout;
	string path = "./Objects.txt";
	fout.open(path, ofstream::app);
	if (!fout.is_open()) {
		throw new exception("can't open file");
	}
	else {
		fout << str << "\n";
	}
	fout.close();

	SendDlgItemMessage(hWndDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)str.c_str());
}

void MyTable::SetCb(void cb(HWND)) {
	MyTable::Select = cb;
}

void MyTable::SetCbDel(void cb(int)) {
	MyTable::DeleteObj = cb;
}

void MyTable::SetDraw(void cb(HWND)) {
	MyTable::Draw = cb;
}

void MyTable::Delete(HWND hWndDlg, int indx) {
	SendDlgItemMessage(hWndDlg, IDC_LIST, LB_DELETESTRING, indx, 0);
	MyTable::DeleteObj(indx);
	ofstream fout;
	string path = "./Objects.txt";
	char str[200];
	int id = 0;
	int c = SendDlgItemMessage(hWndDlg, IDC_LIST, LB_GETCOUNT, 0, 0);
	fout.open(path);
	if (!fout.is_open()) {
		throw new exception("can't open file");
	}
	else {
		for (int i = 0; i < c; i++) {
			SendDlgItemMessage(hWndDlg, IDC_LIST, LB_GETTEXT, i, (LPARAM)str);
			fout << str << "\n";
		}
	}
	fout.close();
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	int wmId = LOWORD(wParam);
	int indx;
	string path = "./Objects.txt";
	ifstream fin;

	if (LOWORD(wParam) == IDC_LIST && HIWORD(wParam) == LBN_SELCHANGE) MyTable::Select(GetParent(hDlg));

	switch (message) {
	case WM_INITDIALOG:
		fin.open(path);
		if (!fin.is_open()) {
			throw new exception("can't open file");
		}
		else {
			string str;
			while (!fin.eof()) {
				str = "";
				getline(fin, str);
				if (str != "") SendDlgItemMessage(hDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)str.c_str());
			}
		}
		fin.close();
		return (INT_PTR)TRUE;
		break;
	case WM_COMMAND:
		int wmId = LOWORD(wParam);
		switch (wmId) {
		case IDB_DRAW:
			MyTable::Draw(GetParent(hDlg));
			break;
		case IDCANCEL:
		case IDB_EXIT:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		case IDB_DELETE:
			indx = SendDlgItemMessage(hDlg, IDC_LIST, LB_GETCURSEL, 0, 0);
			if (indx > 0)
				MyTable::Delete(hDlg, indx);
			return (INT_PTR)TRUE;
			break;
		}
	}
	return (INT_PTR)FALSE;
}
