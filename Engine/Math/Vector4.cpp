#include "Vector4.h"
#include <math.h>


void Vector4::zero() { // Zera o vetor

	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 0.f;
}

float Vector4::length() { // Length do vetor

	float result = pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2);

	if (result > 0.f) // Não deixar dividir por zero
		return sqrt(result); // Retorna a raiz
	else
		return 0;
}

void Vector4::normalize() { // Normaliza o vetor

	float length = this->length();

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}


// Operações com o vetor ---------------------------------------------------

Vector4 Vector4::operator-() { // Nega os elementos do vetor

	return Vector4(-x, -y, -z, -w);
}

Vector4 &Vector4::operator = (const Vector4 &vector) { // Operador "="

	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;

	return *this;
}

Vector4 Vector4::operator + (const Vector4 &vector) { // Operador "+"

	return Vector4(x + vector.x, y + vector.y, z + vector.z, vector.w);
}

Vector4 Vector4::operator - (const Vector4 &vector) const { // Operador "-"

	return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

Vector4 Vector4::operator * (const Vector4 &vector) { // Operador "*"

	return Vector4(x * vector.x, y * vector.y, z * vector.z, w * vector.w);
}

Vector4 Vector4::operator * (const Matrix4 &matrix) { // Operador "*"

	Vector4 result;

	result.x = (matrix.matrix[0] * x) + (matrix.matrix[4] * y) + (matrix.matrix[8]  * z) + (matrix.matrix[12] * w);
	result.y = (matrix.matrix[1] * x) + (matrix.matrix[5] * y) + (matrix.matrix[9]  * z) + (matrix.matrix[13] * w);
	result.z = (matrix.matrix[2] * x) + (matrix.matrix[6] * y) + (matrix.matrix[10] * z) + (matrix.matrix[14] * w);
	result.w = (matrix.matrix[3] * x) + (matrix.matrix[7] * y) + (matrix.matrix[11] * z) + (matrix.matrix[15] * w);

	return result;
}

Vector4 Vector4::operator / (const Vector4 &vector) { // Operador "/"

	return Vector4(x / vector.x, y / vector.y, z / vector.z , w / vector.w);
}

Vector4 &Vector4::operator += (const Vector4 &vector) { // Operador "+="

	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;

	return *this;
}

Vector4 &Vector4::operator -= (const Vector4 &vector) { // Operador "-="

	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

Vector4 &Vector4::operator *= (const Vector4 &vector) { // Operador "*="

	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w += vector.w;

	return *this;
}

Vector4 &Vector4::operator /= (const Vector4 &vector) { // Operador "/="

	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;

	return *this;
}

bool Vector4::operator == (const Vector4 &vector) { // Operador "=="

	return (x == vector.x && y == vector.y && z == vector.z && w == vector.w);
}

bool Vector4::operator != (const Vector4 &vector) { // Operador "!="

	return (x != vector.x && y != vector.y && z != vector.z && w != vector.w);
}

// Funções a parte ---------------------------------------------------------

float vector4Distance(const Vector4 vector01, const Vector4 vector02) { // Distância de dois Vector3

	float length;
	Vector4 resultVector;

	resultVector = vector01 - vector02;
	length = resultVector.length();

	return length;
}

float vector4DotProduct(const Vector4 vector01, const Vector4 vector02) {

	return (vector01.x * vector02.x + vector01.y * vector02.y + vector01.z * vector02.z + vector01.w * vector02.w);
}