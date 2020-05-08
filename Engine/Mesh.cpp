#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures)
{

	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setMesh(); // Inicializa os buffers (o que o renderData faz)
}

void Mesh::setMesh() {

	// Criar os buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Preencher o VBO com as coordenadas do vértice
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// Preencher o EBO com a ordem dos vértices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Setar os attribPointer

	glEnableVertexAttribArray(0); // Posição do Vertice
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1); // Posição do Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//glEnableVertexAttribArray(1); // Posição da textura
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

	//glEnableVertexAttribArray(3); // Posição da tangente
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	//glEnableVertexAttribArray(4); // Posição da bitangente
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

	glBindVertexArray(0);
}

void Mesh::draw(Shader shader) {


	GLuint diffuseNmr = 1;  // Contador de texturas difusas
	GLuint specularNmr = 1;	// Contador de texturas especulares

	for (GLuint i = 0; i < textures.size(); i++)
	{

		glActiveTexture(GL_TEXTURE0 + i); // Ativa a textura de número i

		string number;
		string name = textures[i].type; // type = String do struct texture que guarda o tipo

		if (name == "texture_diffuse")  // Se for tipo difusa
			number = to_string(diffuseNmr++);
		
		else if(name == "texture_specular") // Se for do tipo especular
			number = to_string(specularNmr++);

		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}

	// renderizar
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);			// Volta a apontar pro default
	glActiveTexture(GL_TEXTURE0);
}