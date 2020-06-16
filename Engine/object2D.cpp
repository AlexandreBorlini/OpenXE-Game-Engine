#include "object2D.h"


object2D::object2D(GLfloat width, GLfloat height, GLfloat positionX, GLfloat positionY, GLfloat positionZ, const GLchar *texture)
{

	Shader shader("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
	this->shader = shader;

	width /= 2;
	height /= 2;

	GLfloat vertices[] = {

		// Posições                                        // Coordenadas da textura
		 width,  height, 0.0f,    1.0f, 0.0f,
		 width, -height, 0.0f,    1.0f, 1.0f,
		-width, -height, 0.0f,    0.0f, 1.0f,
		-width,  height, 0.0f,    0.0f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 3, // Primeiro triângulo
		1, 2, 3  // Segundo triângulo
	};

	RenderData render(vertices, indices, sizeof(vertices), sizeof(indices));
	this->render = render;

	Texture2D newTexture(texture);
	this->texture = newTexture;

	transform.translate(positionX, positionY, positionZ);
}

void object2D::use(Camera cam) {

	shader.use();

	shader.setMatrix4("projection", cam.projection);
	shader.setMatrix4("view", cam.view);

	Matrix4 m;

	m = transform.getTransformResultMatrix(); // Pega o conteúdo do transform e transforma em uma matriz
	shader.setMatrix4("transform", m);		  // para ser usado pelo shader

	render.useData();
	texture.use();

	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
}