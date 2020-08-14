#pragma once
#include "Component.h"
#include "Transform.h"
#include "Collider2D.h"
#include "Physics.h"
#include <vector>

class BoxCollider2D : public Collider2D
{

public:

	BoxCollider2D(){}
	BoxCollider2D(Transform *objTransform);
	BoxCollider2D(float up, float down, float left, float right);

	void applyTransformations(Matrix4 objTransformMatrix);
	void move(Vector2 movement);

	/*
		0 ------ 1
		|        |
		|        |
		3 -------2
	*/
	std::vector <Vector2> vertices = { Vector2(-1, 1), Vector2(1, 1),
									   Vector2(1, -1), Vector2(-1, -1) };

	float width;
	float height;

	Transform *parentObjTransform;

	bool triggerCollisionBox2DBox2D(BoxCollider2D otherObject);

	// Ve se está colidindo e retorna o vetor de overlap (MTV)
	Vector2 collisionBox2DBox2D(BoxCollider2D otherObject);
};