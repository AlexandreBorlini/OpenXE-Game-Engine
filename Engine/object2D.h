#include "RigidBody.h"
#include "Rectangle.h"
#include "Camera.h"
#include "Component.h"
#include "Window.h"
#include "Button.h"

class object2D
{
public:

	object2D(Camera *cam, GLfloat width, GLfloat height, GLfloat positionX, GLfloat positionY, GLfloat positionZ, const GLchar *texture);

	void use();

	// Adiciona um rigidbody ao objeto
	void addRigidBody2D();
	void addButton( Window *window );

	template <typename classType>
	classType* getComponent() { 
	
		for (unsigned int i = 0; i < components.size(); i++)
		{

			if(static_cast<const classType*>(components[i]))
				return (classType*)components[i];
		}

		std::cout << "COMPONENTE NÃO EXISTE" << std::endl;
		return NULL;
	}

	Transform transform;
	Texture2D texture;

private:

	std::vector<Component*> components;

	Shader     shader;
	RenderData render;
	Camera    *camera;
};

