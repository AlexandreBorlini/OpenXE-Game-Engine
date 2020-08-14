#pragma once
#include <iostream>
#include "Math/Vector2ui.h"
#include <glew.h>
#include "Shader.h"
#include "Window.h"	
#include "Camera.h"

class Text
{

public:

	Text(Window *window, float x, float y, float z, Camera *cam, std::string newText);
	Text(Window *window, float x, float y, float z, Camera *cam, std::string newText, Vector3 color);

	void use();

	void changeColor(Vector3 newColor);
	void changeText(std::string newText);

	void reCenterize(int mode);

	Transform transform;

private:

	std::string text;

	Vector2 center;
	Vector3 color;

	Window *window;
	Camera *camera;

	Shader shader;
	unsigned int VBO;
	unsigned int VAO;
};

