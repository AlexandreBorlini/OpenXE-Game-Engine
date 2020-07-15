#pragma once
#include <iostream>
#include <glew.h>
#include "Shader.h"

class FrameBuffer
{
public:

	FrameBuffer();

	void defaultFrameBuffer(int screenWidth, int screenHeight);
	void depthMap(int shadowWidth, int shadowHeight);

	void active();

	void use();
	void prepareDepthMap(int shadowWidth, int shadowHeight);
	void useDepthMap(float nearPlane, float farPlane);

	GLuint texture;
private:

	GLuint VAO;
	GLuint VBO;
	
	GLuint FBO;
	GLuint RBO;
	
	
	void render();
	Shader shader = Shader("framebuffer_default.vs", "framebuffer_default.fs");
};

