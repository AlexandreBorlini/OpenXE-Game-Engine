#include "RigidBody.h"
#include "Rectangle.h"
#include "Camera.h"


class object2D
{
public:

	object2D(GLfloat width, GLfloat height, GLfloat positionX, GLfloat positionY, GLfloat positionZ, const GLchar *texture);

	void use(Camera cam);


private:

	RigidBody rigidbody;
	Transform transform;
	
	Shader shader;
	RenderData render;
	Texture2D texture;
};

