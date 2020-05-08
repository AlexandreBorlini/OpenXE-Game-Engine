#include "Shader.h"


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) // Cria program
{
	// String dos shaders
	std::string vertexCode;
	std::string fragmentCode;

	// Ifstream dos shaders
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	// Procura por erros (!)
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//	Abrir os arquivos

		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		// Stringstream dos shaders

		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

		// Ler arquivo em buffer

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// Fechar os arquivos

		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Converter stream para string

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}

	// Caso tiver erro

	catch (std::ifstream::failure error)
	{

		std::cout << "ERRO NO SHADER: ARQUIVO NÃO PODE SER LIDO :: FUNÇÃO SHADER()" << std::endl;
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	// Compilar os shaders

	GLuint vertex;
	GLuint fragment;

	// Vertex shader

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);

	// Fragment shader

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);

	// Program

	ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	// Deletar os shader (depois de linkado não precisa mais)
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() { // Usa o shader

	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) { // Passar um bool

	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) {
														
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) { // Passar o float

	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVector2(const std::string &name, Vector2 value) { // Passar Vec2

	glUniform2f(glGetUniformLocation(ID, name.c_str()), value.vector[0], value.vector[1]);
}

void Shader::setVector3(const std::string &name, Vector3 value) { // Passar Vec3

	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.vector[0], value.vector[1], value.vector[2]);
}

void Shader::setVector4(const std::string &name, Vector4 value) { // Passar Vec4

	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const std::string &name, Matrix4 value) {

	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value.matrix[0]);
}

void Shader::setMatrix4(const std::string &name, Matrix4 value, GLuint shaderID) {

	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &value.matrix[0]);
}