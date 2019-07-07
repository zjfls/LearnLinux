#include <iostream>
#include <windows.h>
#include <cassert>


#define MAX_LOADSTRING 100
HINSTANCE hInst;
const char* szTitle = "my_win";
const char* szWindowClass = "my_win_class";


ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE,int);
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
INT_PTR CALLBACK About(HWND,UINT,WPARAM,LPARAM);

int GetNCmdShow() {
		// It's possible that the process was started with STARTUPINFOW that could have a value for
		// show window other than SW_SHOWDEFAULT. If so we retrieve and return that value. Otherwise
		// we return SW_SHOWDEFAULT.
		::STARTUPINFOW startupInfo;
		::GetStartupInfoW(&startupInfo);
		if ((startupInfo.dwFlags & STARTF_USESHOWWINDOW) != 0) {
			return startupInfo.wShowWindow;
		}
		return SW_SHOWDEFAULT;
}
int main(int argc,char** argv)
{
    //MessageBox( 0, "Press OK", "Hi", MB_SETFOREGROUND );
    HINSTANCE hInstance = static_cast<HINSTANCE>(::GetModuleHandle(nullptr));
    HINSTANCE hPrevInstance = static_cast<HINSTANCE>(nullptr);
    //LPSTR lpCmdLine = GetLPCmdLine();
    int nCmdShow = GetNCmdShow();

    assert(hInstance != nullptr);
    assert(hPrevInstance == nullptr);
   // assert(lpCmdLine != nullptr);


    FreeConsole();

    UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;
    HACCEL hAccelTable;

    MyRegisterClass(hInstance);

    if(!InitInstance(hInstance,nCmdShow))
    {
        return FALSE;
    }

    //hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAUNCHWIN32WINDOWFROMCONSOLE));
    while(GetMessage(&msg,NULL,0,0))
    {
        if(!TranslateAccelerator(msg.hwnd,NULL,&msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);       
        }
    }

    return (int)msg.wParam;


    std::cout<<"hello world"<<std::endl;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAUNCHWIN32WINDOWFROMCONSOLE));
	wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_LAUNCHWIN32WINDOWFROMCONSOLE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		// case IDM_ABOUT:
		// 	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		// 	break;
		//case IDM_EXIT:
		//	DestroyWindow(hWnd);
		//	break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		{
			RECT clientRect;
			GetClientRect(hWnd, &clientRect);
			// HGDIOBJ objects obtained from GetStockObject do not need to be deleted with DeleteObject as per the documentation: https://msdn.microsoft.com/en-us/library/dd144925(v=vs.85).aspx
			HGDIOBJ whiteBrushGDIObj = GetStockObject(WHITE_BRUSH);
			if (whiteBrushGDIObj == nullptr || GetObjectType(whiteBrushGDIObj) != OBJ_BRUSH) {
				PostQuitMessage(1);
			}
			else {
				HBRUSH whiteBrush = static_cast<HBRUSH>(whiteBrushGDIObj);
				FillRect(hdc, &clientRect, whiteBrush);
				COLORREF blackTextColor = 0x00000000;
				if (SetTextColor(hdc, blackTextColor) == CLR_INVALID) {
					PostQuitMessage(1);
				}
				else {
					const char helloWorldString[] = "hello world windows";
					DrawText(hdc, helloWorldString, ARRAYSIZE(helloWorldString) - 1, &clientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
				}
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
