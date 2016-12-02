#include "stdafx.h"
#include "MatrixVector.h"

GVector::GVector()
{
	for (int i = 0; i <= 3; i++)
	{
		this->vec.push_back(0);
	}
}

GVector::GVector(double X, double Y, double Z, double hc)
{
	this->vec.push_back(X);
	this->vec.push_back(Y);
	this->vec.push_back(Z);
	this->vec.push_back(hc);
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

GVector& GVector::operator=(GVector other)
{
	this->vec = other.getVec();
	return *this;
}

GVector GVector::operator+(const GVector other)
{
	GVector result;
	result[0] = (*this)[0] + other[0];
	result[1] = (*this)[1] + other[1];
	result[2] = (*this)[2] + other[2];
	result[3] = (*this)[3];
	return result;
}

GVector GVector::operator-(const GVector other)
{
	GVector result;
	result[0] = (*this)[0] - other[0];
	result[1] = (*this)[1] - other[1];
	result[2] = (*this)[2] - other[2];
	result[3] = (*this)[3];
	return result;
}

GVector GVector::operator/(const double value)
{
	GVector result;
	result[0] = (*this)[0] / value;
	result[1] = (*this)[1] / value;
	result[2] = (*this)[2] / value;
	result[3] = (*this)[3];
	return result;
}

GVector GVector::operator*(const double value)
{
	GVector result;
	result[0] = (*this)[0] * value;
	result[1] = (*this)[1] * value;
	result[2] = (*this)[2] * value;
	result[3] = (*this)[3];
	return result;
}

double& GVector::operator[](const size_t index)
{
	
	return this->vec[index];
}

const double& GVector::operator[](const size_t index) const
{
	
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
	double length = (*this).length();
	if (length == 0)
	{
		return *this;
	}

	double norm = 1 / length;
	for (int i = 0; i < 3; ++i)
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
		if (round(this->vec[i] * 100) / 100. != round(other[i] * 100) / 100.)
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
		if (round(this->vec[i] * 100) / 100. != round(other[i] * 100) / 100.)
		{
			return true;
		}
	}
	return false;
}

//////

GMatrix::GMatrix()
{
	for (size_t i = 0; i <= 3; i++)
	{
		GVector tmp;
		this->matrix.push_back(tmp);
	}
}

GMatrix::GMatrix(const GMatrix& other)
{
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

GMatrix::GMatrix(GMatrix&& other)
{
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

GMatrix::~GMatrix()
{
	this->matrix.clear();
}

GMatrix& GMatrix::operator=(GMatrix other)
{
	this->matrix.clear();
	for (size_t i = 0; i <= 3; i++)
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

GMatrix GMatrix::operator-()
{
	GMatrix result(*this);
	result = result * (-1);
	return result;;
}

GMatrix GMatrix::operator*(const double value)
{
	GMatrix result(*this);

	for (size_t i = 0; i <= 3; i++)
	{
		for (size_t j = 0; j <= 3; j++)
		{
			result[i][j] = result[i][j] * value;
		}
	}
	return result;
}

GMatrix GMatrix::operator*(const GMatrix& other)
{
	GMatrix result(*this);

	for (size_t i = 0; i <= 3; i++)
	{
		GVector row((*this)[i]);
		for (size_t j = 0; j <= 3; j++)
		{
			GVector column(other[0][j], other[1][j], other[2][j], other[3][j]);
			double sum = 0;
			for (size_t k = 0; k <= 3; k++)
				sum += row[k] * column[k];
			result[i][j] = sum;
		}
	}
	return result;
}

bool GMatrix::inverse()
{
	GMatrix result;

	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 0; j <= 3; ++j)
			result[i][j] = 0.0;

		result[i][i] = 1.0;
	}


	GMatrix tmp(*this);

	for (int k = 0; k <= 3; ++k)
	{
		if (fabs(tmp[k][k]) < 1e-8)
		{
			bool changed = false;
			for (int i = k + 1; i <= 3; ++i)
			{
				if (fabs(tmp[i][k]) > 1e-8)
				{
					std::swap(tmp[k], tmp[i]);
					std::swap(result[k], result[i]);

					changed = true;
					break;
				}
			}

			if (!changed)
			{
				return false;
			}
		}


		double div = tmp[k][k];
		for (int j = 0; j <= 3; ++j)
		{
			tmp[k][j] /= div;
			result[k][j] /= div;
		}

		for (int i = k + 1; i <= 3; ++i)
		{
			double multi = tmp[i][k];
			for (int j = 0; j <= 3; ++j)
			{
				tmp[i][j] -= multi * tmp[k][j];
				result[i][j] -= multi * result[k][j];
			}
		}
	}

	for (int k = 3; k > 0; --k)
	{
		for (int i = k - 1; i + 1 > 0; --i)
		{
			double multi = tmp[i][k];
			for (int j = 0; j <= 3; ++j)
			{
				tmp[i][j] -= multi * tmp[k][j];
				result[i][j] -= multi * result[k][j];
			}
		}
	}

	*this = result;

	return true;
}

GMatrix GMatrix::transposition()
{
	GMatrix result;
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			result[i][j] = this->matrix[j][i];
		}
	}
	*this = result;
	return *this;
}

GMatrix matrixrotationX(double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	GMatrix transform;

	transform[0][0] = cosa;
	transform[0][1] = 0;
	transform[0][2] = sina;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = 1;
	transform[1][2] = 0;
	transform[1][3] = 0;

	transform[2][0] = -sina;
	transform[2][1] = 0;
	transform[2][2] = cosa;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

GMatrix matrixrotationY(double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	GMatrix transform;

	transform[0][0] = 1;
	transform[0][1] = 0;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = cosa;
	transform[1][2] = -sina;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = sina;
	transform[2][2] = cosa;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

GMatrix matrixrotationZ(double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	GMatrix transform;

	transform[0][0] = cosa;
	transform[0][1] = -sina;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = sina;
	transform[1][1] = cosa;
	transform[1][2] = 0;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = 0;
	transform[2][2] = 1;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

GMatrix matrixMove(double X, double Y, double Z)
{
	GMatrix transform;

	transform[0][0] = 1;
	transform[0][1] = 0;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = 1;
	transform[1][2] = 0;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = 0;
	transform[2][2] = 1;
	transform[2][3] = 0;

	transform[3][0] = X;
	transform[3][1] = Y;
	transform[3][2] = Z;
	transform[3][3] = 1;

	return transform;
}