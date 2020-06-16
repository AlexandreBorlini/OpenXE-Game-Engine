#pragma once

#include <iostream>
#include <glew.h>
#include <string>
#include <vector>

using namespace std;

class Texture2D
{
public:

	// Variáveis

	GLuint ID; // Número da textura

	int width; // Largura da textura
	int heigth; // Altura da textura
	int channels; // Canais da imagem

	// Constructors

	Texture2D() {};
	Texture2D(const GLchar* texturePath);

	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);
	void loadCubemap(vector<string> faces);

	void changeTexture(const GLchar* newTexturePath);
	void use();
};