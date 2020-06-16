#include "Camera.h"

void Camera::ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) { // Camera ortogonal

	projection.identity();

	GLfloat width = right - left;
	GLfloat height = top - bottom;

	// Parte de escala da matriz

	projection.matrix[0] = 2 / (width);					// 2/width pois a tela no Opengl vai de -1 a 1
	projection.matrix[5] = 2 / (height);				// Portanto o tamanho é de 2 unidades
	projection.matrix[10] = -2 / (zFar - zNear);		// Negativo pois a câmera sempre aponta para o Z negativo (oposto do world) 

	// Parte de translação

	projection.matrix[12] = - (right + left)/ (width);				// Trazer a câmera para o centro X (para o centro ficar no 0)
	projection.matrix[13] = - (top + bottom) / (height);			// Para o centro Y
	projection.matrix[14] = - (zFar + zNear) / (zFar - zNear);		// Eo centro Z
}

void Camera::perspective(GLfloat fov, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar) { // Câmera de perspectiva

	fov = fov * (3.141593f / 180);				// Transformar o ângulo em radianos

	GLfloat halfAngleTan = tan(fov * 0.5f);		// pega a tangente do ângulo / 2
	GLfloat farMnear = zFar - zNear;			// Tamanho do z

	projection.matrix[0] = 1 / (aspectRatio * halfAngleTan);	// 1 / pois estamos lidando com apenas metade da tela
	projection.matrix[5] = 1 / (halfAngleTan);					// tanto que se divide o ângulo por 2
																// multiplicação do aspect ratio pra deixar um quadrado quadrado numa tela retangular

	projection.matrix[10] = -((zNear + zFar) / farMnear);		// Coloca o Z entre -1 e 1
	projection.matrix[11] = -1;									// Necessário para que -z/(z) seja 1, ou seja, -z/-z, ele está nessa posição para não interferir nos outros

	projection.matrix[15] = 0;									// Tem que ser 0 para não interferir nos outros (e mostrar que é uma matriz projeção)

	projection.matrix[14] = -((2 * zFar * zNear) / farMnear);	// Também coloca o Z entre -1 e 1, (para entender porque duas diferentes faça sistema de equações)

	view.matrix[14] = -3.f;
}

void Camera::lookAt( Vector3 eye, Vector3 center, Vector3 up ) {	// LookAt versão mais manual

	Vector3 f = center - eye;
	f.normalize();

	Vector3 s = vector3CrossProduct(f, up);
	s.normalize();

	Vector3 u = vector3CrossProduct(s, f);

	view.matrix[0] = s.vector[0];
	view.matrix[1] = u.vector[0];
	view.matrix[2] = -f.vector[0];

	view.matrix[4] = s.vector[1];
	view.matrix[5] = u.vector[1];
	view.matrix[6] = -f.vector[1];

	view.matrix[8] = s.vector[2];
	view.matrix[9] = u.vector[2];
	view.matrix[10] = -f.vector[2];

	view.matrix[12] = -vector3DotProduct(s, eye);
	view.matrix[13] = -vector3DotProduct(u, eye);
	view.matrix[14] =  vector3DotProduct(f,  eye);
}

void Camera::lookAt(){	// lookAt versão própria da classe

	// Aplica as transformações da câmera
	float horizontalDistance = -distanceFromCenter * cos(glm::radians(pitch));

	float offsetX = horizontalDistance * sin(glm::radians(yaw));
	float offsetZ = horizontalDistance * cos(glm::radians(yaw));

	this->cameraPosition.vector[0] = center.vector[0] - offsetX;
	this->cameraPosition.vector[1] = center.vector[1] + (-distanceFromCenter * sin(glm::radians(pitch)));
	this->cameraPosition.vector[2] = center.vector[2] - offsetZ;
	
	// Cria a matriz
	Vector3 f = center - cameraPosition;
	f.normalize();

	Vector3 s = vector3CrossProduct(f, up);
	s.normalize();

	Vector3 u = vector3CrossProduct(s, f);
	u.normalize();

	view.matrix[0] = s.vector[0];
	view.matrix[1] = u.vector[0];
	view.matrix[2] = -f.vector[0];

	view.matrix[4] = s.vector[1];
	view.matrix[5] = u.vector[1];
	view.matrix[6] = -f.vector[1];

	view.matrix[8] = s.vector[2];
	view.matrix[9] = u.vector[2];
	view.matrix[10] = -f.vector[2];

	view.matrix[12] = -vector3DotProduct(s, cameraPosition);
	view.matrix[13] = -vector3DotProduct(u, cameraPosition);
	view.matrix[14] =  vector3DotProduct(f, cameraPosition);
}

Vector3 Camera::getCameraPosition() {

	return cameraPosition;
}

void Camera::orbitateHorizontally(float angle) {

	yaw += angle;
}
void Camera::orbitateVertically(float angle) {

	pitch += angle;
}
void Camera::changeDistanceFromCenterBy(float distance) {

	distanceFromCenter += distance;
}

/*	
	Matriz do tipo glFrustum, apenas para estudo -----

void Camera::perspective02(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) {

	projection.identity();

	projection.matrix[0] = (2 * zNear) / (right - left);
	projection.matrix[2] = (right + left) / (right - left);

	projection.matrix[5] = (2 * zNear) / (top - bottom);
	projection.matrix[6] = (top + bottom) / (top - bottom);

	projection.matrix[10] = -((zFar + zNear) / (zFar - zNear));
	projection.matrix[11] = -1.f;

	projection.matrix[14] = (-2 * zFar * zNear) / (zFar - zNear);
	projection.matrix[15] = 0;
}*/