#include "Camera.h"

void Camera::TranslateUpDown(float delta)
{
	vPos += vUp * delta;
}

void Camera::TranslateLeftRight(float delta)
{
	vPos += vRight * delta;
}

void Camera::TranslateFwdBack(float delta)
{
	vPos -= vDir * delta;
}

void Camera::TiltUpDown(float ang)
{
	vDir = vDir * Matrix(ROT_AXIS_ANGLE, vRight, ang);
	setOrientAndPosition(Vect(0, 1, 0), vPos - vDir, vPos);
}

void Camera::TurnLeftRight(float ang)
{
	vDir = vDir * Matrix(ROT_Y, ang);
	setOrientAndPosition(Vect(0, 1, 0), vPos - vDir, vPos);
}