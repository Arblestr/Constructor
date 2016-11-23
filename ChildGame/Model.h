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
	int PolygonNum;
	FILE* F;
	void ReadNodes();

public:
	Model();
	~Model();
	int NodesNum;
	node Center;

	vector<node> Nodes;
	vector<node> NewNodes;
	vector<polygon> Polygons;
	vector<GVector> Normals;

	void LoadFromFile(char* FileName);
	void PaintModel(unsigned long* pixels);
	void FillModel(unsigned long* pixels, int width, int height, float* zbuffer, node PointOfLight);
	void MoveX(float DeltaMove);
	void MoveY(float DeltaMove);
	void MoveZ(float DeltaMove);
	void RotateX(float DeltaRotate);
	void RotateY(float DeltaRotate);
	void RotateZ(float DeltaRotate);
	void ClearModel();
};

