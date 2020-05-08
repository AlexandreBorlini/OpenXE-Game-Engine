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

	if (result > 0.f) // N�o deixar dividir por zero
		return sqrt(result); // Retorna a raiz
}

void Vector4::normalize() { // Normaliza o vetor

	float length = this->length();

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}


// Opera��es com o vetor ---------------------------------------------------

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

// Fun��es a parte ---------------------------------------------------------

float vector4Distance(const Vector4 vector01, const Vector4 vector02) { // Dist�ncia de dois Vector3

	float distance;
	float length;
	Vector4 resultVector;

	resultVector = vector01 - vector02;
	length = resultVector.length();

	return length;
}

float vector4DotProduct(const Vector4 vector01, const Vector4 vector02) {

	return (vector01.x * vector02.x + vector01.y * vector02.y + vector01.z * vector02.z + vector01.w * vector02.w);
}