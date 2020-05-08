#include "glew.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"

class Box
{
public:

	Transform transform;

	Box(GLfloat newLength, GLfloat newHeight, GLfloat newWidth) : length(newLength), height(newHeight), width(newWidth) 
	{
		shader = Shader("bookVertexShader.vs", "bookFragmentShader.fs");
		renderBoxData();
	}

	Shader shader;
	void use(Camera cam);

private:


	GLuint VAO;
	GLuint VBO;

	GLfloat length;
	GLfloat height;
	GLfloat width;

	void renderBoxData();
};

