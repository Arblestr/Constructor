#include "stdafx.h"
#include "Camera.h"

//////
Cmatrix matrixrotation(double X, double Y, double Z, double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	Cmatrix transform;

	transform[0][0] = cosa + (1 - cosa) * X * X;
	transform[0][1] = (1 - cosa) * X * Y + sina * Z;
	transform[0][2] = (1 - cosa) * X * Z - sina * Y;
	transform[0][3] = 0;

	transform[1][0] = (1 - cosa) * X * Y - sina * Z;
	transform[1][1] = cosa + (1 - cosa) * Y * Y;
	transform[1][2] = (1 - cosa) * Z * Y + sina * X;
	transform[1][3] = 0;

	transform[2][0] = (1 - cosa) * X * Z + sina * Y;
	transform[2][1] = (1 - cosa) * Y * Z - sina * X;
	transform[2][2] = cosa + (1 - cosa) * Z * Z;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	return transform;
}

Cmatrix matrixmovement(double X, double Y, double Z)
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

Cmatrix matrixscale(double k)
{
	Cmatrix transform;

	transform[0][0] = k;
	transform[0][1] = 0;
	transform[0][2] = 0;
	transform[0][3] = 0;

	transform[1][0] = 0;
	transform[1][1] = k;
	transform[1][2] = 0;
	transform[1][3] = 0;

	transform[2][0] = 0;
	transform[2][1] = 0;
	transform[2][2] = k;
	transform[2][3] = 0;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = k;

	return transform;
}
//////

Camera::Camera()
{
}

Camera::Camera(Cvector position, Cvector target)
{
	this->position = position;
	this->target = target;

	this->right[0] = 1;
	this->right[1] = 0;
	this->right[2] = 0;
	this->right[3] = 0;

	this->up[0] = 0;
	this->up[1] = 1;
	this->up[2] = 0;
	this->up[3] = 0;

	this->direction = this->position - this->target;
}

void Camera::rotateVerticalSphere(double angle)
{
	Cmatrix rotation = matrixrotation(this->right[0], this->right[1], this->right[2], angle);
	this->up = this->up * rotation;
	this->direction = this->direction * rotation;

	Cmatrix movementtoorigin = matrixmovement(this->target[0], this->target[1], this->target[2]);
	Cmatrix movementback = matrixmovement(-this->target[0], -this->target[1], -this->target[2]);
	this->position = this->position * movementback * rotation * movementtoorigin;
}

void Camera::rotateHorizontalSphere(double angle)
{
	Cmatrix rotation = matrixrotation(this->up[0], this->up[1], this->up[2], angle);
	this->right = this->right * rotation;
	this->direction = this->direction * rotation;

	Cmatrix movementtoorigin = matrixmovement(this->target[0], this->target[1], this->target[2]);
	Cmatrix movementback = matrixmovement(-this->target[0], -this->target[1], -this->target[2]);
	this->position = this->position * movementback * rotation * movementtoorigin;
}

Cmatrix Camera::cameraview()
{
	this->direction.normalize();
	if (this->direction == this->right || this->direction == this->right * (-1))
	{
		this->right = Cvector::cross(this->up, this->direction).normalize();
		this->up = Cvector::cross(this->direction, this->right).normalize();
	}
	else
	{
		this->up = Cvector::cross(this->direction, this->right).normalize();
		this->right = Cvector::cross(this->up, this->direction).normalize();
	}
	double X = -Cvector::scalar(this->right, this->position);
	double Y = -Cvector::scalar(this->up, this->position);
	double Z = -Cvector::scalar(this->direction, this->position);

	Cvector t(X, Y, Z, 1);

	Cmatrix view;
	for (int i = 0; i < 4; i++)
	{
		view[i][0] = this->right[i];
		view[i][1] = this->up[i];
		view[i][2] = this->direction[i];
		view[i][3] = t[i];
	}

	view.transposition();
	return view;
}