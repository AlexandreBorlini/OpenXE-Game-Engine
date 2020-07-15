#pragma once
#include <iostream>
#include <glew.h>
#include <map>
#include "GLFW/glfw3.h"
#include "Math/Vector2.h"
#include "Math/Vector2ui.h"
#include <ft2build.h>
#include FT_FREETYPE_H

//void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
void cursorEnterCallback(GLFWwindow *window, int entered);
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

class Window
{
public:

	Window(int width, int height, const char *windowName);

	GLFWwindow* window;

	Vector2 getMousePosition();
	Vector2 getWindowSize();
	
	int getMouseClick();

	struct Character {

		unsigned int ID;

		Vector2ui Size;
		Vector2ui Bearing;

		unsigned int Advance;
	};
	std::map<char, Character> characters;

private:

	int width  = 1;
	int height = 1;

	void inicializeFreeType();
};

