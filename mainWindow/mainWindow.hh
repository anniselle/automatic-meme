#ifndef AM_MAIN_WINDOW_HH
#define AM_MAIN_WINDOW_HH

#include <windows.h>
#include <tchar.h>

class mainWindow
{
public:
	static mainWindow* Instance();
	static void DropInstance();
	~mainWindow();
	int MainFunction(_In_ HINSTANCE hInstance,  
		_In_ HINSTANCE hPrevInstance,  
		_In_ LPSTR     lpCmdLine,  
		_In_ int       nCmdShow);
	LRESULT EventHandler(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);
private:
	mainWindow();
	mainWindow(mainWindow&);
	
	static mainWindow *_instance;
	static bool _dropping;
	HINSTANCE _hInst;
	TCHAR _szWindowClass[16];
	TCHAR _szTitle[32];
};

#endif