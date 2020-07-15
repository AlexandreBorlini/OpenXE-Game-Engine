#include "Window.h"
/*
	0. Nao clicou
	1. Clicou
	2. Soltou
*/
int click = 0;

Vector2 mousePosition;

Window::Window(int width, int height, const char *windowName)
{

	this->width  = width;
	this->height = height;

	if (!glfwInit()) {

		std::cout << "GLFW NÃO INICIADO" << std::endl;
	}

	window = glfwCreateWindow(width, height, windowName, NULL, NULL);

	if (!window)
	{

		std::cout << "JANELA NAO INICIADA" << std::endl;
		glfwTerminate();
	}

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Habilitar blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Deixa a janela como contexto atual
	glfwMakeContextCurrent(window);

	inicializeFreeType();
}

void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {

	mousePosition.vector[0] = xPos;
	mousePosition.vector[1] = yPos;
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

		click = 1;
	}
	else 
		click = 0;

}

Vector2 Window::getMousePosition() {

	glfwSetCursorPosCallback(window, cursorPositionCallback);

	return mousePosition;
}

Vector2 Window::getWindowSize() {

	return Vector2( width, height );
}

int Window::getMouseClick() {

	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	
	return click;
}

void Window::inicializeFreeType() {

	// Iniciar freeType
	FT_Library freeTypeLibrary;

	if (FT_Init_FreeType(&freeTypeLibrary)) // checar por erros
	{

		std::cout << "ERRO::FREETYPE: Biblioteca nao conseguiu inicializar" << std::endl;
		return;
	}

	// criar uma face (fonte)
	FT_Face freeTypeFace;

	// checar erros na face
	if (FT_New_Face(freeTypeLibrary, "Arial.ttf", 0, &freeTypeFace))
	{
		std::cout << "ERRO::FREETYPE: Fonte nao foi encontrada" << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(freeTypeFace, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Para cada um da tabela ASCII
	for (unsigned int i = 0; i < 128; i++)
	{

		if (FT_Load_Char(freeTypeFace, i, FT_LOAD_RENDER)) {

			std::cout << "ERRO::FREETYPE:: Erro ao carregar Glyph" << std::endl;
			continue;
		}

		// Cria a textura do char atual
		unsigned int texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, 
					  freeTypeFace->glyph->bitmap.width, freeTypeFace->glyph->bitmap.rows,
					  0, GL_RED, GL_UNSIGNED_BYTE, freeTypeFace->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Cria um elemento da struct e armazena os dados
		Character character = {

			texture,
			Vector2ui(freeTypeFace->glyph->bitmap.width, freeTypeFace->glyph->bitmap.rows),
			Vector2ui(freeTypeFace->glyph->bitmap_left, freeTypeFace->glyph->bitmap_top),
			freeTypeFace->glyph->advance.x
		};

		// Insere no map
		characters.insert(std::pair<char, Character>(i, character));
	}

	FT_Done_Face(freeTypeFace);
	FT_Done_FreeType(freeTypeLibrary);
}