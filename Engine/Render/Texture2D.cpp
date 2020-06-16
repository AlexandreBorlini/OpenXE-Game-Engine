#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(const GLchar* texturePath)
{

	glGenTextures(1, &ID); // Gera textura
	glBindTexture(GL_TEXTURE_2D, ID); // Liga a textura ao GL_TEXTURE

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Setar o Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Setar o X
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Quando longe é linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Quando perto é nearest

	unsigned char *image = stbi_load(texturePath, &width, &heigth, &channels, 4);

	if (image) { // Se loadImage funcionar

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); // Prende a textura ao objeto
		glGenerateMipmap(GL_TEXTURE_2D); // Gera o mipmap
	}

	else
		std::cout << "ERRO NA TEXTURA: NÃO CARREGOU A IMAGEM :: FUNCAO TEXTURE2D()" << std::endl;

	stbi_image_free(image);
}

void Texture2D::use() {

	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::changeTexture(const GLchar* texturePath) {

	glBindTexture(GL_TEXTURE_2D, ID); // Liga a textura ao GL_TEXTURE

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Setar o Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Setar o X
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Quando longe é linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Quando perto é nearest

	unsigned char *image = stbi_load(texturePath, &width, &heigth, &channels, 4);

	if (image) { // Se loadImage funcionar

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); // Prende a textura ao objeto
		glGenerateMipmap(GL_TEXTURE_2D); // Gera o mipmap
	}

	else
		std::cout << "ERRO NA TEXTURA: NÃO CARREGOU A IMAGEM :: CLASSE TEXTURE2D()" << std::endl;

	stbi_image_free(image);
}

unsigned int Texture2D::TextureFromFile(const char *path, const string &directory, bool gamma)
{

	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

// Carrega as 6 texturas do cubemap de uma vez
void Texture2D::loadCubemap(vector<string> faces) {

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	for (unsigned int i = 0; i < faces.size(); i++)
	{

		unsigned char *data = stbi_load( faces[i].c_str(), &width, &heigth, &channels, 0 );
		if (data) {

			glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
			stbi_image_free(data);
		}
		else {

			std::cout << "FALHA AO CARREGAR CUBEMAP:: FUNÇÃO LOADCUBEMAP \n PATH: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}