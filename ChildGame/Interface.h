#pragma once
#include "Model.h"
#include "Camera.h"
using namespace std;

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

class Label : public Inter
{
public:
	Label();
	Label(WCHAR* Text, int X, int Y, int Height, int Width);
	~Label();
};

class Edit : public Inter
{
private:
	int Id;
public:
	Edit();
	Edit(WCHAR* Text, int X, int Y, int Height, int Width, int ID);
	~Edit();
};

class Scene
{
public:
	Scene();
	Scene(HWND hWnd, int x, int y, int width, int height);
	~Scene();

	void Clear();
	void DrawScene();
	void AddModel(Model MyModel, int type);

	vector<Model> MyModels;
	Camera* cam;
	node PointOfLight;
	node camPointOfLight;

	COLORREF color;
private:
	void InitBitmap();

	int X;
	int Y;
	int width;
	int height;

	unsigned long* pixels;
	float* zbuffer;

	BITMAPINFO sBmInfo;
	HBITMAP sBmp;
	HDC hdc;
	HDC hdcMem;
	HWND hWnd;
	void toCam();

};