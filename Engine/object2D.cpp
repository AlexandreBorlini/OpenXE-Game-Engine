#include "object2D.h"

// Criar o objeto
object2D::object2D(Camera *cam, GLfloat width, GLfloat height, GLfloat positionX, GLfloat positionY, GLfloat positionZ, const GLchar *texture)
{

	camera = cam;

	transform.changeHeightValue(height);
	transform.changeWidthValue (width);

	Shader shader("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
	this->shader = shader;

	width /= 2;
	height /= 2;

	// Definir as posições dos vetores
	GLfloat vertices[] = {

		// Posições               // Coordenadas da textura
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

// Renderizar o objeto
void object2D::use() {

	shader.use();

	shader.setMatrix4("projection", camera->projection);
	shader.setMatrix4("view", camera->view);

	Matrix4 m;

	m = transform.getTransformResultMatrix(); // Pega o conteúdo do transform e transforma em uma matriz
	shader.setMatrix4("transform", m);		  // para ser usado pelo shader

	render.useData();
	texture.use();

	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
}

void object2D::addRigidBody2D() {

	RigidBody *newRb = new RigidBody;
	newRb->setObjectTransform(&transform);

	components.push_back(newRb);
}

void object2D::addButton( Window *window ) {

	Button *newBtn = new Button(window, &transform, camera);

	components.push_back(newBtn);
}