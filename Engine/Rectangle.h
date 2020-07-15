#pragma once
#include "Shader.h"
#include "Transform.h"
#include "Render/RenderData.h"
#include "Render/Texture2D.h"
#include "Math/Matrix4.h"
#include "Camera.h"

class Rectangle
{
public:

	Texture2D texture;
	Transform transform;

	Rectangle() {};
	Rectangle(GLfloat width, GLfloat height, GLfloat positionX, GLfloat positionY, GLfloat positionZ, const GLchar *texture);

	void use(Camera camera);

	Shader shader;

private:

	RenderData render;
};

