#pragma once
class Vector2ui
{
public:

	// x: 0
	// y: 1
	unsigned int vector[2] = {0, 0};

	Vector2ui() {};
	Vector2ui(unsigned int x, unsigned int y) { vector[0] = x; vector[1] = y;}
};

