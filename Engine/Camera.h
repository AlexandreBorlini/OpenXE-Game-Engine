#pragma once
#include "glew.h"
#include "Math/Matrix4.h"
#include "Transform.h"
#include <cmath>

class Camera
{
public:

	Camera() {}

	Matrix4 projection;
	Matrix4 view;

	void ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
	void perspective(GLfloat fov, GLfloat aspectRatio,GLfloat zNear, GLfloat zFar);

	void lookAt(Vector3 eye, Vector3 center, Vector3 up); // Olha para o center
	void lookAt(); // Olha para o center

	void setLookAtCenter(Vector3 center) { this->center = center; }	 // Define para onde a camera vai olhar
	void setDistanceFromCenter(float distance) { this->distanceFromCenter = distance; }	// Define a distância da câmera do centro 

	void orbitateVertically( float angle );				 // Orbita o centro verticalmente
	void orbitateHorizontally( float angle );			 // Orbita o centro horizontalmente
	void changeDistanceFromCenterBy(float distance);	 // Muda a distância até o centro por 'distance'

	Vector3 getCameraPosition();
	Vector2 getCameraHalfSize() { return cameraHalfSize; }
	Vector2 getCameraSize()     { return cameraHalfSize * 2; }

	float getLeftValue() { return leftValue; };
	float getBottomValue() { return bottomValue; };
	// FUNCAO DE MOVER CAMERA

private:

	// Pega a menor posição X (a esquerda) e menor Y (embaixo)
	// Usar apenas em modo ortho
	float leftValue;
	float bottomValue;

	Vector2 cameraHalfSize;

	float yaw = 0.f;				// Rotação y da câmera
	float pitch = 0.f;				// Rotação x da câmera
	float distanceFromCenter = 6.f; // Distância do centro

	Vector3 cameraPosition = Vector3(0.f, 0.f, 3.f);	// Posição mda câmera 
	Vector3 center =		 Vector3(0.f, .0f, 0.f);	// Para onde está olhando
	Vector3 up =			 Vector3(0.f, 1.f, 0.f);	// Vetor "pra cima" da câmera
};

