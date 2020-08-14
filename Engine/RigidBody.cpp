#include "RigidBody.h"

void RigidBody::applyGravity( float deltaTime ) {

	if (rigidbodyType == 0) {

		 velocity.vector[1] += -(gravity * deltaTime);
	}
}


void RigidBody::addForce(Vector3 force, float deltaTime) {

	velocity += Vector3((force / mass)) * deltaTime;
}


Vector3 RigidBody::getResultantVector(float deltaTime) {

	applyGravity(deltaTime);

	return velocity;
}

void RigidBody::move( Vector3 movement, double deltaTime ) {

	movement.vector[0] *= deltaTime;
	movement.vector[1] *= deltaTime;
	movement.vector[2] *= deltaTime;

	// Atualizar a velocidade
	velocity = movement;

	objectTransform->translate(movement);
}

void RigidBody::move( Vector3 direction, float speed, double deltaTime, float acceleration, float velocityLimit ) {

	// Mover objeto com aceleração acelerando 
	// Botar limite de velocidade
}