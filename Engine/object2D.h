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
	object2D(Camera *cam, GLfloat width, GLfloat height, GLfloat positionX, GLfloat positionY, GLfloat positionZ, const GLchar *texture, bool useAlfa);

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

		return NULL;
	}

	// Colisão ----

	// Colisores
	void addBoxCollider2D();
	void addBoxCollider2D(float top, float bottom, float left, float right);
	
	void collision(object2D *otherObject);

	Transform transform;
	Texture2D texture;

	std::vector<Collider2D*> colliders;
private:

	std::vector<Component*>  components;

	Shader     shader;
	RenderData render;
	Camera    *camera;
};