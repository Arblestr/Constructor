#include "stdafx.h"
#include "Interface.h"

HWND Inter::hwnd;
HINSTANCE Inter::hInst;

	Inter::Inter() 
	{
	}
	Inter::~Inter() 
	{
	}
	Inter::Inter(HWND hWnd, HINSTANCE hInst)
	{
		this->hwnd = hWnd;
		this->hInst = hInst;
	}


	Button::Button()
	{
	}
	Button::Button(WCHAR* Text, int X, int Y, int Height, int Width, int Id)
	{
		this->Id = Id;
		CreateWindowW(L"BUTTON", Text,
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			X, Y, Width, Height,
			this->hwnd, (HMENU)this->Id, this->hInst, NULL);
	}
	Button::~Button()
	{
		DestroyWindow(GetDlgItem(this->hwnd, this->Id));
	}