#pragma once
#include "stdafx.h"
#include <vector>
#include "MatrixVector.h"

using namespace std;

typedef struct node
{
	float X;
	float Y;
	float Z;
};

typedef struct polygon
{
	int A;
	int B;
	int C;
	int N;
};

class Model 
{
private:
	
	FILE* F;
	void ReadNodes();

public:
	Model();
	~Model();
	int NodesNum;
	node Center;
	COLORREF Color;
	float coeff;
	int PolygonNum;

	vector<node> Nodes;
	vector<node> NewNodes;
	vector<polygon> Polygons;
	vector<Cvector> Normals;
	vector<Cvector> sNormals;
	Cmatrix rotate;
	Cmatrix nMatrixRotation;

	void LoadFromFile(char* FileName);
	void PaintSkeleton(unsigned long* pixels);
	void PaintModel(unsigned long* pixels, int width, int height, float* zbuffer, node PointOfLight);
	void MoveX(float DeltaMove);
	void MoveY(float DeltaMove);
	void MoveZ(float DeltaMove);
	void RotateX(float DeltaRotate);
	void RotateY(float DeltaRotate);
	void RotateZ(float DeltaRotate);
	void initModification(node* Center);
	void ClearModel();
	int PolygonCompare(node A1, node A2, node A3, node B1, node B2, node B3);
};

