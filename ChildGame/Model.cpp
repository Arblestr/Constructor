#include "stdafx.h"
#include "math.h"
#include "Model.h"
#include <algorithm>


double intencity(double X, double Y, double Z, GVector N, node light)
{
	GVector D(light.X - X, light.Y - Y, light.Z + Z, 1);
	//D * (-1);
	D.normalize();
	N.normalize();
	double I;
	double Iconst = 0.4;
	double gg = GVector::scalar(N, D);
	double Idiff = 0.4 * max(0, gg);
	double Iblinn = 0;
	I = Iconst + Idiff + Iblinn;
	return I;
}

/////////////
void line(int x0, int y0, int x1, int y1, unsigned long* pixels, int width)
{
	bool step = false;
	if (abs(x0 - x1) < abs(y0 - y1)) {
		swap(x0, y0);
		swap(x1, y1);
		step = true;
	}

	if (x0 > x1) {
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
void fillFaces(node A, node B, node C, unsigned long* pixels, int width, int height, int* zbuffer,
	           GVector normA, GVector normB, GVector normC, node light)
{
	if (A.Y == B.Y && A.Y == C.Y) return;

	if (A.Y > B.Y) { std::swap(A, B); std::swap(normA, normB); }
	if (A.Y > C.Y) { std::swap(A, C); std::swap(normA, normC); }
	if (B.Y > C.Y) { std::swap(B, C); std::swap(normB, normC); }

	int faceHeight = (int)C.Y - (int)A.Y;
	int halfHeight = (int)B.Y - (int)A.Y;

	for (int yCoord = 0; yCoord < faceHeight; yCoord++) {
		bool secondPart = yCoord >(int)B.Y - (int)A.Y || (int)B.Y == (int)A.Y;

		float ak = (float)yCoord / faceHeight;
		float bk;
		if (secondPart)
		{
			halfHeight = (int)C.Y - (int)B.Y;
			bk = (float)(yCoord - ((int)B.Y - (int)A.Y)) / halfHeight;
		}
		else
		{
			bk = (float)yCoord / halfHeight;
		}

		node na;
		na.X = (int)A.X + ((int)C.X - (int)A.X) * ak;
		na.Y = (int)A.Y + ((int)C.Y - (int)A.Y) * ak;
		na.Z = (int)A.Z + ((int)C.Z - (int)A.Z) * ak;
		GVector nNormA(normA + (normC - normA) * ak);

		node nb;
		GVector nNormB;
		if (secondPart)
		{
			nb.X = (int)B.X + ((int)C.X - (int)B.X) * bk;
			nb.Y = (int)B.Y + ((int)C.Y - (int)B.Y) * bk;
			nb.Z = (int)B.Z + ((int)C.Z - (int)B.Z) * bk;

			nNormB = normB + (normC - normB) * bk;
		}
		else
		{
			nb.X = (int)A.X + ((int)B.X - (int)A.X) * bk;
			nb.Y = (int)A.Y + ((int)B.Y - (int)A.Y) * bk;
			nb.Z = (int)A.Z + ((int)B.Z - (int)A.Z) * bk;

			nNormB = normA + (normB - normA) * bk;
		}

		if ((int)na.X > (int)nb.X)
		{
			std::swap(na, nb);
			std::swap(nNormA, nNormB);
		}

		for (int xCoord = (int)na.X; xCoord <= (int)nb.X; xCoord++)
		{

			double phi = 1.;
			if ((int)nb.X != (int)na.X)
			{
				phi = (double)(xCoord - (int)na.X) / (double)((int)nb.X - (int)na.X);
			}
			//double AG = normA.length();
			node P;
			P.X = (int)na.X + ((int)nb.X - (int)na.X) * phi;
			P.Y = (int)na.Y + ((int)nb.Y - (int)na.Y) * phi;
			P.Z = (int)na.Z + ((int)nb.Z - (int)na.Z) * phi;
			GVector normP(nNormA + (nNormB - nNormA) * phi);

			int pix = ((int)A.Y + yCoord) * width + xCoord;
			if (pix >= 0 && pix <= width * height)
			{
				if (zbuffer[(int)P.X + (int)P.Y * width] <= P.Z)
				{
					zbuffer[(int)P.X + (int)P.Y * width] = P.Z;
					double I = intencity(P.X, P.Y, P.Z, normP, light);
					pixels[pix] =  RGB(GetRValue(0x00ff00) * I, GetGValue(0x00ff00) * I, GetBValue(0x00ff00) * I);
				}
			}
		}

	}

}
////////////////


/////////////////

Model::Model()
{
	this->NodesNum = 0;
	this->PolygonNum = 0;
};

Model::~Model()
{
	Nodes.clear();
	Polygons.clear();
};

void Model::LoadFromFile(char* FileName)
{
	this->F = fopen(FileName,"r");
	if (!(this->F)) 
	{
		// error
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
	GVector BufNormal;
	//BufNormal[3] = 1;
	fscanf_s(this->F, "%d", &(this->NodesNum));
	for (int i = 0; i < this->NodesNum; i++)
	{
		fscanf_s(this->F, "%f %f %f", &(BufNode.X), &(BufNode.Y), &(BufNode.Z));
		BufNode.X = BufNode.X*40;
		BufNode.Y = BufNode.Y*40;
		BufNode.Z = BufNode.Z*40;
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
		fscanf_s(this->F, "%d %d %d", &(BufNormal[0]), &(BufNormal[1]), &(BufNormal[2]));
		this->Normals.push_back(BufNormal);
	}
	fscanf_s(this->F, "%f %f %f", &(this->Center.X), &(this->Center.Y), &(this->Center.Z));

}

void Model::PaintModel(unsigned long* pixels)
{	
	for (int i = 0; i < this->PolygonNum; i++)
	{
		int x1 = this->NewNodes[this->Polygons[i].A].X;
		int y1 = this->NewNodes[this->Polygons[i].A].Y;

		int x2 = this->NewNodes[this->Polygons[i].B].X;
		int y2 = this->NewNodes[this->Polygons[i].B].Y;

		int x3 = this->NewNodes[this->Polygons[i].C].X;
		int y3 = this->NewNodes[this->Polygons[i].C].Y;

		line(x1, y1, x2, y2, pixels, 500);
		line(x2, y2, x3, y3, pixels, 500);
		line(x1, y1, x3, y3, pixels, 500);

	}
}

void Model::FillModel(unsigned long* pixels, int width, int height, int* zbuffer, node PointOfLight)
{
	node A;
	node B;
	node C;
	GVector N;

	for (int i = 0; i < this->PolygonNum; i++)
	{
		A = this->NewNodes[this->Polygons[i].A];
	    B = this->NewNodes[this->Polygons[i].B];
		C = this->NewNodes[this->Polygons[i].C];
		N = this->Normals[this->Polygons[i].N];
		//int kk = this->Polygons[i].N;
		//double AG = N.length();
		fillFaces(A, B, C, pixels, width, height, zbuffer, N,N,N, PointOfLight);
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
}

void Model::RotateY(float DeltaRotate)
{
	for (int i = 0; i < this->NodesNum; i++)
	{
		float NewX = this->Center.X + (this->Nodes[i].X - this->Center.X) * cos(DeltaRotate*M_PI / 180) -
			(this->Nodes[i].Z - this->Center.Z) * sin(DeltaRotate*M_PI / 180);

		float NewZ = this->Center.Z + (this->Nodes[i].X - this->Center.X) * sin(DeltaRotate*M_PI / 180) +
			(this->Nodes[i].Z - this->Center.Z) * cos(DeltaRotate*M_PI / 180);

		this->Nodes[i].X = NewX;
		this->Nodes[i].Z = NewZ;
	}
}

void Model::RotateZ(float DeltaRotate)
{
	for (int i = 0; i < this->NodesNum; i++)
	{
		float NewX = this->Center.X + (this->Nodes[i].X - this->Center.X) * cos(DeltaRotate*M_PI / 180) -
			(this->Nodes[i].Y - this->Center.Y) * sin(DeltaRotate*M_PI / 180);

		float NewY = this->Center.Y + (this->Nodes[i].X - this->Center.X) * sin(DeltaRotate*M_PI / 180) +
			(this->Nodes[i].Y - this->Center.Y) * cos(DeltaRotate*M_PI / 180);

		this->Nodes[i].X = NewX;
		this->Nodes[i].Y = NewY;
	}
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


