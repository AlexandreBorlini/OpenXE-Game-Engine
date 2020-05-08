#pragma once
#include "glew.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <cmath>

class Quaternion
{
public:

	GLfloat w = 1.f;
	GLfloat x = 0.f;
	GLfloat y = 0.f;
	GLfloat z = 0.f;

	Quaternion();
	Quaternion(GLfloat qw, GLfloat qx, GLfloat qy, GLfloat qz) : w(qw), x(qx), y(qy), z(qz) {}

	void identity() { w = 1.f, x = y = z = 0.f; } // Volta o quaternion identidade
	void negate() { w *= -1; x *= -1; y *= -1; z *= -1; } // Nega o quaternion

	void normalize() { const float normalizeMult = 1.f / sqrt(x*x + y * y + z * z + w * w);
	x *= normalizeMult; y *= normalizeMult; z *= normalizeMult; w *= normalizeMult;
	}

	void rotateAboutX(GLfloat angle);
	void rotateAboutY(GLfloat angle);
	void rotateAboutZ(GLfloat angle);
	void rotateAboutAxis(Vector3 v, GLfloat angle);

	Quaternion &operator *(const Quaternion &q);
	Quaternion &operator *=(const Quaternion &q);
};