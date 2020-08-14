#pragma once
#include "Matrix4.h"

class Vector4
{
public:

	// Variaveis

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;

	// Constructors

	Vector4() {}
	Vector4(float vx, float vy, float vz, float vw) : x(vx), y(vy), z(vz), w(vw) {}
	Vector4(const Vector4 &vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

	// Funções

	Vector4 &operator = (const Vector4 &vector); // Operador "="
	
	Vector4 operator -(); // Nega os valores do vetor

	Vector4 operator + (const Vector4 &vector); // Operador "+" 
	Vector4 operator - (const Vector4 &vector) const; // Operador "-"
	Vector4 operator * (const Vector4 &vector); // Operador "*"
	Vector4 operator * (const Matrix4 &matrix); // Operador "*" com matrizes
	Vector4 operator / (const Vector4 &vector); // Operador "/"
		  
	Vector4 &operator += (const Vector4 &vector); // Operador "+=" 
	Vector4 &operator -= (const Vector4 &vector); // Operador "-="
	Vector4 &operator *= (const Vector4 &vector); // Operador "*="
	Vector4 &operator /= (const Vector4 &vector); // Operador "/="

	bool operator ==(const Vector4 &vector); // Operador "=="
	bool operator !=(const Vector4 &vector); // Operador "!="

	float length(); // Tamanho do vetor ( || vetor || )

	void zero(); // Zera os elementos dos vetors
	void normalize(); // Normalize o vetor
};

float vector4Distance(const Vector4 vector01, const Vector4 vector02); // Distância de dois Vector4
float vector4DotProduct(const Vector4 vector01, const Vector4 vector02); // Dot product de dois Vector4