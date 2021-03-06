#include "stdafx.h"
#include "math.h"
#include "Model.h"
#include <algorithm>
#include "MatrixVector.h"
#include "triangles.h"

int Model:: PolygonCompare(node A1, node A2, node A3, node B1, node B2, node B3)
{
	float V0[3], V1[3], V2[3];
	V0[0] = A1.X; V0[1] = A1.Y; V0[2] = A1.Z;
	V1[0] = A2.X; V1[1] = A2.Y; V1[2] = A2.Z;
	V2[0] = A3.X; V2[1] = A3.Y; V2[2] = A3.Z;
	float U0[3], U1[3], U2[3];
	U0[0] = B1.X; U0[1] = B1.Y; U0[2] = B1.Z;
	U1[0] = B2.X; U1[1] = B2.Y; U1[2] = B2.Z;
	U2[0] = B3.X; U2[1] = B3.Y; U2[2] = B3.Z;
	return tri_tri_intersect(V0, V1, V2, U0, U1, U2);
}

double CalculateIntensity(double X, double Y, double Z, Cvector N, node light)
{
	Cvector D(light.X - X, light.Y - Y, light.Z - Z, 1);
	D * (-1);
	D.normalize();
	N.normalize();
	double I;
	double Iconst = 0.4;
	double gg = Cvector::scalar(N, D);
	double Idiff = 0.4 * max(0, gg);
	double Iblinn = 0;
	I = Iconst + Idiff + Iblinn;
	return I;
}

