#pragma once
#include "MatrixVector.h"

class Camera
{
public:
	Camera();

	Camera(GVector position, GVector direction);

	void rotateHorizontalSphere(double angle);

	void rotateVerticalSphere(double angle);

	GMatrix cameraview();

	GVector position;	/*!< Camera position */
	GVector target;		/*! Point on which looks camera */

private:
	GVector right;		/*! "X" axis of camera coordinate system */
	GVector up;			/*! "Y" axis of camera coordinate system */
	GVector direction;	/*! "Z" axis of camera coordinate system */

};
