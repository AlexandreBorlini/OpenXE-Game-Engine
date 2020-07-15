#include "Time.h"

Time::Time(){}

double Time::getDeltaTime() {

	double deltaTime;

	deltaTime = glfwGetTime();
	deltaTime = deltaTime - lastUpdate;
	lastUpdate = glfwGetTime();

	return deltaTime;
}