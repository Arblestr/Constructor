#include "stdafx.h"
#include "Camera.h"

//////
GMatrix matrixrotation(double X, double Y, double Z, double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	GMatrix transform;

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

GMatrix matrixmovement(double X, double Y, double Z)
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

GMatrix matrixscale(double k)
{
	GMatrix transform;

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

Camera::Camera(GVector position, GVector target)
{
	this->position = position;
	this->target = target;

	this->right[0] = 1;
	this->right[1] = 0;
	this->right[2] = 0;
	this->right[3] = 1;

	this->up[0] = 0;
	this->up[1] = 1;
	this->up[2] = 0;
	this->up[3] = 1;

	this->direction[0] = 0;
	this->direction[1] = 0;
	this->direction[2] = 1;
	this->direction[3] = 1;
}

void Camera::rotateVerticalSphere(double angle)
{
	GMatrix rotation = matrixrotation(this->right[0], this->right[1], this->right[2], angle);
	this->up = this->up * rotation;
	this->direction = this->direction * rotation;
	GMatrix movement = matrixmovement(this->target[0], this->target[1], this->target[2]);
	this->position = this->position * (-movement) * rotation * movement;
}

void Camera::rotateHorizontalSphere(double angle)
{
	GMatrix rotation = matrixrotation(this->up[0], this->up[1], this->up[2], angle);
	this->right = this->right * rotation;
	this->direction = this->direction * rotation;
	GMatrix movement = matrixmovement(this->target[0], this->target[1], this->target[2]);
	this->position = this->position * (-movement) * rotation * movement;
}

GMatrix Camera::cameraview()
{
	this->right = GVector::cross(this->up, this->direction).normalize();
	this->up = GVector::cross(this->direction, this->right).normalize();
	this->direction.normalize();

	double X = -GVector::scalar(this->right, this->position);
	double Y = -GVector::scalar(this->up, this->position);
	double Z = -GVector::scalar(this->direction, this->position);

	GMatrix view;

	for (int i = 0; i < 3; i++)
	{
		view[i][0] = this->right[i];
		view[i][1] = this->up[i];
		view[i][2] = this->direction[i];
		view[i][3] = 1;
	}
	view[3][0] = X;
	view[3][1] = Y;
	view[3][2] = Z;
	view[3][3] = 1;

	return view;
}