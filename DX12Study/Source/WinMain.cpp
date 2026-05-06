#include "pch.h"

//Globals --------------------------------------------
#pragma region

WCHAR WindowClass[MAX_NAME_STRING];
WCHAR WindowTitle[MAX_NAME_STRING];
INT WindowWidth;
INT WindowHeight;
HICON hIcon;

#pragma endregion
// --------------------------------------------------
//Pre-Declarations----------------------------
#pragma region

VOID InitializeVariables();
VOID InitializeWindow();
VOID CreateWindowClass();
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
VOID MessageLoop();
#pragma endregion
//--------------------------------------------

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) 
{
	InitializeVariables();
	CreateWindowClass();
	InitializeWindow();
	MessageLoop();

	return 0;

}
//Functions------------------------------------
#pragma region

VOID InitializeVariables() {
	LoadString(HInstance(), IDS_PERGAMENAME, WindowTitle, MAX_NAME_STRING);
	LoadString(HInstance(), IDS_WINDOWCLASS, WindowClass, MAX_NAME_STRING);

	WindowWidth = 1366;
	WindowHeight = 768;

	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));
}

VOID CreateWindowClass() {
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX); //Size of class (initialization)
	windowClass.style = CS_HREDRAW | CS_VREDRAW; //HORIZONTAL REDRAW AND VERTICAL REDRAW

	//These two variables are used to add extra memory at runtime. Not needed now.
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;

	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	windowClass.hIcon = hIcon;
	windowClass.hIconSm = hIcon;

	windowClass.lpszClassName = WindowClass;

	windowClass.lpszMenuName = nullptr;

	windowClass.hInstance = HInstance();

	windowClass.lpfnWndProc = WindowProcess;

	RegisterClassEx(&windowClass);
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) {

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}

VOID MessageLoop() {
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
VOID InitializeWindow()
{
	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);

	if (!hWnd)
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(hWnd, SW_SHOW);
}

#pragma endregion
//---------------------------------------------
