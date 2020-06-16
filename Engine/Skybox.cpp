#include "Skybox.h"

Skybox::Skybox( vector<std::string> textures, float size )
{

	this->size = size;

	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );

	glBindVertexArray(VAO);
	glBindBuffer( GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	texture.loadCubemap( textures );

	shader.use();
	shader.setInt("texture_skybox", 0);
}

void Skybox::use( Camera cam ) {

	glDepthFunc(GL_LEQUAL);
	shader.use();

	shader.setMatrix4("projection", cam.projection);

	Matrix4 newView;
	for (int i = 0; i < 11; i++)
	{
		newView.matrix[i] = cam.view.matrix[i];
	}

	shader.setMatrix4("view", newView);

	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture.ID);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}