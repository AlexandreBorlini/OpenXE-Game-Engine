#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(float up, float down, float left, float right)
{

	vertices[0] = Vector2(left, up);
	vertices[1] = Vector2(right, up);

	vertices[2] = Vector2(right, down);
	vertices[3] = Vector2(left, down);

	width  = right - left;
	height = up - down;

	type = box; // Seta o tipo como box
}

// Ajeita o colisor conforme o transform
BoxCollider2D::BoxCollider2D(Transform *objTransform)
{

	float left  = objTransform->position.x - objTransform->getWidthOver2();
	float right = objTransform->position.x + objTransform->getWidthOver2();
	float up    = objTransform->position.y + objTransform->getHeightOver2();
	float down  = objTransform->position.y - objTransform->getHeightOver2();

	vertices[0] = Vector2(left, up);
	vertices[1] = Vector2(right, up);

	vertices[2] = Vector2(right, down);
	vertices[3] = Vector2(left, down);

	width  = objTransform->getWidthOver2();
	height = objTransform->getHeightOver2();

	parentObjTransform = objTransform;

	type = box; // Seta o tipo como box
}

void BoxCollider2D::applyTransformations(Matrix4 objTransformMatrix) {

	Vector4 untransformedVertices;
	Vector4 result;

	// Aplicar no 0 (superior esquerdo) ------
	untransformedVertices = Vector4(-width, height, 0, 1);
	result = untransformedVertices * objTransformMatrix;

	vertices[0] = Vector2(result.x, result.y);

	// 1 -----
	untransformedVertices = Vector4(width, height, 0, 1);
	result = untransformedVertices * objTransformMatrix;

	vertices[1] = Vector2(result.x, result.y);

	// 2 -----
	untransformedVertices = Vector4(width, -height, 1, 1);
	result = untransformedVertices * objTransformMatrix;

	vertices[2] = Vector2(result.x, result.y);

	// 3 -----
	untransformedVertices = Vector4(-width, -height, 1, 1);
	result = untransformedVertices * objTransformMatrix;

	vertices[3] = Vector2(result.x, result.y);

	type = box; // Seta o tipo como box

}

// Trigger Collision 2D usando SAT Box-Box
bool BoxCollider2D::triggerCollisionBox2DBox2D(BoxCollider2D otherObject) {

	// Normals
	std::vector<Vector2> axis01;
	std::vector<Vector2> axis02;

	// Axis do objeto atual
	axis01 = Physics::getNormals(axis01, vertices);
	axis02 = Physics::getNormals(axis02, otherObject.vertices);

	// Testar colisão com axis desse objeto
	if (!Physics::testOverlapAxis2D(axis01, vertices, otherObject.vertices))
		return false;

	if (!Physics::testOverlapAxis2D(axis02, vertices, otherObject.vertices))
		return false;

	return true;
}

Vector2 BoxCollider2D::collisionBox2DBox2D(BoxCollider2D otherObject) {

	double overlap = INFINITY;
	Vector2 smallest;

	// Normals
	std::vector<Vector2> axis01;
	std::vector<Vector2> axis02;

	// Axis do objeto atual
	axis01 = Physics::getNormals(axis01, vertices);
	axis02 = Physics::getNormals(axis02, otherObject.vertices);

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	// Testar colisão com axis desse objeto
	for (int i = 0; i < 4; i++)
	{

		Vector2 axis = axis01[i];

		Vector2 proj01 = Physics::getProjectionVector2(axis, vertices);
		Vector2 proj02 = Physics::getProjectionVector2(axis, otherObject.vertices);

		// Se não se colidirem retorna falso
		if (!Physics::vector2Overlap(proj01, proj02)) {

			return Vector2(0, 0);
		}
		else { // Se houver colisão

			// Pegar o quanto de oberlap
			double o = Physics::getOverlapValue(proj01, proj02);

			if (o < overlap) {

				overlap = o;
				smallest = axis;
			}
		}
	}

	// Testar com o axis do outro
	for (int i = 0; i < 4; i++)
	{

		Vector2 axis = axis02[i];

		Vector2 proj01 = Physics::getProjectionVector2(axis, vertices);
		Vector2 proj02 = Physics::getProjectionVector2(axis, otherObject.vertices);

		// Se não se colidirem retorna falso
		if (!Physics::vector2Overlap(proj01, proj02)) {

			return Vector2(0, 0);
		}
		else { // Se houver colisão

			// Pegar o quanto de oberlap
			double o = Physics::getOverlapValue(proj01, proj02);

			if (o < overlap) {

				overlap = o;
				smallest = axis;
			}
		}
	}

	// Ver se estão apontando para a mesma direção, caso não, inverte
	bool pointingSameDirection = vector2DotProduct(Vector2(parentObjTransform->position.x, parentObjTransform->position.y) - Vector2(otherObject.parentObjTransform->position.x, otherObject.parentObjTransform->position.y), smallest) < 0;

	if (pointingSameDirection) 
		smallest = -smallest;

	// Pega o vetor resultado e move ESTE objeto
	Vector2 MTV = Vector2(smallest.vector[0] * overlap, smallest.vector[1] * overlap);

	return MTV;
}

void BoxCollider2D::move(Vector2 movement) {

	for (int i = 0; i < vertices.size(); i++)
		vertices[i] += movement;
	
}