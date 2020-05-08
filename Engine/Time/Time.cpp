#include "Time.h"

Time::Time(){}

GLfloat Time::getDeltaTime() {

	GLfloat deltaTime;

	deltaTime = glfwGetTime();
	deltaTime = deltaTime - lastUpdate;
	lastUpdate = glfwGetTime();

	return deltaTime;
}