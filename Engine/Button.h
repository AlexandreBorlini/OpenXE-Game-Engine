#pragma once
#include "Rectangle.h"
#include "GLFW/glfw3.h"
#include "Component.h"
#include "Window.h"
#include "Camera.h"

class Button : public Component
{
public:

	Button();
	Button(Window *window, Transform *objTransform, Camera *camera);

	bool hasClicked();

private:
	
	Transform *transform;
	Window    *thisWindow;
	Camera    *camera;

	bool clicked = false;
};

