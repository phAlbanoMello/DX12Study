#include <windows.h>

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

WCHAR WindowClass[MAX_NAME_STRING];
WCHAR WindowTitle[MAX_NAME_STRING];

INT WindowWidth;
INT WindowHeight;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) 
{
	//Init global variables
	wcscpy_s(WindowClass, TEXT("DX12Study 1"));
	wcscpy_s(WindowTitle, TEXT("First A Window"));
	WindowWidth = 1366;
	WindowHeight = 768;

	//Create window class
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX); //Size of class (initialization)
	windowClass.style = CS_HREDRAW | CS_VREDRAW; //HORIZONTAL REDRAW AND VERTICAL REDRAW
	
	//These two variables are used to add extra memory at runtime. Not needed now.
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;

	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	windowClass.hIconSm = LoadIcon(0, IDI_APPLICATION);

	windowClass.lpszClassName = WindowClass;

	windowClass.lpszMenuName = nullptr;

	windowClass.hInstance = HInstance();

	windowClass.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&windowClass);

	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);

	if (!hWnd)
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);


	MSG msg = { 0 };
	while (msg.message != WM_QUIT) 
	{
		if (PeekMessage(&msg, 0,0,0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return 0;

}
