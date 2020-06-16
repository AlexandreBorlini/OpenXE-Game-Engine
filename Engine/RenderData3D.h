#pragma once
#include "glew.h"

class RenderData3D
{
public:

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	RenderData3D(GLfloat vertices[], GLuint indices[], int verticesSize, int indicesSize);
};

