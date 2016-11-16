#include "stdafx.h"
#include "math.h"
#include "Model.h"

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
void fillFaces(node A, node B, node C, unsigned long* pixels, int width)
{
	if (A.Y == B.Y && A.Y == C.Y) return;

	if (A.Y > B.Y) swap(A, B);
	if (A.Y > C.Y) swap(A, C);
	if (B.Y > C.Y) swap(B, C);

	int aY = A.Y;
	int bY = B.Y;
	int cY = C.Y;
	int aX = A.X;
	int bX = B.X;
	int cX = C.X;

	int faceHeight = cY - aY;
	int halfHeight = bY - aY;

	for (int yCoord = 0; yCoord < faceHeight; yCoord++) {
		bool secondPart = yCoord > bY - aY || bY == aY;

		float ak = (float)yCoord / faceHeight;
		float bk;
		if (secondPart)
		{
			halfHeight = cY - bY;
			bk = (float)(yCoord - (bY - aY)) / halfHeight;
		}
		else
		{
			bk = (float)yCoord / halfHeight;
		}

		node na;
		na.X = (aX + (cX - aX) * ak);
		na.Y = (aY + (cY - aY) * ak);
		na.Z = 0;
		node nb;
		if (secondPart)
		{
			nb.X = (bX + (cX - bX) * bk);
			nb.Y = (bY + (cY - bY) * bk);
		}
		else
		{
			nb.X = (aX + (bX - aX) * bk);
			nb.Y = (aY + (bY - aY) * bk);
		}

		if (na.X > nb.X)
		{
			swap(na, nb);
		}

		for (int xCoord = na.X; xCoord <= nb.X; xCoord++)
		{
			pixels[(int)(A.Y + yCoord)*width + xCoord] = 0x00006700;
		}

	}

}
////////////////

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
	fscanf_s(this->F, "%d", &(this->NodesNum));
	for (int i = 0; i < this->NodesNum; i++)
	{
		fscanf_s(this->F, "%f %f %f", &(BufNode.X), &(BufNode.Y), &(BufNode.Z));
		BufNode.X = BufNode.X*20;
		BufNode.Y = BufNode.Y*20;
		BufNode.Z = BufNode.Z*20;
		this->Nodes.push_back(BufNode);
		this->NewNodes.push_back(BufNode);
	}

	fscanf_s(this->F, "%d", &(this->PolygonNum));
	for (int i = 0; i < this->PolygonNum; i++)
	{
		fscanf_s(this->F, "%d %d %d", &(BufPolygon.A), &(BufPolygon.B), &(BufPolygon.C));
		this->Polygons.push_back(BufPolygon);
	}
	fscanf_s(this->F, "%f %f %f", &(this->Center.X), &(this->Center.Y), &(this->Center.Z));

}

void Model::PaintModel(unsigned long* pixels)
{	
	for (int i = 0; i < this->PolygonNum; i++)
	{
		int x1 = this->Nodes[this->Polygons[i].A].X;
		int y1 = this->Nodes[this->Polygons[i].A].Y;

		int x2 = this->Nodes[this->Polygons[i].B].X;
		int y2 = this->Nodes[this->Polygons[i].B].Y;

		int x3 = this->Nodes[this->Polygons[i].C].X;
		int y3 = this->Nodes[this->Polygons[i].C].Y;

		line(x1, y1, x2, y2, pixels, 500);
		line(x2, y2, x3, y3, pixels, 500);
		line(x1, y1, x3, y3, pixels, 500);

	}
}

void Model::FillModel(unsigned long* pixels)
{
	for (int i = 0; i < this->PolygonNum; i++)
	{
		node A = this->NewNodes[this->Polygons[i].A];
	    node B = this->NewNodes[this->Polygons[i].B];
		node C = this->NewNodes[this->Polygons[i].C];

		fillFaces(A, B, C, pixels, 500);
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


