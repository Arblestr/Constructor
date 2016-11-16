#include "stdafx.h"
#include "Interface.h"

HWND Inter::hWnd;
HINSTANCE Inter::hInst;

Inter::Inter()
{
}
Inter::~Inter()
{
}
Inter::Inter(HWND hWnd, HINSTANCE hInst)
{
	this->hWnd = hWnd;
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
		this->hWnd, (HMENU)this->Id, this->hInst, NULL);
}
Button::~Button()
{
	//MessageBox(this->hWnd, L"dd", L"dddd", MB_OK);
	//DestroyWindow(GetDlgItem(this->hWnd, this->Id));
}


Label::Label()
{
}
Label::Label(WCHAR* Text, int X, int Y, int Height, int Width)
{
	CreateWindowW(L"static", Text,
		WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE,
		X, Y, Width, Height,
		this->hWnd, NULL, this->hInst, NULL);
}
Label::~Label()
{
}


Edit::Edit()
{
}
Edit::Edit(WCHAR* Text, int X, int Y, int Height, int Width, int Id)
{
	this->Id = Id;

	CreateWindowEx(WS_EX_WINDOWEDGE, L"edit", Text,
		WS_CHILD | WS_VISIBLE | WS_BORDER ,
		X, Y, Width, Height,
		this->hWnd, (HMENU)this->Id, NULL, NULL);
}
Edit::~Edit()
{
}

Scene::Scene()
{
	this->hWnd = NULL;
	this->hdc = NULL;
	this->hdcMem = NULL;

	this->X = 0;
	this->Y = 0;
	this->width = 0;
	this->height = 0;

	this->InitBitmap();

	//this->bricks = nullptr;
	this->pixels = nullptr;
	//this->render = nullptr;
	//this->cam = nullptr;
}

Scene::Scene(HWND hWnd, int x, int y, int width, int height)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	this->hdcMem = CreateCompatibleDC(this->hdc);

	this->X = x;
	this->Y = y;
	this->width = width;
	this->height = height;

	//this->model = model;

	this->pixels = new unsigned long[this->width * this->height];
	if (!this->pixels)
	{
		//throw AllocationMemoryError();
	}

	this->InitBitmap();

	/*this->bricks = new Composite;
	if (!this->bricks)
	{
		delete this->pixels;
		this->pixels = nullptr;

		throw AllocationMemoryError();
	}

	this->render = new Render(pixels, this->height, this->width);
	if (!this->render)
	{
		delete this->pixels;
		delete this->bricks;
		this->pixels = nullptr;
		this->bricks = nullptr;

		throw AllocationMemoryError();
	}

	this->cam = new Camera;
	if (!this->cam)
	{
		delete this->pixels;
		delete this->bricks;
		delete this->render;
		this->pixels = nullptr;
		this->bricks = nullptr;
		this->render = nullptr;

		throw AllocationMemoryError();
	}*/
}

Scene::~Scene()
{
	//delete this->pixels;
	//delete this->bricks;
	//delete this->render;
	//delete this->cam;
	//this->pixels = nullptr;
	//this->bricks = nullptr;
	//this->render = nullptr;
	//this->cam = nullptr;
}

void Scene::InitBitmap()
{
	this->sBmInfo.bmiHeader.biSize = sizeof(BITMAPINFO);
	this->sBmInfo.bmiHeader.biWidth = this->width;
	this->sBmInfo.bmiHeader.biHeight = -this->height;
	this->sBmInfo.bmiHeader.biPlanes = 1;
	this->sBmInfo.bmiHeader.biBitCount = 32;
	this->sBmInfo.bmiHeader.biCompression = BI_RGB;
	this->sBmInfo.bmiHeader.biSizeImage = 0;
	this->sBmInfo.bmiHeader.biXPelsPerMeter = 0;
	this->sBmInfo.bmiHeader.biYPelsPerMeter = 0;
	this->sBmInfo.bmiHeader.biClrUsed = 0;
	this->sBmInfo.bmiHeader.biClrImportant = 0;

	this->sBmInfo.bmiColors[0].rgbBlue = 0;
	this->sBmInfo.bmiColors[0].rgbGreen = 0;
	this->sBmInfo.bmiColors[0].rgbRed = 0;
	this->sBmInfo.bmiColors[0].rgbReserved = 0;

	this->sBmp = CreateDIBSection(
		this->hdc, &this->sBmInfo, DIB_RGB_COLORS, (void**)&pixels, NULL, 0
	);
}

void Scene::DrawScene()
{
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
			this->pixels[j*this->width + i] = 0xffff00;

	for (int i = 0; i < MyModels.size(); i++)
	{
		this->MyModels[i].PaintModel(this->pixels);
		this->MyModels[i].FillModel(this->pixels);
	}
	

	//Brick* brick = bricks->objects[0]; // temporary
	//this->render->run(brick, this->cam);

	SelectObject(this->hdcMem, this->sBmp);
	BitBlt(this->hdc, X, Y, this->width, this->height, this->hdcMem, 0, 0, SRCCOPY);
}

void Scene::AddModel(Model MyModel)
{
	for (int i = 0; i < MyModel.NodesNum; i++)
	{
		MyModel.Nodes[i].X = MyModel.Nodes[i].X * 100 + this->width / 2 - MyModel.Center.X * 100;
		MyModel.Nodes[i].Y = MyModel.Nodes[i].Y * 100 + this->height / 2 - MyModel.Center.Y * 100;
		MyModel.Nodes[i].Z = MyModel.Nodes[i].Z * 100 - MyModel.Center.Z * 100;
	}

	MyModel.Center.X = this->width / 2;
	MyModel.Center.Y = this->height / 2;
	MyModel.Center.Z = 0;

	this->MyModels.push_back(MyModel);
}

void Scene::Clear()
{
	this->MyModels.clear();
}

/*Composite* Scene::getBricks()
{
	return this->bricks;
}*/