#include "Physics.h"

Physics::Physics() {}

// Retorna se entrou no outro ou não
bool Physics::vector2Overlap(Vector2 v01, Vector2 v02) {

	// 0 min
	// 1 max

	if (v01.vector[0] < v02.vector[1] && v01.vector[1] > v02.vector[0])
		return true;

	return false;
}


// Retorna o quanto um vetor entrou no outro
double Physics::getOverlapValue(Vector2 v01, Vector2 v02) {

	double max;
	double min;

	// Pegar o menor dos pontos maiores
	if (v01.vector[1] > v02.vector[1]) max = v02.vector[1];
	else max = v01.vector[1];

	// Pegar o menor dos pontos menores
	if (v01.vector[0] > v02.vector[0]) min = v01.vector[0];
	else min = v02.vector[0];

	double result = max - min;
	return result;
}


// Projeta os pontos do vetor no axis e retorna o ponto minimo e maximo
Vector2 Physics::getProjectionVector2(Vector2 axis, std::vector<Vector2> objVertices) {

	float min = vector2DotProduct(axis, objVertices[0]);
	float max = min;

	for (int i = 1; i < objVertices.size(); i++)
	{

		float p = vector2DotProduct(axis, objVertices[i]);

		// Pegar os pontos maximo e minimo
		if (p < min) min = p;
		if (p > max) max = p;
	}

	return Vector2(min, max);
}

// Pega as Normals do objeto
std::vector<Vector2> Physics::getNormals(std::vector<Vector2> axis, std::vector<Vector2> colliderVertices) {

	int numberOfVertices = colliderVertices.size();

	std::vector<Vector2> result;

	// Axis do objeto atual
	for (int i = 0; i < colliderVertices.size(); i++)
	{

		Vector2 p01 = colliderVertices[i];
		Vector2 p02 = colliderVertices[i + 1 == numberOfVertices ? 0 : i + 1];

		Vector2 edge = p01 - p02;

		// Pegar a normal usando a perpendicular
		float save = edge.vector[0];

		edge.vector[0] = edge.vector[1];
		edge.vector[1] = -save;

		edge.normalize();

		result.push_back(edge);
	}

	return result;
}

bool Physics::testOverlapAxis2D(std::vector<Vector2> axes, std::vector<Vector2> vertices01, std::vector<Vector2> vertices02) {

	for (int i = 0; i < 4; i++)
	{

		Vector2 axis = axes[i];

		Vector2 proj01 = getProjectionVector2(axis, vertices01);
		Vector2 proj02 = getProjectionVector2(axis, vertices02);

		// Se não se colidirem retorna falso
		if (!vector2Overlap(proj01, proj02)) {

			return false;
		}
	}

	return true;
}