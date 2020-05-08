#pragma once
#include "glew.h"
#include <cmath>

class Matrix4
{
public:

	GLfloat matrix[16] = {

		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	Matrix4() {}
	Matrix4(GLfloat n);

	Matrix4 identity(); // Retorna a matriz a identidade
	void transpose(); // Cria a matriz transposta
	void inverse();

	Matrix4 &operator = (const Matrix4 &matrix); // Operador "="
	
	Matrix4 operator + (Matrix4 matrix); // Operador "+" 
	Matrix4 operator - (Matrix4 matrix); // Operador "-"
	Matrix4 operator * (Matrix4 matrix); // Operador "*"
	
	Matrix4 &operator += (const Matrix4 &matrix); // Operador "+=" 
	Matrix4 operator -= (Matrix4 matrix); // Operador "-="
	Matrix4 &operator *= (const Matrix4 &matrix); // Operador "*="

	bool operator ==(const Matrix4 &matrix); // Operador "=="
	bool operator !=(const Matrix4 &matrix); // Operador "!="
};

