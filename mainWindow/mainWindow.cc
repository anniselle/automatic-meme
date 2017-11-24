// C headers
#include <stdlib.h> 
#include <string.h>
#include <stdint.h>

// Local headers
#include "mainWindow.hh"

bool mainWindow::_dropping = false;
mainWindow *mainWindow::_instance = NULL;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	mainWindow* main = mainWindow::Instance();
	return main->EventHandler(hWnd, message, wParam, lParam);
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow)  
{
	int ret = 0;
	
	mainWindow* main = mainWindow::Instance();
	
	ret = main->MainFunction(hInstance, hPrevInstance,
			lpCmdLine, nCmdShow);
	
	 mainWindow::DropInstance();
	
	return ret;
}

mainWindow::mainWindow() :
	_hInst(),
	_szWindowClass(_T("win32app")),
	_szTitle(_T("mainWindow"))
{
	// empty
}

mainWindow::~mainWindow()
{
	// empty
}

mainWindow* mainWindow::Instance()
{
	if (_instance == NULL)
	{
		_instance = new mainWindow();
		_dropping = false;
	}
	
	return _instance;
}
void mainWindow::DropInstance()
{
	if (_instance != NULL && !_dropping)
	{
		_dropping = true;
		delete _instance;
	}
}

int mainWindow::MainFunction(_In_ HINSTANCE hInstance,  
		_In_ HINSTANCE hPrevInstance,  
		_In_ LPSTR     lpCmdLine,  
		_In_ int       nCmdShow)
{
	WNDCLASSEX wcex;
 
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = _szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Win32 Guided Tour"),
            0);

        return 1;
    }

    _hInst = hInstance;

    HWND hWnd = CreateWindow(
        _szWindowClass,
        _szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 100,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Win32 Guided Tour"),
            0);

        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT mainWindow::EventHandler(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, World!");

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 5, 5,
            greeting, strlen(greeting));

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}