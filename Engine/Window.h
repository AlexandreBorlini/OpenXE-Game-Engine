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

	bool closed() { return glfwWindowShouldClose(window); }; // Se a janela foi fechada

	void begin();
	void processInput();

	// Inputs
	bool pressedA() { return glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS; }
	bool pressedB() { return glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS; }
	bool pressedC() { return glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS; }
	bool pressedD() { return glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS; }
	bool pressedE() { return glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS; }
	bool pressedF() { return glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS; }
	bool pressedG() { return glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS; }
	bool pressedH() { return glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS; }
	bool pressedI() { return glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS; }
	bool pressedJ() { return glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS; }
	bool pressedK() { return glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS; }
	bool pressedL() { return glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS; }
	bool pressedM() { return glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS; }
	bool pressedN() { return glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS; }
	bool pressedO() { return glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS; }
	bool pressedP() { return glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS; }
	bool pressedQ() { return glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS; }
	bool pressedR() { return glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS; }
	bool pressedS() { return glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS; }
	bool pressedT() { return glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS; }
	bool pressedU() { return glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS; }
	bool pressedV() { return glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS; }
	bool pressedW() { return glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS; }
	bool pressedX() { return glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS; }
	bool pressedY() { return glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS; }
	bool pressedZ() { return glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS; }
private:

	int width  = 1;
	int height = 1;

	void inicializeFreeType();
};

