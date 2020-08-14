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

		Vector2 mousePos   = thisWindow->getMousePosition();
		Vector2 windowSize = thisWindow->getWindowSize();
		
		Vector2 mouseNormalizedPosition;
		mouseNormalizedPosition = mousePos / windowSize;
		mouseNormalizedPosition.vector[1] = -(mouseNormalizedPosition.vector[1] - 1);

		// Redefinir mousePos para o resultado final
		mousePos = camera->getCameraSize() * mouseNormalizedPosition;
		
		if(camera->getLeftValue() > 0)
			mousePos.vector[0] += camera->getLeftValue();
		else
			mousePos.vector[0] -= abs(camera->getLeftValue());
		
		if(camera->getBottomValue() > 0)
			mousePos.vector[1] += abs(camera->getBottomValue());
		else
			mousePos.vector[1] -= abs(camera->getBottomValue());

		if (mousePos.vector[0] > transform->position.x - transform->getWidthOver2() && 
			mousePos.vector[0] < transform->position.x + transform->getWidthOver2() &&
			mousePos.vector[1] > transform->position.y - transform->getHeightOver2() &&
			mousePos.vector[1] < transform->position.y + transform->getHeightOver2()) {

			return true;
		}
	}

	return false;
}