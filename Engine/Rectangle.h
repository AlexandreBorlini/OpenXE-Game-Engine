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

	Rectangle(GLfloat width, GLfloat height, GLfloat positionX, GLfloat positionY, GLfloat positionZ, const GLchar *texture);

	void applyTransform();
	void use(Camera camera);

private:

	Shader shader;
	RenderData render;
};
