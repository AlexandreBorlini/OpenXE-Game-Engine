#include "Transform.h"

void Transform::scale( GLfloat x, GLfloat y, GLfloat z) { // Escala a matriz com 3 floats

	lenght = x;
	height = y;
	width = z;
}

void Transform::scale(GLfloat n) { // Escala a matriz com 3 floats

	lenght = n;
	height = n;
	width = n;
}

void Transform::translate(GLfloat nx, GLfloat ny, GLfloat nz) { // Translate matrix

	position.x += nx;
	position.y += ny;
	position.z += nz;
}

void Transform::goTo( GLfloat nx, GLfloat ny, GLfloat nz) { // Vai até posição indicada

	position.x = nx;
	position.y = ny;
	position.z = nz;
}

void Transform::localRotationX(GLfloat angle) {

	angle = degreesToRadians(angle);

	Quaternion rotationQuat;
	rotationQuat.rotateAboutX(angle);

	q *= rotationQuat; // Concatena multiplicando
}

void Transform::worldRotationX(GLfloat angle) {

	angle = degreesToRadians(angle);

	Quaternion rotationQuat;
	rotationQuat.rotateAboutX(angle);

	q = rotationQuat * q;
}

void Transform::localRotationY(GLfloat angle) {

	angle = degreesToRadians(angle);

	Quaternion rotationQuat;
	rotationQuat.rotateAboutY(angle);

	q *= rotationQuat; // Concatena multiplicando
}


void Transform::worldRotationY(GLfloat angle) {

	angle = degreesToRadians(angle);

	Quaternion rotationQuat;
	rotationQuat.rotateAboutY(angle);

	q = rotationQuat * q;
}

void Transform::localRotationZ(GLfloat angle) {

	angle = degreesToRadians(angle);

	Quaternion rotationQuat;

	rotationQuat.rotateAboutZ(angle);

	q *= rotationQuat; // Concatena multiplicando
}

void Transform::worldRotationZ(GLfloat angle) {

	angle = degreesToRadians(angle);

	Quaternion rotationQuat;
	rotationQuat.rotateAboutZ(angle);

	q = rotationQuat * q;
}

Matrix4 Transform::quaternionToMatrix() {

	Matrix4 m;

	q.normalize();

	GLfloat yRaisedBy2 = (q.y * q.y);
	GLfloat zRaisedBy2 = (q.z * q.z);
	GLfloat xRaisedBy2 = (q.x * q.x);
	GLfloat wRaisedBy2 = (q.w * q.w);

	GLfloat XmY = 2 * q.x * q.y;
	GLfloat XmZ = 2* q.x * q.z;

	GLfloat YmZ = 2 * q.y * q.z;

	GLfloat WmX = 2 * q.w * q.x;
	GLfloat WmY = 2 * q.w * q.y;
	GLfloat WmZ = 2 * q.w * q.z;

	m.matrix[0] = wRaisedBy2 + xRaisedBy2 - yRaisedBy2 - zRaisedBy2;
	m.matrix[1] = XmY - WmZ;
	m.matrix[2] = (XmZ + WmY);
	 
	m.matrix[4] = XmY + WmZ;
	m.matrix[5] = wRaisedBy2 - xRaisedBy2 + yRaisedBy2 - zRaisedBy2;
	m.matrix[6] = YmZ - WmX;
	 
	m.matrix[8] = (XmZ - WmY);
	m.matrix[9] = YmZ + WmX;
	m.matrix[10] = wRaisedBy2 - xRaisedBy2 - yRaisedBy2 + zRaisedBy2;

	return m;
}

Matrix4 Transform::getTransformResultMatrix() { 

	Matrix4 scaleMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translateMatrix;

	scaleMatrix.matrix[0] = lenght;
	scaleMatrix.matrix[5] = height;
	scaleMatrix.matrix[10] = width;

	rotationMatrix = quaternionToMatrix();

	// Posição
	translateMatrix.matrix[12] = position.x;
	translateMatrix.matrix[13] = position.y;
	translateMatrix.matrix[14] = position.z;

	translateMatrix.identity();

	return scaleMatrix * rotationMatrix * translateMatrix;
}

GLfloat Transform::degreesToRadians(GLfloat degrees) {

	return degrees * (3.141593f / 180);
}