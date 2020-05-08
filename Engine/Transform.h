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

		GLfloat x = 0;
		GLfloat y = 0;
		GLfloat z = 0;
	}position;

	Transform() {}

	void translate( GLfloat x, GLfloat y, GLfloat z); // Trnaslação
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

	Matrix4 getTransformResultMatrix(); // Pega o transform e transforma numa matriz para ser usada no shader

private:

	GLfloat lenght = 1;
	GLfloat height = 1;
	GLfloat width = 1;


	Quaternion q;
	Matrix4 quaternionToMatrix(); // Pega o quaternion da classe e transforma em matriz pro shader
	GLfloat degreesToRadians(GLfloat angle);
};