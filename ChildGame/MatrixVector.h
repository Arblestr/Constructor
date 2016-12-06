#pragma once
#include "stdafx.h"
#include <vector>

using namespace std;

class Cmatrix;

class Cvector
{
public:

	Cvector();
	Cvector(double X, double Y, double Z, double hc);
	Cvector(const Cvector& other);
	Cvector(Cvector&& other);
	~Cvector();
	Cvector& operator=(Cvector other);
	Cvector operator+(const Cvector other);
	Cvector operator-(const Cvector other);
	Cvector operator/(const double value);
	Cvector operator*(const double value);
	double& operator[](const size_t index);
	const double& operator[](const size_t index) const;
	vector<double> getVec() const;
	double length();
	Cvector normalize();
	static Cvector cross(Cvector first, Cvector second);
	static double scalar(Cvector first, Cvector second);
	static double angle(Cvector first, Cvector second);
	Cvector operator*(Cmatrix matrix);
	bool operator==(const Cvector& other) const;
	bool operator!=(const Cvector& other) const;
private:
	vector<double> vec;	
};

////////

class Cmatrix
{
public:
	Cmatrix();
	Cmatrix(const Cmatrix& other);
	Cmatrix(Cmatrix&& other);
	~Cmatrix();
	Cmatrix& operator=(Cmatrix other);
	Cvector& operator[](const unsigned long index);
	const Cvector& operator[](const unsigned long index) const;
	Cmatrix operator-();
	Cmatrix operator*(const double value);
	Cmatrix operator*(const Cmatrix& other);
	bool inverse();
	Cmatrix transposition();
private:
	vector<Cvector> matrix;	
};


Cmatrix matrixrotationX(double angle);
Cmatrix matrixrotationY(double angle);
Cmatrix matrixrotationZ(double angle);
Cmatrix matrixMove(double X, double Y, double Z);