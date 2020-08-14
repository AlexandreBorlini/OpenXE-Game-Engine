#include "Render/Texture2D.h"
#include "Shader.h"
#include "Camera.h"
class Skybox
{
public:

	Skybox( vector<std::string> textures, float size );

	void use( Camera cam );

	Texture2D texture;

	Shader shader = Shader("shaders/skybox.vs", "shaders/skybox.fs");
private:

	float size;

	GLuint VAO;
	GLuint VBO;

	float data[108] = {

		-size,  size, -size,
		-size, -size, -size,
		 size, -size, -size,
		 size, -size, -size,
		 size,  size, -size,
		-size,  size, -size,
		 		  		
		-size, -size,  size,
		-size, -size, -size,
		-size,  size, -size,
		-size,  size, -size,
		-size,  size,  size,
		-size, -size,  size,

		 size, -size, -size,
		 size, -size,  size,
		 size,  size,  size,
		 size,  size,  size,
		 size,  size, -size,
		 size, -size, -size,
			 
		-size, -size,  size,
		-size,  size,  size,
		 size,  size,  size,
		 size,  size,  size,
		 size, -size,  size,
		-size, -size,  size,
	 		
		-size,  size, -size,
		 size,  size, -size,
		 size,  size,  size,
		 size,  size,  size,
		-size,  size,  size,
		-size,  size, -size,
		 		
		-size, -size, -size,
		-size, -size,  size,
		 size, -size, -size,
		 size, -size, -size,
		-size, -size,  size,
		 size, -size,  size
	};
};

