#include "Button.h"

Button::Button()
{
}

Button::Button(Window *window, Transform *objTransform, Camera *camera)
{

	thisWindow = window;
	transform = objTransform;
	this->camera = camera;
}

bool Button::hasClicked() {

	if (thisWindow->getMouseClick()) {

		Vector2 mousePos = thisWindow->getMousePosition();
		
		Vector3 cameraPos      = camera->getCameraPosition();
		Vector2 cameraHalfSize = camera->getCameraHalfSize();

		// Remapear as coordinadas de tela para as 
		// coordinadas de camera
		mousePos.vector[0] = ((mousePos.vector[0] * (cameraHalfSize.vector[0] * 2)) / thisWindow->getWindowSize().vector[0]) - cameraHalfSize.vector[0];
		mousePos.vector[1] = -1 * (((mousePos.vector[1] * (cameraHalfSize.vector[1] * 2)) / thisWindow->getWindowSize().vector[1]) - cameraHalfSize.vector[1]);

		if (mousePos.vector[0] > transform->position.x - transform->getWidthOver2() && 
			mousePos.vector[0] < transform->position.x + transform->getWidthOver2() &&
			mousePos.vector[1] > transform->position.y - transform->getHeightOver2() &&
			mousePos.vector[1] < transform->position.y + transform->getHeightOver2()) {

			return true;
		}
	}

	return false;
}