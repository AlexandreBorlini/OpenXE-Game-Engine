#pragma once
#include <cmath>

class Vector2
{
public:

	// Variaveis

	float vector[2]; // x : 0, y : 1
	
	// Constructor

	Vector2() {}
	Vector2(float vx, float vy) { vector[0] = vx;  vector[1] = vy; }
	Vector2(const Vector2 &vector) {
		this->vector[0] = vector.vector[0]; this->vector[1] = vector.vector[1];
	}

	// Funções


	float length(); // Tamanho do vetor ( || vetor || )

	void zero(); // Zera os elementos dos vetors
	void normalize(); // Normalize o vetor

	Vector2 &operator = (const Vector2 &vector); // Operador "="
	Vector2 operator -(); // Nega os valores do vetor
		  
	Vector2 operator + (const Vector2 &vector); // Operador "+" 
	Vector2 operator - (const Vector2 &vector) const; // Operador "-"
	Vector2 operator * (const Vector2 &vector); // Operador "*"
	Vector2 operator * (const float value);
	Vector2 operator / (const Vector2 &vector); // Operador "/"
		  
	Vector2 &operator += (const Vector2 &vector); // Operador "+=" 
	Vector2 &operator -= (const Vector2 &vector); // Operador "-="
	Vector2 &operator *= (const Vector2 &vector); // Operador "*="
	Vector2 &operator /= (const Vector2 &vector); // Operador "/="

	bool operator ==(const Vector2 &vector); // Operador "=="
	bool operator !=(const Vector2 &vector); // Operador "!="

private:


};

float vector2Distance(const Vector2 vector01, const Vector2 vector02); // Distância de dois Vector3
float vector2DotProduct(const Vector2 vector01, const Vector2 vector02); // Dot product de dois Vector3