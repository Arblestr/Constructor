#pragma once
#include "MatrixVector.h"

class Camera
{
public:
	Camera();

	Camera(Cvector position, Cvector direction);

	void rotateHorizontalSphere(double angle);

	void rotateVerticalSphere(double angle);

	Cmatrix cameraview();

	Cvector position;	/*!< Camera position */
	Cvector target;		/*! Point on which looks camera */

private:
	Cvector right;		/*! "X" axis of camera coordinate system */
	Cvector up;			/*! "Y" axis of camera coordinate system */
	Cvector direction;	/*! "Z" axis of camera coordinate system */
};
