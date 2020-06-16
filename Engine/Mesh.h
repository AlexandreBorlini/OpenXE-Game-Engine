#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "glew.h"

#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include "Render/Texture2D.h"
#include "Shader.h"

using namespace std;

struct Vertex { // Informações de um vértice

	Vector3 position;
	Vector3 normal;
	Vector2	textureCoordinates;

	Vector3 tangent;
	Vector3 bitangent; // Cross product da tangent e normal
};

struct Texture { // Informações de uma textura

	unsigned int ID;

	string type;
	string path;
};

class Mesh
{
public:

	// Data
	vector<Vertex> vertices; // Vetor de struct de vertices
	vector<GLuint> indices; // Vetor de índices
	vector<Texture> textures; // Vetor de struct de textures

	GLuint VAO;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures); // Constructor
	void draw(Shader shader);

private:

	GLuint VBO, EBO;

	void setMesh();
};

