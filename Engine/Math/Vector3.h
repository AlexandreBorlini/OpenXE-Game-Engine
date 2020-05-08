#pragma once

#include <cmath>

class Vector3
{
public:

	// Variaveis

	float vector[3];

	// Constructor

	Vector3() {
		vector[0] = 0.f;
		vector[1] = 0.f;
		vector[2] = 0.f; }

	Vector3(float vx, float vy, float vz){
		vector[0] = vx;
		vector[1] = vy;
		vector[2] = vz; }

	Vector3(const Vector3 &vector){
		this->vector[0] = vector.vector[0];
		this->vector[1] = vector.vector[1];
		this->vector[2] = vector.vector[2]; }

	// Funções

	Vector3 &operator = (const Vector3 &vector); // Operador "="
	Vector3 operator -(); // Nega os valores do vetor

	Vector3 operator + (const Vector3 &vector); // Operador "+" 
	Vector3 operator - (const Vector3 &vector) const; // Operador "-"
	Vector3 operator * (const Vector3 &vector); // Operador "*"
	Vector3 operator / (const Vector3 &vector); // Operador "/"

	Vector3 &operator += (const Vector3 &vector); // Operador "+=" 
	Vector3 &operator -= (const Vector3 &vector); // Operador "-="
	Vector3 &operator *= (const Vector3 &vector); // Operador "*="
	Vector3 &operator /= (const Vector3 &vector); // Operador "/="

	bool operator ==(const Vector3 &vector); // Operador "=="
	bool operator !=(const Vector3 &vector); // Operador "!="

	float length(); // Tamanho do vetor ( || vetor || )

	void zero(); // Zera os elementos dos vetors
	void normalize(); // Normalize o vetor
};

float vector3Distance(const Vector3 vector01, const Vector3 vector02); // Distância de dois Vector3
float vector3DotProduct(const Vector3 vector01, const Vector3 vector02); // Dot product de dois Vector3
Vector3 vector3CrossProduct(const Vector3 vector01, const Vector3 vector02); // Cross product de dois Vector3