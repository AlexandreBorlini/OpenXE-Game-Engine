#include "Camera.h"

void Camera::ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) { // Camera ortogonal

	projection.identity();

	GLfloat width = right - left;
	GLfloat height = top - bottom;

	cameraPosition = Vector3( (width / 2) + left, (height/2) + bottom, 0.f );
	cameraHalfSize = Vector2( width/2, height/2 );
		
	// Parte de escala da matriz

	projection.matrix[0] = 2 / (width);					
	projection.matrix[5] = 2 / (height);				
	projection.matrix[10] = -2 / (zFar - zNear);		

	// Parte de translação

	projection.matrix[12] = - (right + left)/ (width);				
	projection.matrix[13] = - (top + bottom) / (height);			
	projection.matrix[14] = - (zFar + zNear) / (zFar - zNear);		
}

void Camera::perspective(GLfloat fov, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar) { // Câmera de perspectiva

	fov = fov * (3.141593f / 180);				

	GLfloat halfAngleTan = tan(fov * 0.5f);		
	GLfloat farMnear = zFar - zNear;			

	projection.matrix[0] = 1 / (aspectRatio * halfAngleTan);	
	projection.matrix[5] = 1 / (halfAngleTan);					
																

	projection.matrix[10] = -((zNear + zFar) / farMnear);		
	projection.matrix[11] = -1;									

	projection.matrix[15] = 0;									

	projection.matrix[14] = -((2 * zFar * zNear) / farMnear);	

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