#include "Vector2.h"



void Vector2::zero() { // Zera o vetor

	vector[0] = 0.f;
	vector[1] = 0.f;
}

float Vector2::length() { // Length do vetor

	float result = pow(vector[0], 2) + pow(vector[1], 2);

	if (result > 0.f) // Não deixar dividir por zero
		return sqrt(result); // Retorna a raiz
	else
		return -1;
}

void Vector2::normalize() { // Normaliza o vetor

	float length = this->length();

	vector[0] /= length;
	vector[1] /= length;
}


// Operações com o vetor ---------------------------------------------------

Vector2 Vector2::operator-() { // Nega os elementos do vetor

	return Vector2(-vector[0], -vector[1]);
}

Vector2 &Vector2::operator = (const Vector2 &vector) { // Operador "="

	this->vector[0] = vector.vector[0];
	this->vector[1] = vector.vector[1];

	return *this;
}

Vector2 Vector2::operator + (const Vector2 &vector) { // Operador "+"

	return Vector2(this->vector[0] + vector.vector[0], this->vector[1] + vector.vector[1]);
}

Vector2 Vector2::operator - (const Vector2 &vector) const { // Operador "-"

	return Vector2(this->vector[0] - vector.vector[0], this->vector[1] - vector.vector[1]);
}

Vector2 Vector2::operator * (const Vector2 &vector) { // Operador "*"

	return Vector2(this->vector[0] * vector.vector[0], this->vector[1] * vector.vector[1]);
}

Vector2 Vector2::operator * (const float value) { // Operador "*"

	return Vector2(this->vector[0] * value, this->vector[1] * value);
}


Vector2 Vector2::operator / (const Vector2 &vector) { // Operador "/"

	return Vector2(this->vector[0] / vector.vector[0], this->vector[1] / vector.vector[1]);
}

Vector2 &Vector2::operator += (const Vector2 &vector) { // Operador "+="

	this->vector[0] += vector.vector[0];
	this->vector[1] += vector.vector[1];

	return *this;
}

Vector2 &Vector2::operator -= (const Vector2 &vector) { // Operador "-="

	this->vector[0] -= vector.vector[0];
	this->vector[1] -= vector.vector[1];

	return *this;
}

Vector2 &Vector2::operator *= (const Vector2 &vector) { // Operador "*="

	this->vector[0] *= vector.vector[0];
	this->vector[1] *= vector.vector[1];

	return *this;
}

Vector2 &Vector2::operator /= (const Vector2 &vector) { // Operador "/="

	this->vector[0] /= vector.vector[0];
	this->vector[1] /= vector.vector[1];

	return *this;
}

bool Vector2::operator == (const Vector2 &vector) { // Operador "=="

	return (this->vector[0] == vector.vector[0] && this->vector[1] == vector.vector[1]);
}

bool Vector2::operator != (const Vector2 &vector) { // Operador "!="

	return (this->vector[0] != vector.vector[0] && this->vector[1] != vector.vector[1]);
}

// Funções a parte ---------------------------------------------------------

float vector2Distance(const Vector2 vector01, const Vector2 vector02) { // Distância de dois Vector3

	float length;
	Vector2 resultVector;

	resultVector = vector01 - vector02;
	length = resultVector.length();

	return length;
}

float vector2DotProduct(const Vector2 vector01, const Vector2 vector02) {

	return (vector01.vector[0] * vector02.vector[0] + vector01.vector[1] * vector02.vector[1]);
}