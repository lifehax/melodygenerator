#include "stdafx.h"
#include "AboutBox.h"

AboutBox::AboutBox(MainWindow * mainWindow) {
	this->mainWindow = mainWindow;
}

INT_PTR CALLBACK AboutBox::proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AboutBox::Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG:
		SetProp(hDlg, L"about_box_object", (HANDLE)lParam);
		break;

	case WM_NCDESTROY:
		RemoveProp(hDlg, L"about_box_object");
		break;
	}

	AboutBox * box = (AboutBox *)GetProp(hDlg, L"about_box_object");
	return box ? box->proc(hDlg, message, wParam, lParam) : (INT_PTR)FALSE;
}
