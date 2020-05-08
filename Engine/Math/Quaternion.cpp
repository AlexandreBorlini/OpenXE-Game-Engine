#include "Quaternion.h"

Quaternion::Quaternion() { }

void Quaternion::rotateAboutX(GLfloat angle) { // Rotaciona pelo eixo X

	w = cos(angle * 0.5f);
	x = sin(angle * 0.5f);
	y = 0.f;
	z = 0.f;
}

void Quaternion::rotateAboutY(GLfloat angle) { // Rotaciona pelo eixo Y

	w = cos(angle * 0.5f);
	x = 0.f;
	y = sin(angle * 0.5f);
	z = 0.f;
}

void Quaternion::rotateAboutZ(GLfloat angle) { // Rotaciona pelo eixo Z

	w = cos(angle * 0.5f);
	x = 0.f;
	y = 0.f;
	z = sin(angle * 0.5f);
}

void Quaternion::rotateAboutAxis(Vector3 v, GLfloat angle) { // Rotaciona por um eixo arbitrário

	v.normalize(); // Precisa normalizar

	w = cos(angle * 0.5f);
	x = v.vector[0] * (angle * 0.5f);
	y = v.vector[1] * (angle * 0.5f);
	z = v.vector[2] * (angle * 0.5f);
}

Quaternion &Quaternion::operator*(const Quaternion &q) {

	Quaternion result;

	result.w = q.w*w - q.x*x - q.y*y - q.z*z;
	result.x = q.w*x +	q.x*w + q.z*y - q.y*z;
	result.y = q.w*y + q.y*w + q.x*z - q.z*x;
	result.z = q.w*z + q.z*w + q.y*x - q.x*y;

	return result;
}

Quaternion &Quaternion::operator*=(const Quaternion &q) {

	*this = *this * q;
	return *this;
}