#pragma once
#include "BoxCollider2D.h"
#include <vector>

class Physics
{
public:

	Physics();

	static bool vector2Overlap(Vector2 v01, Vector2 v02);
	static double getOverlapValue(Vector2 v01, Vector2 v02);
	static Vector2 getProjectionVector2(Vector2 axis, std::vector<Vector2> objVertices);

	static std::vector<Vector2> getNormals(std::vector<Vector2> axis, std::vector<Vector2> colliderVertices);
	static bool testOverlapAxis2D(std::vector<Vector2> axes, std::vector<Vector2> vertices01,
															 std::vector<Vector2> vertices02);
};

