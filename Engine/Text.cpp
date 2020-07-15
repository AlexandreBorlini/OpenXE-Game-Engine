#include "Text.h"

Text::Text(Window *window, float x, float y, float z, Camera *cam, std::string newText)
{
	
	transform.goTo(x, y, z);

	text = newText;
	this->window = window;
	camera = cam;
	shader = Shader("shaders/text_default.vs", "shaders/text_default.fs");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Armazenar como dinamico para poder mudar o tamanho depois
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	center.vector[0] = 0;

	std::string::const_iterator i;
	for (i = text.begin(); i != text.end(); i++)
	{

		Window::Character ch = window->characters[*i];
		center.vector[0] += (ch.Advance >> 6) * transform.getScale().vector[0];
	}
}

void Text::use( ) {
	
	shader.use();
	shader.setMatrix4("projection", camera->projection);
	shader.setMatrix4("view", camera->view);
	shader.setMatrix4("transform", transform.getTransformResultMatrix());

	Vector3 color = Vector3(1.f, 1.f, 1.f);

	shader.setVector3("textColor", color);
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	
	float x = -center.vector[0]/2;
	float y = 0.f;

	float scaleX = transform.getScale().vector[0];
	float scaleY = transform.getScale().vector[1];
	
	std::string::const_iterator i;
	for (i = text.begin(); i != text.end(); i++)
	{
		
		Window::Character ch = window->characters[*i];

		float xPos = x + ch.Bearing.vector[0] * scaleX;
		float yPos = y - (ch.Size.vector[1] - ch.Bearing.vector[1]) * scaleY;

		float width  = (ch.Size.vector[0] * scaleX);
		float height = (ch.Size.vector[1] * scaleY);

		float vertices[6][4] = {

			{ xPos	        , yPos + height, 0.f, 0.f },
			{ xPos	        , yPos         , 0.f, 1.f },
			{ xPos + width	, yPos         , 1.f, 1.f },

			{ xPos	        , yPos + height, 0.f, 0.f },
			{ xPos + width  , yPos         , 1.f, 1.f },
			{ xPos + width	, yPos + height, 1.f, 0.f }
		};
		
		glBindTexture(GL_TEXTURE_2D, ch.ID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6) * scaleX;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}