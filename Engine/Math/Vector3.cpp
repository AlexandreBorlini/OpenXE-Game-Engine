#include "Vector3.h"
#include <iostream>

void Vector3::zero() { // Zera o vetor

	vector[0] = 0.f;
	vector[1] = 0.f;
	vector[2] = 0.f;
}

float Vector3::length() { // Length do vetor

	float result = pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2);

	if (result > 0.f) // Não deixar dividir por zero
		return sqrt(result); // Retorna a raiz
	else
		return -1;
}

void Vector3::normalize() { // Normaliza o vetor

	float length = this->length();

	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}

// Operações com o vetor ---------------------------------------------------

Vector3 Vector3::operator-() { // Nega os elementos do vetor

	return Vector3(-vector[0], -vector[1], -vector[2]);
}

Vector3 &Vector3::operator = (const Vector3 &vector) { // Operador "="

	this->vector[0] = vector.vector[0];
	this->vector[1] = vector.vector[1];
	this->vector[2] = vector.vector[2];

	return *this;
}

Vector3 Vector3::operator + (const Vector3 &vector) { // Operador "+"

	return Vector3(this->vector[0] + vector.vector[0], this->vector[1] + vector.vector[1], this->vector[2] + vector.vector[2]);
}

Vector3 Vector3::operator + (const float value) { // Operador "+"

	return Vector3(this->vector[0] + value, this->vector[1] + value, this->vector[2] + value);
}

Vector3 Vector3::operator - (const Vector3 &vector) const { // Operador "-"

	return Vector3(this->vector[0] - vector.vector[0], this->vector[1] - vector.vector[1], this->vector[2] - vector.vector[2]);
}


Vector3 Vector3::operator * (const Vector3 &vector) { // Operador "*"

	return Vector3(this->vector[0] * vector.vector[0], this->vector[1] * vector.vector[1], this->vector[2] * vector.vector[2]);
}

Vector3 Vector3::operator * (float magnitude) { // Operador "*" com floats

	return Vector3(this->vector[0] * magnitude, this->vector[1] * magnitude, this->vector[2] * magnitude);
}


Vector3 Vector3::operator / (const Vector3 &vector) { // Operador "/"

	return Vector3(this->vector[0] / vector.vector[0], this->vector[1] / vector.vector[1], this->vector[2] / vector.vector[2]);
}

Vector3 Vector3::operator / (float magnitude) { // Operador "/"

	return Vector3(this->vector[0] / magnitude, this->vector[1] / magnitude, this->vector[2] / magnitude);
}


Vector3 &Vector3::operator += (const Vector3 &vector) { // Operador "+="

	this->vector[0] += vector.vector[0];
	this->vector[1] += vector.vector[1];
	this->vector[2] += vector.vector[2];

	return *this;
}

Vector3 &Vector3::operator -= (const Vector3 &vector) { // Operador "-="

	this->vector[0] -= vector.vector[0];
	this->vector[1] -= vector.vector[1];
	this->vector[2] -= vector.vector[2];

	return *this;
}

Vector3 &Vector3::operator *= (const Vector3 &vector) { // Operador "*="

	this->vector[0] *= vector.vector[0];
	this->vector[1] *= vector.vector[1];
	this->vector[2] *= vector.vector[2];

	return *this;
}

Vector3 &Vector3::operator /= (const Vector3 &vector) { // Operador "/="

	this->vector[0] /= vector.vector[0];
	this->vector[1] /= vector.vector[1];
	this->vector[2] /= vector.vector[2];

	return *this;
}

bool Vector3::operator == (const Vector3 &vector) { // Operador "=="

	return (this->vector[0] == vector.vector[0] && this->vector[1] == vector.vector[1] && this->vector[2] == vector.vector[2]);
}

bool Vector3::operator != (const Vector3 &vector) { // Operador "!="

	return (this->vector[0] != vector.vector[0] && this->vector[1] != vector.vector[1] && this->vector[2] != vector.vector[2]);
}

// Funções a parte ---------------------------------------------------------

float vector3Distance(const Vector3 vector01, const Vector3 vector02) { // Distância de dois Vector3

	float length;
	Vector3 resultVector;

	resultVector = vector01 - vector02;
	length = resultVector.length();

	return length;
}

float vector3DotProduct(const Vector3 vector01, const Vector3 vector02) {

	
	float x = vector01.vector[0] * vector02.vector[0];
	float y = vector01.vector[1] * vector02.vector[1];
	float z = vector01.vector[2] * vector02.vector[2];
		
	return x + y + z;
}

Vector3 vector3CrossProduct(const Vector3 vector01, const Vector3 vector02) {

	float cx, cy, cz;

	cx = (vector01.vector[1] * vector02.vector[2]) - (vector01.vector[2] * vector02.vector[1]);
	cy = (vector01.vector[2] * vector02.vector[0]) - (vector01.vector[0] * vector02.vector[2]);
	cz = (vector01.vector[0] * vector02.vector[1]) - (vector01.vector[1] * vector02.vector[0]);

	return Vector3(cx, cy, cz);
}