#include "stdafx.h"
#include "MatrixVector.h"

GVector::GVector()
{
	for (int i = 0; i <= 3; i++)
	{
		this->vec.push_back(0);
	}
}

GVector::GVector(double X, double Y, double Z, double lenglth)
{
	this->vec.push_back(X);
	this->vec.push_back(Y);
	this->vec.push_back(Z);
	this->vec.push_back(1);
}

GVector::GVector(const GVector& other)
{
	this->vec = other.getVec();
}

GVector::GVector(GVector&& other)
{
	this->vec = other.getVec();
}

GVector::~GVector()
{
	this->vec.clear();
}

GVector& GVector::operator=(GVector& other)
{
	this->vec = other.getVec();
	return *this;
}

GVector& GVector::operator=(const GVector& other)
{
	this->vec = other.getVec();
	return *this;
}

GVector& GVector::operator=(GVector&& other)
{
	this->vec = other.getVec();
	return *this;
}

GVector& GVector::operator+(const GVector other)
{
	(*this)[0] = (*this)[0] + other[0];
	(*this)[1] = (*this)[1] + other[1];
	(*this)[2] = (*this)[2] + other[2];
	return *this;
}

GVector& GVector::operator-(const GVector other)
{
	(*this)[0] = (*this)[0] - other[0];
	(*this)[1] = (*this)[1] - other[1];
	(*this)[2] = (*this)[2] - other[2];
	return *this;
}

GVector& GVector::operator/(const double value)
{
	(*this)[0] = (*this)[0] / value;
	(*this)[1] = (*this)[1] / value;
	(*this)[2] = (*this)[2] / value;
	return *this;
}

GVector& GVector::operator*(const double value)
{
	(*this)[0] = (*this)[0] * value;
	(*this)[1] = (*this)[1] * value;
	(*this)[2] = (*this)[2] * value;
	return *this;
}

double& GVector::operator[](const size_t index)
{
	if (index > 3 || index < 0)
	{
		//throw VectorIndexError();
	}
	return this->vec[index];
}

const double& GVector::operator[](const size_t index) const
{
	if (index > 3 || index < 0)
	{
		//throw VectorIndexError();
	}
	return this->vec[index];
}

vector<double> GVector::getVec() const
{
	return this->vec;
}

double GVector::length()
{
	double X = (*this)[0];
	double Y = (*this)[1];
	double Z = (*this)[2];

	return sqrt(X * X + Y * Y + Z * Z);
}

GVector GVector::normalize()
{
	double norm = 1 / (*this).length();
	for (int i = 0; i <= 3; ++i)
	{
		(*this)[i] = (*this)[i] * norm;
	}

	return *this;
}

GVector GVector::cross(GVector first, GVector second)
{
	GVector result;
	result[0] = first[1] * second[2] - first[2] * second[1]; // new X = Y1 * Z2 - Z1 * Y2
	result[1] = first[2] * second[0] - first[0] * second[2]; // new Y = Z1 * X2 - X1 * Z2
	result[2] = first[0] * second[1] - first[1] * second[0]; // new Z = X1 * Y2 - Y1 * X2
	result[3] = 1;

	return result;
}

double GVector::scalar(GVector first, GVector second)
{
	return first[0] * second[0] + first[1] * second[1] + first[2] * second[2];
}

double GVector::angle(GVector first, GVector second)
{
	double angle = acos(scalar(first, second) / (first.length() * second.length()));
	angle *= 180 / M_PI;

	if (angle > 180)
	{
		angle -= 180;
	}

	return angle;
}

GVector GVector::operator*(GMatrix matrix)
{
	GVector result;
	for (size_t i = 0; i <= 3; i++)
	{
		for (size_t j = 0; j <= 3; j++)
		{
			result[i] = result[i] + matrix[j][i] * this->vec[j];
		}
	}
	return result;
}

bool GVector::operator==(const GVector& other) const
{
	for (int i = 0; i < 4; i++)
	{
		if (this->vec[i] != other[i])
		{
			return false;
		}
	}
	return true;
}

bool GVector::operator!=(const GVector& other) const
{
	for (int i = 0; i < 4; i++)
	{
		if (this->vec[i] != other[i])
		{
			return true;
		}
	}
	return false;
}

/////////////////

GMatrix::GMatrix()
{
	for (unsigned long i = 0; i <= 3; i++)
	{
		GVector tmp;
		this->matrix.push_back(tmp);
	}
}

GMatrix::GMatrix(const GMatrix& other)
{
	for (unsigned long i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

GMatrix::GMatrix(GMatrix&& other)
{
	for (unsigned long i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

GMatrix::~GMatrix()
{
	this->matrix.clear();
}

GMatrix& GMatrix::operator=(GMatrix& other)
{
	for (unsigned long i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}

	return (*this);
}

GMatrix& GMatrix::operator=(GMatrix&& other)
{
	for (unsigned long i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}

	return (*this);
}

GVector& GMatrix::operator[](const unsigned long index)
{
	return this->matrix[index];
}

const GVector& GMatrix::operator[](const unsigned long index) const
{
	return this->matrix[index];
}

GMatrix& GMatrix::operator-()
{
	return *this * (-1);
}

GMatrix& GMatrix::operator*(const double value)
{
	GMatrix result(*this);
	for (unsigned long i = 0; i <= 3; i++)
	{
		for (unsigned long j = 0; j <= 3; j++)
		{
			result[i][j] = result[i][j] * value;
		}
	}
	return (*this);
}