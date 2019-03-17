#include "AlarmLib.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnClickListener(HINSTANCE Instance, HWND hWnd, int type);

HINSTANCE gInstance;
const char *lpszClassN = "Park Alarm";
int FocusWnd = 0;
bool bAddMenu = false;
bool bDeleteMenu = false;
ALARM *HeadNode = NULL;
TIME tSelectedTime = { 0, };	// For redraw.

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Msg;
	WNDCLASS WndClass;
	gInstance = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClassN;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClassN, "", WS_THICKFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Msg, 0, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	int x, y;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_CREATE:
		MoveWindow(hWnd, 0, 0, 300, 150, TRUE);
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 500;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 700;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 500;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 700;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		PrintMainDisplay(gInstance, hWnd, hdc, &ps);
		if (bAddMenu) AppearAddMenu(gInstance, hWnd, hdc, tSelectedTime, &FocusWnd);
		if (bDeleteMenu);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		UpdateSelectedButton(gInstance, hWnd, CheckingMousePos(x, y, FocusWnd, false), &FocusWnd);
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		OnClickListener(gInstance, hWnd, CheckingMousePos(x, y, FocusWnd, true));
		SendMessage(hWnd, WM_MOUSEMOVE, 0, 0);

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void OnClickListener(HINSTANCE Instance, HWND hWnd, int type) {
	static int OldHourType = 0;
	static int OldMinuteType = 0;

	if (FocusWnd == 0) {
		switch (type) {
		case 1:
			bAddMenu = true;
			InvalidateRect(hWnd, NULL, false);
			break;

		case 2:
			MessageBox(hWnd, "Click Modify button!!", "From. Park Alarm", MB_OK);
			break;

		case 3:
			MessageBox(hWnd, "Click Delete button!!", "From. Park Alarm", MB_OK);
			break;

		case 4:
			MessageBox(hWnd, "Click Copy button!!", "From. Park Alarm", MB_OK);
			break;

		}
	} else if (FocusWnd == 1) {
		switch (type) {
		case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31:
		case 32: case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40: case 41: case 42: case 43:
			PrintSelectedButton(Instance, hWnd, OldHourType, &FocusWnd, false);
			PrintSelectedButton(Instance, hWnd, type, &FocusWnd, true);
			OldHourType = type;
			tSelectedTime.Hou = type;
			break;

		case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57: case 58: case 59: case 60: case 61:
		case 62: case 63: case 64: case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73:
		case 74: case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84: case 85:
		case 86: case 87: case 88: case 89: case 90: case 91: case 92: case 93: case 94: case 95: case 96: case 97:
		case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109:
			PrintSelectedButton(Instance, hWnd, OldMinuteType, &FocusWnd, false);
			PrintSelectedButton(Instance, hWnd, type, &FocusWnd, true);
			OldMinuteType = type;
			tSelectedTime.Min = type;
			break;
		}
	}
}