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

// Checar colisão
bool RigidBody::triggerCollisionAABB(Transform *thisObject, Transform *otherObject) {

	Vector2 thisObjectPoints  = thisObject->getLeftAndRightX();
	Vector2 otherObjectPoints = otherObject->getLeftAndRightX();

	// Se colidir no X axis
	if (thisObjectPoints.vector[1] >= otherObjectPoints.vector[0] &&
		thisObjectPoints.vector[0] <= otherObjectPoints.vector[1]) {

		thisObjectPoints  =  thisObject->getLeftAndRightY();
		otherObjectPoints =  otherObject->getLeftAndRightY();

		// Se colidir no Y axis
		if (thisObjectPoints.vector[1] >= otherObjectPoints.vector[0] &&
			thisObjectPoints.vector[0] <= otherObjectPoints.vector[1]) {

			return true;
		}
	}

	return false;
}

bool RigidBody::collisionAABB(Transform *thisObject, Transform *otherObject) {

	Vector2 thisObjectPointsX = thisObject->getLeftAndRightX();
	Vector2 otherObjectPointsX = otherObject->getLeftAndRightX();

	// Se colidir no X axis
	if (thisObjectPointsX.vector[1] >= otherObjectPointsX.vector[0] &&
		thisObjectPointsX.vector[0] <= otherObjectPointsX.vector[1]) {

		Vector2 thisObjectPointsY = thisObject->getLeftAndRightY();
		Vector2 otherObjectPointsY = otherObject->getLeftAndRightY();

		// Se colidir no Y axis
		if (thisObjectPointsY.vector[1] >= otherObjectPointsY.vector[0] &&
			thisObjectPointsY.vector[0] <= otherObjectPointsY.vector[1]) {

			// A colisão ocorreu

			// Tirar o aspect ratio para caso o outro objeto for retangular
			float otherObjectAspectRatio = otherObject->getWidthOver2() / otherObject->getHeightOver2();

			// Detectar de qual lado
			// Se este estiver a direita
			if (otherObject->position.x + (otherObject->getWidthOver2() / otherObjectAspectRatio) < thisObject->position.x ) {

				// fazer voltar a diferença no lado em que está
				std::cout << "ESTA NA DIREITA" << std::endl;
			}

			return true;
		}
	}

	return false;
}

void RigidBody::move( Vector2 direction, float speed, double deltaTime ) {


}

void RigidBody::move( Vector2 direction, float speed, double deltaTime, float acceleration, float accelerationLimit ) {


}