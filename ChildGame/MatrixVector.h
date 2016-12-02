#pragma once
#include "stdafx.h"
#include <vector>

using namespace std;

class GMatrix;

class GVector
{
public:

	GVector();

	GVector(double X, double Y, double Z, double lenglth);

	GVector(const GVector& other);

	GVector(GVector&& other);

	~GVector();

	GVector& operator=(GVector& other);
	GVector& operator=(const GVector& other);
	GVector& operator=(GVector&& other);
	GVector& operator+(const GVector other);
	GVector& operator-(const GVector other);
	GVector& operator/(const double value);
	GVector& operator*(const double value);
	double& operator[](const size_t index);
	const double& operator[](const size_t index) const;

	vector<double> getVec() const;
	double length();

	GVector normalize();

	static GVector cross(GVector first, GVector second);

	static double scalar(GVector first, GVector second);

	static double angle(GVector first, GVector second);

	GVector operator*(GMatrix matrix);

	bool operator==(const GVector& other) const;

	bool operator!=(const GVector& other) const;



private:
	vector<double> vec;	/*!< Vector contains coordinates */
};

////////

class GMatrix
{
public:
	GMatrix();

	GMatrix(const GMatrix& other);

	GMatrix(GMatrix&& other);

	~GMatrix();

	GMatrix& operator=(GMatrix& other);
	GMatrix& operator=(GMatrix&& other);
	GVector& operator[](const unsigned long index);
	const GVector& operator[](const unsigned long index) const;
	GMatrix& operator-();
	GMatrix& operator*(const double value);
	GMatrix operator*(const GMatrix& other);
	bool inverse();
	GMatrix transposition();

private:
	vector<GVector> matrix;	
};


GMatrix matrixrotationX(double angle);
GMatrix matrixrotationY(double angle);
GMatrix matrixrotationZ(double angle);
GMatrix matrixMove(double X, double Y, double Z);