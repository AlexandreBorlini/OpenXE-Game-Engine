#include "Transform.h"
#include "Component.h"
#include "BoxCollider2D.h"
#include <vector>

class RigidBody : public Component 

{
public:

	enum rbType{

		Dynamic, Kinematic, Static
	};
	
	int rigidbodyType = Dynamic;

	float mass = 1.f;
	Vector3 oldPosition;
	
	float acceleration = 9.8f;
	int orientation = 1;

	// Constructors ----
	RigidBody() {};
	RigidBody(int newRigidbodyType) { rigidbodyType = newRigidbodyType; }

	// Forças ----
	void setGravity(float newGravity) { gravity = newGravity; }
	void applyGravity( float deltaTime);							// Faz o cálculo da gravidade
	void addForce(Vector3 force, float deltaTime);					// Acelera um objeto de acordo com a força dada

	// Rigidbody ----
	void changeRigidbodyType( int newRigidbodyType ) { rigidbodyType = newRigidbodyType; };
	Vector3 getResultantVector( float deltaTime );

	// Transforms ----
	void move(Vector3 movement, double deltaTime); // Move em velocidade constante
	void move(Vector3 direction, float speed, double deltaTime, float acceleration, float accelerationLimit ); // Move com aceleração

	// Se precisar setar outro transform
	void setObjectTransform( Transform* newObjectTransform ) {

		objectTransform = newObjectTransform;
	}

	Vector3 velocity;

private:

	Transform *objectTransform;

	// Movimento ----
	float gravity = 9.8f;
	Vector3 resultantVector;
};