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
		WS_CHILD | WS_VISIBLE | WS_BORDER,
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
	this->pixels = nullptr;
}

Scene::Scene(HWND hWnd, int x, int y, int width, int height)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	this->hdcMem = CreateCompatibleDC(this->hdc);
	this->color = 0x0fffff;

	this->X = x;
	this->Y = y;
	this->width = width;
	this->height = height;

	this->pixels = new unsigned long[this->width * this->height];

	this->InitBitmap();

	Cvector position(0, 0, 100, 1);
	Cvector target(0, 0, 0, 1);

	this->cam = new Camera(position, target);

	this->PointOfLight.X = 0;
	this->PointOfLight.Y = 0;
	this->PointOfLight.Z = -50;

	this->zbuffer = new float[this->width * this->height];

}

Scene::~Scene()
{

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

void sunny(node light, float* zbuffer, unsigned long* pixels, int width, int height)
{
	//for (int x = -10; x <= 10; x++)
	//{
		//for (int y = -10; y <= 10; y++)
		//{
			if (light.X  < 0 || light.X  > width || light.Y  < 0 || light.Y  > height)
				return;
			int pix = (light.Y ) * width + light.X ;
			if (pix >= 0 && pix <= width * height)
				if (zbuffer[pix] < light.Z)
				{
					zbuffer[pix] = light.Z;
					pixels[pix] = RGB(GetBValue(0xff0000), GetGValue(0xff0000), GetRValue(0xff0000));
				//}
		//}
	}
}

void Scene::DrawScene()
{
	this->toCam();
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
			this->pixels[j*this->width + i] = RGB(GetBValue(this->color), GetGValue(this->color), GetRValue(this->color));

	for (int i = 0; i<this->width * this->height; i++)
	{
		this->zbuffer[i] = -9999999;
	}
	sunny(this->camPointOfLight, this->zbuffer, this->pixels, this->width, this->height);
	for (int i = 0; i < MyModels.size(); i++)
	{
		this->MyModels[i].PaintModel(this->pixels, this->width, this->height, this->zbuffer, this->camPointOfLight);
	}

	SelectObject(this->hdcMem, this->sBmp);
	BitBlt(this->hdc, X, Y, this->width, this->height, this->hdcMem, 0, 0, SRCCOPY);
}

void Scene::AddModel(Model MyModel)
{
	//#pragma omp parallel for
	for (int vertexIndex = 0; vertexIndex < MyModel.NodesNum; vertexIndex++)
	{
		node v;
		v.X = MyModel.Nodes[vertexIndex].X;
		v.Y = MyModel.Nodes[vertexIndex].Y;
		v.Z = MyModel.Nodes[vertexIndex].Z;

		int nX = v.X + 1. - MyModel.Center.X;
		int nY = v.Y + 1. - MyModel.Center.Y;
		int nZ = v.Z + 1. - MyModel.Center.Z;

		MyModel.Nodes[vertexIndex].X = nX;
		MyModel.Nodes[vertexIndex].Y = nY;
		MyModel.Nodes[vertexIndex].Z = nZ;
	}

	node center;
	center.X = 0;
	center.Y = 0;
	center.Z = 0;

	MyModel.Center.X = center.X;
	MyModel.Center.Y = center.Y;
	MyModel.Center.Z = center.Z;

	this->MyModels.push_back(MyModel);
}

void Scene::Clear()
{
	this->MyModels.clear();
}

void Scene::toCam()
{
	int xCenter = this->width / 2;
	int yCenter = this->height / 2;

	Cmatrix view = this->cam->cameraview();

	for (int Index = 0; Index < this->MyModels.size(); Index++)
	{
		Model* MyModel = &this->MyModels[Index];

		for (int vertexIndex = 0; vertexIndex < MyModel->NodesNum; vertexIndex++)
		{
			Cvector NodVec(MyModel->Nodes[vertexIndex].X, MyModel->Nodes[vertexIndex].Y, MyModel->Nodes[vertexIndex].Z, 1);
			Cvector result;
			for (int i = 0; i <= 3; i++)
			{
				for (int j = 0; j <= 3; j++)
				{
					result[i] = result[i] + view[j][i] * NodVec[j];
				}
			}
			MyModel->NewNodes[vertexIndex].X = result[0] + xCenter;
			MyModel->NewNodes[vertexIndex].Y = result[1] + yCenter;
			MyModel->NewNodes[vertexIndex].Z = result[2];
		}

		Cmatrix nview = view;
		nview.transposition();
		nview.inverse();

		for (int i = 0; i < MyModel->Normals.size(); i++)
		{
			MyModel->sNormals[i] = MyModel->Normals[i] * nview;
		}
	}
		Cvector tmp(PointOfLight.X, PointOfLight.Y, PointOfLight.Z, 1);
		Cvector result = tmp;
		result = result * view;
		
		this->camPointOfLight.X = result[0] / result[3];
		this->camPointOfLight.Y = result[1] / result[3];
		this->camPointOfLight.Z = result[2] / result[3];

		this->camPointOfLight.X += this->width / 2;
		this->camPointOfLight.Y += this->height / 2;
		this->camPointOfLight.Z += 0;
}