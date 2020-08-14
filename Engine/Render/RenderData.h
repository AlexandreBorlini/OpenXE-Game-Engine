#pragma once
#include <iostream>
#include <glew.h>

class RenderData
{
public:

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	RenderData() {};
	RenderData( GLfloat vertices[], GLuint indices[], int verticesSize, int indicesSize);

	void useData();
};

