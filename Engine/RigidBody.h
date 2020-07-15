#include "Transform.h"
#include "Component.h"

class RigidBody : public Component 

{
public:
	
	float acceleration = 9.8f;
	int orientation = 1;

	RigidBody() {};
	RigidBody(int newRigidbodyType) { rigidbodyType = newRigidbodyType; }

	// Forças ----
	void setGravity(float newGravity) { gravity = newGravity; }
	void applyGravity( float deltaTime);							// Faz o cálculo da gravidade
	void addForce(Vector3 force, float deltaTime);					// Acelera um objeto de acordo com a força dada

	// Rigidbody ----
	void changeRigidbodyType( int newRigidbodyType ) { rigidbodyType = newRigidbodyType; };
	void changeColliderType(int newColliderType)     { colliderType  = newColliderType;   };

	Vector3 getResultantVector( float deltaTime );

	// Mover ----

	void move( Vector2 direction, float speed, double deltaTime); // Move em velocidade constante
	void move( Vector2 direction, float speed, double deltaTime, float acceleration, float accelerationLimit ); // Move com aceleração

	// Colisão ----
	bool triggerCollisionAABB(Transform *thisObject, Transform *otherObject);
	bool collisionAABB (Transform *thisObject, Transform *otherObject);

	void setObjectTransform( Transform* newObjectTransform ) {

		objectTransform = newObjectTransform;
	}

	/*
		0. Dinâmico
		1. Kinematic
		2. Estático
	*/
	int rigidbodyType = 0;

	float mass = 1.f;

private:

	Transform *objectTransform;

	/*
		0. Trigger
		1. Colisão normal
	*/
	int colliderType = 1;

	float gravity = 9.8f;

	Vector3 velocity;
	Vector3 resultantVector;
};