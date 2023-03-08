#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

void AddControls(HWND);
std::string Calculator(WPARAM);

HWND hNum1;
HWND hNum2;
HWND hButtonPlus, hButtonMinus, hButtonMultiply, hButtonDivide;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}

		case WM_CREATE: {
			AddControls(hwnd);
			break;
		}

		case WM_COMMAND:{
			switch (wParam)
			{
			case 1:
				MessageBox(hwnd, Calculator(wParam).c_str(),"Result",MB_OK);
				break;
			case 2:
				MessageBox(hwnd, Calculator(wParam).c_str(),"Result",MB_OK);
				break;
			case 3:
				MessageBox(hwnd, Calculator(wParam).c_str(),"Result",MB_OK);
				break;
			case 4:
				MessageBox(hwnd, Calculator(wParam).c_str(),"Result",MB_OK);
				break;
			}
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); //set bg color

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = brush;
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

void AddControls(HWND hwnd)
{
	CreateWindowEx(
    0,                      // Extended style
    "Static",                 // Class name
    "Please input two numbers",                     // Text
    WS_CHILD | WS_VISIBLE | SS_CENTER, // Style
    10, 10, 200, 20,        // Position and size
    hwnd,                   // Parent window
    NULL,                   // Menu handle
    NULL,              // Instance handle
    NULL                    // Additional application data
	);

	hNum1 = CreateWindowEx(0,"EDIT","",WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,10, 40, 200, 20,hwnd,NULL,NULL,NULL);
	hNum2 = CreateWindowEx(0,"EDIT","",WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,10, 70, 200, 20,hwnd,NULL,NULL,NULL);

	hButtonPlus = CreateWindowEx(0,"BUTTON","+",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,60, 100, 20, 20,hwnd,(HMENU)1,NULL,NULL);
	hButtonMinus = CreateWindowEx(0,"BUTTON","-",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,90, 100, 20, 20,hwnd,(HMENU)2,NULL,NULL);
	hButtonMultiply = CreateWindowEx(0,"BUTTON","*",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,120, 100, 20, 20,hwnd,(HMENU)3,NULL,NULL);
	hButtonDivide = CreateWindowEx(0,"BUTTON","/",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,150, 100, 20, 20,hwnd,(HMENU)4,NULL,NULL);

}

std::string Calculator(WPARAM wParam)
{
	float result;
	char buffer[256];
	GetWindowText(hNum1,buffer,256);
	float x = atof(buffer);
	GetWindowText(hNum2,buffer,256);
	float y = atof(buffer);

	switch (wParam)
	{
	case 1:
		result = x + y;
		break;
	
	case 2:
		result = x - y;
		break;

	case 3:
		result = x * y;
		break;

	case 4:
		result = x / y;
		break;
	}
	std::string result_str = std::to_string(result);

	return result_str;
}