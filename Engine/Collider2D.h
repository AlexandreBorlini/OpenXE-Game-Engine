#pragma once
#include "Math/Vector2.h"
class Collider2D
{

public:

	enum ColliderType
	{

		circle, box, polygon
	} type;

	bool isTrigger = false;

	Collider2D();
};

