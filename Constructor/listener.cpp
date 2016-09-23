#include "stdafx.h"
#include "listener.h"
#include "Interface.h"

// √лобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпл€р

//
//  ‘”Ќ ÷»я: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ќј«Ќј„≈Ќ»≈:  обрабатывает сообщени€ в главном окне.
//
//  WM_COMMAND Ч обработать меню приложени€
//  WM_PAINT Ч отрисовать главное окно
//  WM_DESTROY Ч отправить сообщение о выходе и вернутьс€
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		Inter MainInter(hWnd, hInst);
		Button ButRotateX(TEXT("RotateX"), 10, 10, 50, 100, Id_ButRotateX);
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// –азобрать выбор в меню:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ƒобавьте сюда любой код прорисовки, использующий HDC...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}