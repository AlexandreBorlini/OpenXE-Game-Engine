#pragma once
#include "glew.h"
#include "Math/Matrix4.h"
#include <cmath>

class Camera
{
public:

	Camera() {}

	Matrix4 projection;
	Matrix4 view;

	void ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

	void perspective(GLfloat fov, GLfloat aspectRatio,GLfloat zNear, GLfloat zFar);
	//void perspective02(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
};

