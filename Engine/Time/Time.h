#include "glew.h"
#include "glfw3.h"

class Time
{
public:

	GLfloat lastUpdate = 0.f;

	Time();

	GLfloat getDeltaTime(); // Pega o valor do deltaTime
};

