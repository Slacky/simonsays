/*
 * main.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: Zach Knight
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>

static TCHAR szWindowClass[] = _T("simonsays");
static TCHAR szTitle[] = _T("Simon Says");
bool color[4] = { false, false, false, false };
bool simonsTurn = false;
HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = szWindowClass;

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Simon Says"),
			0);

		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		512, 334,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd) {
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Simon Says"),
			0);

		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	MSG msg;
	PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
    while(msg.message != WM_QUIT) {
        if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
            try{
                Sleep(50);
                if(simonsTurn) {

                }
            }
            catch(std::exception& e){
            /*    onError(e.what());
                close();*/
            	break;
            }
    }

	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	WORD x, y;
    HBRUSH hOldBrush, hNewBrush;

    x = LOWORD(lParam);
    y = HIWORD(lParam);

	switch (message) {
	case WM_LBUTTONUP:
		color[0] = false;
		color[1] = false;
		color[2] = false;
		color[3] = false;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		if(x >= 177 && x <= 257 && y >= 61 && y <= 140)
			color[0] = true;
		if(x >= 256 && x <= 335 && y >= 61 && y <= 141)
			color[1] = true;
		if(x >= 177 && x <= 257 && y >= 139 && y <= 219)
			color[2] = true;
		if(x >= 256 && x <= 335 && y >= 140 && y <= 219)
			color[3] = true;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if(color[0]) {
			hNewBrush = CreateSolidBrush(RGB(0, 255, 0));
        	hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
		}
		MoveToEx(hdc, 177, 61, NULL);
		Rectangle(hdc, 177, 61, 257, 140);
		hNewBrush = CreateSolidBrush(RGB(255, 255, 255));
        hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
		if(color[1]) {
			hNewBrush = CreateSolidBrush(RGB(0, 0, 255));
        	hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
		}
		MoveToEx(hdc, 256, 61, NULL);
		Rectangle(hdc, 256, 61, 335, 141);
		hNewBrush = CreateSolidBrush(RGB(255, 255, 255));
        hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
		if(color[2]) {
			hNewBrush = CreateSolidBrush(RGB(255, 0, 0));
        	hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
		}
		MoveToEx(hdc, 177, 139, NULL);
		Rectangle(hdc, 177, 139, 257, 219);
		hNewBrush = CreateSolidBrush(RGB(255, 255, 255));
        hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
		if(color[3]) {
			hNewBrush = CreateSolidBrush(RGB(255, 255, 0));
        	hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
		}
		MoveToEx(hdc, 256, 140, NULL);
		Rectangle(hdc, 256, 140, 335, 219);
		hNewBrush = CreateSolidBrush(RGB(255, 255, 255));
        hOldBrush = (HBRUSH) SelectObject(hdc, hNewBrush);
        TextOut(hdc, 200, 256, "Your turn...", 12);
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
