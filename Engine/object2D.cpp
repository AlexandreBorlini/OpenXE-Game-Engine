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

		0, 1, 2, // Primeiro triângulo
		0, 3, 2  // Segundo triângulo
	};

	RenderData render(vertices, indices, sizeof(vertices), sizeof(indices));
	this->render = render;

	Texture2D newTexture(texture, true);
	this->texture = newTexture;
	
	transform.translate(positionX, positionY, positionZ);
}

// Caso a textura tiver ou não alfa
object2D::object2D(Camera *cam, GLfloat width, GLfloat height, GLfloat positionX, GLfloat positionY, GLfloat positionZ, const GLchar *texture, bool useAlfa) {

	camera = cam;

	transform.changeHeightValue(height);
	transform.changeWidthValue(width);

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

		0, 1, 2, // Primeiro triângulo
		0, 3, 2  // Segundo triângulo
	};

	RenderData render(vertices, indices, sizeof(vertices), sizeof(indices));
	this->render = render;

	Texture2D newTexture(texture, useAlfa);
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

	if(colliders.size() > 0)
		static_cast<BoxCollider2D*>(colliders[0])->applyTransformations(m);

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

void object2D::collision(object2D *otherObject) {

	RigidBody *thisRb = getComponent<RigidBody>();

	// Se não tiver rigidbody então não faz o cálculo
	if (thisRb == NULL)
		return;

	RigidBody *otherObjectRb = otherObject->getComponent<RigidBody>();

	// Trata ele como static se não tiver rigidbody ou se o rigidbody
	// estiver setado como static
	if (otherObject->colliders.size() > 0) {

		Vector2 MTV;

		if (otherObjectRb == NULL || otherObjectRb->rigidbodyType == RigidBody::Static) {

			for (int i = 0; i < colliders.size(); i++)
			{

				if (!colliders[i]->isTrigger) {

					for (int j = 0; j < otherObject->colliders.size(); j++)
					{

						if (!otherObject->colliders[i]->isTrigger) {

							switch (otherObject->colliders[i]->type) {

							case Collider2D::box:

								MTV = static_cast<BoxCollider2D*>(colliders[i])->collisionBox2DBox2D(*static_cast<BoxCollider2D*>(otherObject->colliders[i]));
								getComponent<RigidBody>()->move(Vector3(MTV.vector[0], MTV.vector[1], 0), 1);

								break;
							}
						}
					}
				}
			}
		}
		else {

			std::cout << "OTHER COLLISION TYPE" << std::endl;
		}
	}
	else {

	}
}

void object2D::addBoxCollider2D() {

	BoxCollider2D *newBoxCollider = new BoxCollider2D(&transform);
	newBoxCollider->type = BoxCollider2D::box;

	colliders.push_back(newBoxCollider);
}

void object2D::addBoxCollider2D(float top, float bottom, float left, float right) {

	BoxCollider2D *newBoxCollider = new BoxCollider2D(top, bottom, left, right);
	newBoxCollider->type = BoxCollider2D::box;

	colliders.push_back(newBoxCollider);
}