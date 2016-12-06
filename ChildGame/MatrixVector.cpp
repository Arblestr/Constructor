#include "stdafx.h"
#include "MatrixVector.h"

Cvector::Cvector()
{
	for (int i = 0; i <= 3; i++)
	{
		this->vec.push_back(0);
	}
}

Cvector::Cvector(double X, double Y, double Z, double hc)
{
	this->vec.push_back(X);
	this->vec.push_back(Y);
	this->vec.push_back(Z);
	this->vec.push_back(hc);
}

Cvector::Cvector(const Cvector& other)
{
	this->vec = other.getVec();
}

Cvector::Cvector(Cvector&& other)
{
	this->vec = other.getVec();
}

Cvector::~Cvector()
{
	this->vec.clear();
}

Cvector& Cvector::operator=(Cvector other)
{
	this->vec = other.getVec();
	return *this;
}

Cvector Cvector::operator+(const Cvector other)
{
	Cvector result;
	result[0] = (*this)[0] + other[0];
	result[1] = (*this)[1] + other[1];
	result[2] = (*this)[2] + other[2];
	result[3] = (*this)[3] + other[3];
	return result;
}

Cvector Cvector::operator-(const Cvector other)
{
	Cvector result;
	result[0] = (*this)[0] - other[0];
	result[1] = (*this)[1] - other[1];
	result[2] = (*this)[2] - other[2];
	result[3] = (*this)[3] - other[3];
	return result;
}

Cvector Cvector::operator/(const double value)
{
	Cvector result;
	result[0] = (*this)[0] / value;
	result[1] = (*this)[1] / value;
	result[2] = (*this)[2] / value;
	result[3] = (*this)[3] / value;
	return result;
}

Cvector Cvector::operator*(const double value)
{
	Cvector result;
	result[0] = (*this)[0] * value;
	result[1] = (*this)[1] * value;
	result[2] = (*this)[2] * value;
	result[3] = (*this)[3] * value;
	return result;
}

double& Cvector::operator[](const size_t index)
{
	
	return this->vec[index];
}

const double& Cvector::operator[](const size_t index) const
{
	
	return this->vec[index];
}

vector<double> Cvector::getVec() const
{
	return this->vec;
}

double Cvector::length()
{
	double X = (*this)[0];
	double Y = (*this)[1];
	double Z = (*this)[2];

	return sqrt(X * X + Y * Y + Z * Z);
}

Cvector Cvector::normalize()
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

Cvector Cvector::cross(Cvector first, Cvector second)
{
	Cvector result;
	result[0] = first[1] * second[2] - first[2] * second[1]; // new X = Y1 * Z2 - Z1 * Y2
	result[1] = first[2] * second[0] - first[0] * second[2]; // new Y = Z1 * X2 - X1 * Z2
	result[2] = first[0] * second[1] - first[1] * second[0]; // new Z = X1 * Y2 - Y1 * X2
	result[3] = 0;

	return result;
}

double Cvector::scalar(Cvector first, Cvector second)
{
	return first[0] * second[0] + first[1] * second[1] + first[2] * second[2];
}

double Cvector::angle(Cvector first, Cvector second)
{
	double angle = acos(scalar(first, second) / (first.length() * second.length()));
	angle *= 180 / M_PI;

	if (angle > 180)
	{
		angle -= 180;
	}

	return angle;
}

Cvector Cvector::operator*(Cmatrix matrix)
{
	Cvector result;
	for (size_t i = 0; i <= 3; i++)
	{
		for (size_t j = 0; j <= 3; j++)
		{
			result[i] = result[i] + matrix[j][i] * this->vec[j];
		}
	}
	return result;
}

bool Cvector::operator==(const Cvector& other) const
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

bool Cvector::operator!=(const Cvector& other) const
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

Cmatrix::Cmatrix()
{
	for (size_t i = 0; i <= 3; i++)
	{
		Cvector tmp;
		this->matrix.push_back(tmp);
	}
}

Cmatrix::Cmatrix(const Cmatrix& other)
{
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

Cmatrix::Cmatrix(Cmatrix&& other)
{
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}
}

Cmatrix::~Cmatrix()
{
	this->matrix.clear();
}

Cmatrix& Cmatrix::operator=(Cmatrix other)
{
	this->matrix.clear();
	for (size_t i = 0; i <= 3; i++)
	{
		this->matrix.push_back(other[i]);
	}

	return (*this);
}

Cvector& Cmatrix::operator[](const unsigned long index)
{
	return this->matrix[index];
}

const Cvector& Cmatrix::operator[](const unsigned long index) const
{
	return this->matrix[index];
}

Cmatrix Cmatrix::operator-()
{
	Cmatrix result(*this);
	result = result * (-1);
	return result;;
}

Cmatrix Cmatrix::operator*(const double value)
{
	Cmatrix result(*this);

	for (size_t i = 0; i <= 3; i++)
	{
		for (size_t j = 0; j <= 3; j++)
		{
			result[i][j] = result[i][j] * value;
		}
	}
	return result;
}

Cmatrix Cmatrix::operator*(const Cmatrix& other)
{
	Cmatrix result(*this);

	for (size_t i = 0; i <= 3; i++)
	{
		Cvector row((*this)[i]);
		for (size_t j = 0; j <= 3; j++)
		{
			Cvector column(other[0][j], other[1][j], other[2][j], other[3][j]);
			double sum = 0;
			for (size_t k = 0; k <= 3; k++)
				sum += row[k] * column[k];
			result[i][j] = sum;
		}
	}
	return result;
}

bool Cmatrix::inverse()
{
	Cmatrix result;

	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 0; j <= 3; ++j)
			result[i][j] = 0.0;

		result[i][i] = 1.0;
	}


	Cmatrix tmp(*this);

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

Cmatrix Cmatrix::transposition()
{
	Cmatrix result;
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

Cmatrix matrixrotationY(double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	Cmatrix transform;

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

Cmatrix matrixrotationX(double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	Cmatrix transform;

	transform[0][0] = 1;
	transform[0][1] = 0;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = cosa;
	transform[1][2] = sina;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = -sina;
	transform[2][2] = cosa;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

Cmatrix matrixrotationZ(double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	Cmatrix transform;

	transform[0][0] = cosa;
	transform[0][1] = sina;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = -sina;
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

Cmatrix matrixMove(double X, double Y, double Z)
{
	Cmatrix transform;

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