#include "Matrix4.h"
#include <iostream>

Matrix4::Matrix4(GLfloat n) {

	matrix[0] = n;
	matrix[5] = n;
	matrix[10] = n;
	matrix[15] = n;
}


void Matrix4::transpose() { // Faz a transposta

	/*
		matriz normal:
		0  1   2  3
		4  5   6  7
		8  9  10 11
		12 13 14 15

		matriz transposta:
		0 4  8 12
		1 5  9 13
		2 6 10 14
		3 7 11 15
	*/

	Matrix4 newMatrix(1.f);

	*this = newMatrix;

	matrix[1] = newMatrix.matrix[4];
	matrix[2] = newMatrix.matrix[8];
	matrix[3] = newMatrix.matrix[12];
	matrix[4] = newMatrix.matrix[1];
	matrix[5] = newMatrix.matrix[5];
	matrix[6] = newMatrix.matrix[9];
	matrix[7] = newMatrix.matrix[13];
	matrix[8] = newMatrix.matrix[2];
	matrix[9] = newMatrix.matrix[6];
	matrix[10] = newMatrix.matrix[10];
	matrix[11] = newMatrix.matrix[14];
	matrix[12] = newMatrix.matrix[3];
	matrix[13] = newMatrix.matrix[7];
	matrix[14] = newMatrix.matrix[11];
	matrix[15] = newMatrix.matrix[15];
}


Matrix4 Matrix4::identity() { // Retorna a identidade

	Matrix4 newMatrix(1.f);
	return newMatrix;
}

// Operators ----------------------------------------------------

Matrix4 &Matrix4::operator=(const Matrix4 &m) { // =

	for (int i = 0; i < 15; i++)
		matrix[i] = m.matrix[i];

	return *this;
}

bool Matrix4::operator ==(const Matrix4 &m) { // ==

	for (int i = 0; i < 15; i++) 

		if (matrix[i] != m.matrix[i])
			return false;
	
	return true;
}

bool Matrix4::operator !=(const Matrix4 &m) { // !=

	for (int i = 0; i < 15; i++)

		if (matrix[i] != m.matrix[i])
			return true;

	return false;
}

Matrix4 Matrix4::operator + (Matrix4 m) { // +

	for (int i = 0; i < 16; i++)
		 m.matrix[i] += matrix[i];

	return (m);
}

Matrix4 &Matrix4::operator += (const Matrix4 &m) { // +=

	for (int i = 0; i < 16; i++)
		matrix[i] += m.matrix[i];

	return *this;
}

Matrix4 Matrix4::operator- (Matrix4 m) { // -


	for (int i = 0; i < 16; i++)
		m.matrix[i] = matrix[i] - m.matrix[i];

	return (m);
}

Matrix4 Matrix4::operator -= ( Matrix4 m) { // -=

	for (int i = 0; i < 16; i++)
		matrix[i] -= m.matrix[i];

	return *this;
}

Matrix4 Matrix4::operator * (Matrix4 m) { // *

	/*
		m00 m01 m02 m03		m00 m01 m02 m03
		m04 m05 m06 m07	 x	m04 m05 m06 m07
		m08 m09 m10 m11		m08 m09 m10 m11
		m12 m13 m14 m15		m12 m13 m14 m15
	*/

	Matrix4 result;

	result.matrix[0] = matrix[0] * m.matrix[0] + matrix[1] * m.matrix[4] + matrix[2] * m.matrix[8] + matrix[3] * m.matrix[12];
	result.matrix[1] = matrix[0] * m.matrix[1] + matrix[1] * m.matrix[5] + matrix[2] * m.matrix[9] + matrix[3] * m.matrix[13];
	result.matrix[2] = matrix[0] * m.matrix[2] + matrix[1] * m.matrix[6] + matrix[2] * m.matrix[10] + matrix[3] * m.matrix[14];
	result.matrix[3] = matrix[0] * m.matrix[3] + matrix[1] * m.matrix[7] + matrix[2] * m.matrix[11] + matrix[3] * m.matrix[15];

	result.matrix[4] = matrix[4] * m.matrix[0] + matrix[5] * m.matrix[4] + matrix[6] * m.matrix[8] + matrix[7] * m.matrix[12];
	result.matrix[5] = matrix[4] * m.matrix[1] + matrix[5] * m.matrix[5] + matrix[6] * m.matrix[9] + matrix[7] * m.matrix[13];
	result.matrix[6] = matrix[4] * m.matrix[2] + matrix[5] * m.matrix[6] + matrix[6] * m.matrix[10] + matrix[7] * m.matrix[14];
	result.matrix[7] = matrix[4] * m.matrix[3] + matrix[5] * m.matrix[7] + matrix[6] * m.matrix[11] + matrix[7] * m.matrix[15];

	result.matrix[8] = matrix[8] * m.matrix[0] + matrix[9] * m.matrix[4] + matrix[10] * m.matrix[8] + matrix[11] *  m.matrix[12];
	result.matrix[9] = matrix[8] * m.matrix[1] + matrix[9] * m.matrix[5] + matrix[10] * m.matrix[9] + matrix[11] *  m.matrix[13];
	result.matrix[10] =matrix[8] * m.matrix[2] + matrix[9] * m.matrix[6] + matrix[10] * m.matrix[10] + matrix[11] * m.matrix[14];
	result.matrix[11] =matrix[8] * m.matrix[3] + matrix[9] * m.matrix[7] + matrix[10] * m.matrix[11] + matrix[11] * m.matrix[15];

	result.matrix[12] = matrix[12] * m.matrix[0] + matrix[13] * m.matrix[4] + matrix[14] * m.matrix[8] + matrix[15] * m.matrix[12];
	result.matrix[13] = matrix[12] * m.matrix[1] + matrix[13] * m.matrix[5] + matrix[14] * m.matrix[9] + matrix[15] * m.matrix[13];

	result.matrix[14] = matrix[12] * m.matrix[2] + matrix[13] * m.matrix[6] + matrix[14] * m.matrix[10] + matrix[15] * m.matrix[14];

	result.matrix[14] /= 10;

	result.matrix[15] = matrix[12] * m.matrix[3] + matrix[13] * m.matrix[7] + matrix[14] * m.matrix[11] + matrix[15] * m.matrix[15];

	return result;
}

Matrix4 &Matrix4::operator *= (const Matrix4 &m) {// *=

	*this = *this * m;
	return *this;
}