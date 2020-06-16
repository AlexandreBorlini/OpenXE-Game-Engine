#include "Box.h"

void Box::use(Camera cam) {

	shader.use();

	shader.setMatrix4("model", transform.getTransformResultMatrix());
	shader.setMatrix4("projection", cam.projection);
	shader.setMatrix4("view", cam.view);

	glm::mat4 view = glm::mat4(1.f);
	view[3][2] = -3.f;

	// Primeira luz
	glm::vec4 worldLight = glm::vec4(.0f, .0f, 3.0f, .0f);
	glUniform4fv(glGetUniformLocation(shader.ID, "Light[0].Position"), 1, &worldLight[0]);

	shader.setVector3( "Lights[0].Itensity", Vector3(0.f, 0.8f, 0.8f) );

	shader.setVector4( "Light[0].Position", Vector4(3.f, 5.0f, 0.f, 1.f) );
	shader.setVector3("Lights[0].Itensity", Vector3(0.8f, 0.f, 0.8f));

	shader.setVector3("Kd", Vector3(0.9f, 0.5f, 0.3f));
	shader.setVector3("Ka", Vector3(0.9f, 0.5f, 0.3f));
	shader.setVector3("Ks", Vector3(0.8f, 0.8f, 0.8f));

	shader.setFloat("Shininess", 2.0f);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Box::renderBoxData() {

	GLfloat widthDby2 = width / 2;
	GLfloat heightDby2 = height / 2;
	GLfloat lengthDby2 = length / 2;

	GLfloat vertices[] = {

		-length, -height, -width,  0.0f,  0.0f, -1.0f,
         length, -height, -width,  0.0f,  0.0f, -1.0f,
         length,  height, -width,  0.0f,  0.0f, -1.0f,
         length,  height, -width,  0.0f,  0.0f, -1.0f,
        -length,  height, -width,  0.0f,  0.0f, -1.0f,
        -length, -height, -width,  0.0f,  0.0f, -1.0f,
					
        -length, -height,  width,  0.0f,  0.0f,  1.0f,
         length, -height,  width,  0.0f,  0.0f,  1.0f,
         length,  height,  width,  0.0f,  0.0f,  1.0f,
         length,  height,  width,  0.0f,  0.0f,  1.0f,
        -length,  height,  width,  0.0f,  0.0f,  1.0f,
        -length, -height,  width,  0.0f,  0.0f,  1.0f,
					
        -length,  height,  width, -1.0f,  0.0f,  0.0f,
        -length,  height, -width, -1.0f,  0.0f,  0.0f,
        -length, -height, -width, -1.0f,  0.0f,  0.0f,
        -length, -height, -width, -1.0f,  0.0f,  0.0f,
        -length, -height,  width, -1.0f,  0.0f,  0.0f,
        -length,  height,  width, -1.0f,  0.0f,  0.0f,
					
         length,  height,  width,  1.0f,  0.0f,  0.0f,
         length,  height, -width,  1.0f,  0.0f,  0.0f,
         length, -height, -width,  1.0f,  0.0f,  0.0f,
         length, -height, -width,  1.0f,  0.0f,  0.0f,
         length, -height,  width,  1.0f,  0.0f,  0.0f,
         length,  height,  width,  1.0f,  0.0f,  0.0f,
				
        -length, -height, -width,  0.0f, -1.0f,  0.0f,
         length, -height, -width,  0.0f, -1.0f,  0.0f,
         length, -height,  width,  0.0f, -1.0f,  0.0f,
         length, -height,  width,  0.0f, -1.0f,  0.0f,
        -length, -height,  width,  0.0f, -1.0f,  0.0f,
        -length, -height, -width,  0.0f, -1.0f,  0.0f,
					
        -length,  height, -width,  0.0f,  1.0f,  0.0f,
         length,  height, -width,  0.0f,  1.0f,  0.0f,
         length,  height,  width,  0.0f,  1.0f,  0.0f,
         length,  height,  width,  0.0f,  1.0f,  0.0f,
        -length,  height,  width,  0.0f,  1.0f,  0.0f,
        -length,  height, -width,  0.0f,  1.0f,  0.0f
	};

	// Gerar buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bindar e preencher os buffers
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Fazer apontar para a posição correta

	// Coordenadas dos vértices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}