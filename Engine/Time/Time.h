#include "glew.h"
#include "glfw3.h"

class Time
{
public:

	double lastUpdate = 0.f;

	Time();

	double getDeltaTime(); // Pega o valor do deltaTime
};