////////////////
void PaintLine(int x0, int y0, int x1, int y1, unsigned long* pixels, int width)
{
	bool step = false;
	if (abs(x0 - x1) < abs(y0 - y1)) 
	{
		swap(x0, y0);
		swap(x1, y1);
		step = true;
	}

	if (x0 > x1) 
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = abs(dy) * 2;
	int error2 = 0;

	int y = y0;

	for (int x = x0; x <= x1; x++) {
		if (step) {
			pixels[x*width + y] = 0x000000;
		}
		else {
			pixels[y*width + x] = 0x000000;
		}
		error2 += derror2;

		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}
////////////////
void PaintSide(COLORREF color,node A, node B, node C, unsigned long* pixels, int width, int height, float* zbuffer, Cvector normA, node light)
{
	if (A.Y == B.Y && A.Y == C.Y) return;

	if (A.Y > B.Y)
		swap(A, B);
	if (A.Y > C.Y)
		swap(A, C);
	if (B.Y > C.Y)
		swap(B, C);

	if (int(A.Y + .5) == int(B.Y + .5) && B.X < A.X)
		swap(A, B);

	int x1 = int(A.X + .5);
	int x2 = int(B.X + .5);
	int x3 = int(C.X + .5);
	int y1 = int(A.Y + .5);
	int y2 = int(B.Y + .5);
	int y3 = int(C.Y + .5);
	float z1 = A.Z;
	float z2 = B.Z;
	float z3 = C.Z;

	double dx13 = 0, dx12 = 0, dx23 = 0;
	double dz13 = 0, dz12 = 0, dz23 = 0;

	if (y3 != y1)
	{
		dz13 = (z3 - z1) / (double)(y3 - y1);
		dx13 = (x3 - x1) / (double)(y3 - y1);
	}
	if (y2 != y1)
	{
		dz12 = (z2 - z1) / (double)(y2 - y1);
		dx12 = (x2 - x1) / (double)(y2 - y1);
	}
	if (y3 != y2)
	{
		dz23 = (z3 - z2) / (double)(y3 - y2);
		dx23 = (x3 - x2) / (double)(y3 - y2);
	}

	double z = 0;
	double dz = 0;

	double wx1 = x1;
	double wx2 = x1;
	double wz1 = z1;
	double wz2 = z1;

	double _dx13 = dx13;
	double _dz13 = dz13;


	if (dx13 > dx12)
	{
		swap(dx13, dx12);
		swap(dz13, dz12);
	}

	if (y1 == y2)
	{
		wx1 = x1;
		wx2 = x2;
		wz1 = z1;
		wz2 = z2;
	}

	if (_dx13 < dx23)
	{
		swap(_dx13, dx23);
		swap(_dz13, dz23);
	}

	for (int yCoord = y1; yCoord < y3; yCoord++)
	{
		z = wz1;

		if (wx1 != wx2)
			dz = (wz2 - wz1) / (double)(wx2 - wx1);

		for (int xCoord = wx1; xCoord < wx2; xCoord++)
		{
			int pix = yCoord * width + xCoord;
			if (xCoord < 0 || xCoord > width || yCoord < 0 || yCoord > height)
				return;
			if (pix >= 0 && pix <= width * height)
				if (zbuffer[pix] < z)
				{
					double I = CalculateIntensity(xCoord, yCoord, z, normA, light);
					zbuffer[pix] = z;
					pixels[pix] = RGB(GetBValue(color) * I,GetGValue(color) * I,GetRValue(color) * I);
				}
			z += dz;
		}
		if (yCoord < y2)
		{
			wx1 += dx13;
			wx2 += dx12;
			wz1 += dz13;
			wz2 += dz12;
		}
		else
		{
			wx1 += _dx13;
			wx2 += dx23;
			wz1 += _dz13;
			wz2 += dz23;
		}
	}
}
////////////////

Model::Model()
{
	this->NodesNum = 0;
	this->PolygonNum = 0;
	this->Color = 0x0000ff;
	this->coeff = 1;
};

Model::~Model()
{
	Nodes.clear();
	Polygons.clear();
};

void Model::LoadFromFile(char* FileName)
{
	this->F = fopen(FileName, "r");
	if (!(this->F))
	{
		
	}
	else
	{
		this->ReadNodes();

		fclose(this->F);
	}
}

void Model::ReadNodes()
{
	node BufNode;
	polygon BufPolygon;
	Cvector BufNormal;
	double BufNormalX;
	double BufNormalY;
	double BufNormalZ;
	BufNormal[3] = 0;
	fscanf_s(this->F, "%d", &(this->NodesNum));
	for (int i = 0; i < this->NodesNum; i++)
	{
		fscanf_s(this->F, "%f %f %f", &(BufNode.X), &(BufNode.Y), &(BufNode.Z));
		BufNode.X = BufNode.X * 40;
		BufNode.Y = BufNode.Y * 40;
		BufNode.Z = BufNode.Z * 40;
		this->Nodes.push_back(BufNode);
		this->NewNodes.push_back(BufNode);
	}

	fscanf_s(this->F, "%d", &(this->PolygonNum));
	for (int i = 0; i < this->PolygonNum; i++)
	{
		fscanf_s(this->F, "%d %d %d %d", &(BufPolygon.A), &(BufPolygon.B), &(BufPolygon.C), &(BufPolygon.N));
		this->Polygons.push_back(BufPolygon);
	}
	for (int i = 0; i < 6; i++)
	{
		fscanf_s(this->F, "%lf %lf %lf", &(BufNormal[0]), &(BufNormal[1]), &(BufNormal[2]));
		this->Normals.push_back(BufNormal);
		this->sNormals.push_back(BufNormal);
	}
	fscanf_s(this->F, "%f %f %f", &(this->Center.X), &(this->Center.Y), &(this->Center.Z));
	this->NewCenter = this->Center;

}

void Model::PaintSkeleton(unsigned long* pixels)
{
	for (int i = 0; i < this->PolygonNum; i++)
	{
		int x1 = this->NewNodes[this->Polygons[i].A].X;
		int y1 = this->NewNodes[this->Polygons[i].A].Y;

		int x2 = this->NewNodes[this->Polygons[i].B].X;
		int y2 = this->NewNodes[this->Polygons[i].B].Y;

		int x3 = this->NewNodes[this->Polygons[i].C].X;
		int y3 = this->NewNodes[this->Polygons[i].C].Y;

		PaintLine(x1, y1, x2, y2, pixels, 500);
		PaintLine(x2, y2, x3, y3, pixels, 500);
		PaintLine(x1, y1, x3, y3, pixels, 500);

	}
}

void Model::PaintModel(unsigned long* pixels, int width, int height, float* zbuffer, node PointOfLight)
{
	node A;
	node B;
	node C;
	Cvector N;

	for (int i = 0; i < this->PolygonNum; i++)
	{
		A = this->NewNodes[this->Polygons[i].A];
		B = this->NewNodes[this->Polygons[i].B];
		C = this->NewNodes[this->Polygons[i].C];
		N = this->sNormals[this->Polygons[i].N];

		PaintSide(this->Color,A, B, C, pixels, width, height, zbuffer, N, PointOfLight);
	}		
}

void Model::MoveX(float DeltaMove)
{
	for (int i = 0; i < this->NodesNum; i++)
		this->Nodes[i].X += DeltaMove;
	this->Center.X += DeltaMove;
}

void Model::MoveY(float DeltaMove)
{
	for (int i = 0; i < this->NodesNum; i++)
		this->Nodes[i].Y += DeltaMove;
	this->Center.Y += DeltaMove;
}

void Model::MoveZ(float DeltaMove)
{
	for (int i = 0; i < this->NodesNum; i++)
		this->Nodes[i].Z += DeltaMove;
	this->Center.Z += DeltaMove;
}

void Model::RotateX(float DeltaRotate)
{
	this->Xangle += DeltaRotate;
	this->rotate = matrixrotationX(DeltaRotate*M_PI / 180);
	this->initModification(&Center);
	for (int i = 0; i < this->NodesNum; i++)
	{
		float NewY =
			this->Center.Y + (this->Nodes[i].Y - this->Center.Y) * cos(DeltaRotate*M_PI / 180) -
			(this->Nodes[i].Z - this->Center.Z) * sin(DeltaRotate*M_PI / 180);

		float NewZ = this->Center.Z + (this->Nodes[i].Y - this->Center.Y) * sin(DeltaRotate*M_PI / 180) +
			(this->Nodes[i].Z - this->Center.Z) * cos(DeltaRotate*M_PI / 180);

		this->Nodes[i].Y = NewY;
		this->Nodes[i].Z = NewZ;
	}

	for (int j = 0; j < this->Normals.size(); j++)
	{
		this->Normals[j] = this->Normals[j] * this->nMatrixRotation;
	}
}

void Model::RotateY(float DeltaRotate)
{
	this->Yangle += DeltaRotate;
	this->rotate = matrixrotationY(DeltaRotate*M_PI / 180);
	this->initModification(&Center);
	for (int i = 0; i < this->NodesNum; i++)
	{
		float NewX = this->Center.X + (this->Nodes[i].X - this->Center.X) * cos(DeltaRotate*M_PI / 180) -
			(this->Nodes[i].Z - this->Center.Z) * sin(DeltaRotate*M_PI / 180);

		float NewZ = this->Center.Z + (this->Nodes[i].X - this->Center.X) * sin(DeltaRotate*M_PI / 180) +
			(this->Nodes[i].Z - this->Center.Z) * cos(DeltaRotate*M_PI / 180);

		this->Nodes[i].X = NewX;
		this->Nodes[i].Z = NewZ;
	}

	for (int j = 0; j < this->Normals.size(); j++)
	{
		this->Normals[j] = this->Normals[j] * this->nMatrixRotation;
	}
}

void Model::RotateZ(float DeltaRotate)
{
	this->Zangle += DeltaRotate;
	this->rotate = matrixrotationZ(DeltaRotate*M_PI / 180);
	this->initModification(&Center);
	for (int i = 0; i < this->NodesNum; i++)
	{
		float NewX = this->Center.X + (this->Nodes[i].X - this->Center.X) * cos(DeltaRotate*M_PI / 180) -
			(this->Nodes[i].Y - this->Center.Y) * sin(DeltaRotate*M_PI / 180);

		float NewY = this->Center.Y + (this->Nodes[i].X - this->Center.X) * sin(DeltaRotate*M_PI / 180) +
			(this->Nodes[i].Y - this->Center.Y) * cos(DeltaRotate*M_PI / 180);

		this->Nodes[i].X = NewX;
		this->Nodes[i].Y = NewY;
	}

	for (int j = 0; j < this->Normals.size(); j++)
	{
		this->Normals[j] = this->Normals[j] * this->nMatrixRotation;
	}
}

void Model::initModification(node* Center)
{
	//this->Center.X = Center->X;
	//this->Center.Y = Center->Y;
	//this->Center.Z = Center->Z;
	Cmatrix moveToOrigin = matrixMove(-this->NewCenter.X, -this->NewCenter.Y, -this->NewCenter.Z);
	Cmatrix moveBack = matrixMove(this->NewCenter.X, this->NewCenter.Y, this->NewCenter.Z);

	this->nMatrixRotation = moveToOrigin * rotate * moveBack;
	this->nMatrixRotation.transposition();
	this->nMatrixRotation.inverse();
}

void Model::ClearModel()
{
	this->NewNodes.clear();
	this->Nodes.clear();
	this->Polygons.clear();
	this->PolygonNum = 0;
	this->NodesNum = 0;
	this->Normals.clear();
}