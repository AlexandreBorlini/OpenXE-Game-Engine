#pragma once
#include "glew.h"

#include "Math/Matrix4.h"
#include "Math/Quaternion.h"

#include "Math/Matrix4.h"
#include <cmath>

#include "Shader.h"

class Transform
{

public:

	struct position {

		GLfloat x = 0.f;
		GLfloat y = 0.f;
		GLfloat z = 0.f;
	}position;

	Transform() {}

	void translate( GLfloat x, GLfloat y, GLfloat z); // Translação
	void translate( Vector3 vector );
	void translateLocal(GLfloat nx, GLfloat ny, GLfloat nz);

	void goTo( GLfloat x, GLfloat y, GLfloat z); // Vai para a posição indicada

	// Rotação global
	void worldRotationX(GLfloat angle);
	void worldRotationY(GLfloat angle);
	void worldRotationZ(GLfloat angle);

	// Rotação local
	void localRotationX(GLfloat angle);
	void localRotationY(GLfloat angle);
	void localRotationZ(GLfloat angle);

	void scale( GLfloat x, GLfloat y, GLfloat z); // Escala conforme o dado
	void scale(GLfloat n);

	Vector3 getScale();

	// Pega os valore do menor e maior vértice
	// vector[0] é o Vértice menor e vector[1] o maior
	Vector2 getLeftAndRightX();
	Vector2 getLeftAndRightY();

	void changeHeightValue(float newHeight);
	void changeWidthValue (float newWidth);

	float getHeightOver2();
	float getWidthOver2();

	Matrix4 getTransformResultMatrix(); // Pega o transform e transforma numa matriz para ser usada no shader

private:

	// A escala do objeto atual, começa como 1 por padrão
	GLfloat scaleX = 1.f;
	GLfloat scaleY = 1.f;
	GLfloat scaleZ = 1.f;

	// O comprimento e a largura do objeto / 2
	GLfloat widthOver2  = 0.5f;
	GLfloat heightOver2 = 0.5f;

	Quaternion q;

	Matrix4 quaternionToMatrix();    // Pega o quaternion da classe e transforma em matriz pro shader

	GLfloat degreesToRadians(GLfloat angle);
};