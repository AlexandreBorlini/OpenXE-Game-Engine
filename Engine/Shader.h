#pragma once

#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"

class Shader
{
public:

	// Constructor

	Shader() {};
	Shader(const GLchar* vertexArq, const GLchar* fragmentArq);

	// Variáveis

	GLuint ID; // ID do shader

	// Funções

	void use(); // Usar shader

	// Manda os valores para o shader

	void setBool( const std::string &name, bool value);
	void setFloat( const std::string &name, float value);
	void setInt( const std::string &name, int value);

	void setVector2( const std::string &name, Vector2 value);
	void setVector3( const std::string &name, Vector3 value);
	void setVector4( const std::string &name, Vector4 value);

	void setMatrix4( const std::string &name, Matrix4 value);
	void setMatrix4(const std::string &name, Matrix4 value,	GLuint shaderID); // Seta uma matrix para o shader referido
																			  // no ultimo argumento
	void setMatrix4(const std::string &name, glm::mat4 value);

private:

	void debugCompilation(GLuint shader, const char* actualShader);
	std::string getShaderInfoLog(GLuint shader);
};

