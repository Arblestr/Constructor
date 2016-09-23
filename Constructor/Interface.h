#pragma once

#include "stdafx.h"

class Inter
{
public:
	Inter();
	Inter(HWND hWnd, HINSTANCE hInst);
	~Inter();
protected:
	static HWND hWnd;
	static HINSTANCE hInst;
};

class Button : public Inter
{
private:
	int Id;
public:
	Button();
	Button(WCHAR* Text, int X, int Y, int Height, int Width, int Id);
	~Button();
};
