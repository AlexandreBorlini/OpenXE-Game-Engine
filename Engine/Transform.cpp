#include "Transform.h"

void Transform::scale( GLfloat x, GLfloat y, GLfloat z) { // Escala a matriz com 3 floats

	scaleX = x;
	scaleY = y;
	scaleZ = z;
}

void Transform::scale(GLfloat n) { // Escala a matriz com 3 floats

	scaleX = n;
	scaleY = n;
	scaleZ = n;
}

void Transform::translate(GLfloat nx, GLfloat ny, GLfloat nz) { // Translate matrix

	position.x += nx;
	position.y += ny;
	position.z += nz;
}

void Transform::translateLocal(GLfloat nx, GLfloat ny, GLfloat nz) {

	Matrix4 rotationMatrix = quaternionToMatrix();
	
	Vector4 translateMatrix;
	translateMatrix.x = nx;
	translateMatrix.y = ny;
	translateMatrix.z = nz;

	Vector4 result = translateMatrix * rotationMatrix;

	position.x += result.x;
	position.y += result.y;
	position.z += result.z;
}

void Transform::translate(Vector3 vector) { // Translate matrix

	position.x += vector.vector[0];
	position.y += vector.vector[1];
	position.z += vector.vector[2];
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

	scaleMatrix.matrix[0]  = scaleX;
	scaleMatrix.matrix[5]  = scaleY;
	scaleMatrix.matrix[10] = scaleZ;

	rotationMatrix = quaternionToMatrix();

	// Posição
	translateMatrix.matrix[12] = position.x;
	translateMatrix.matrix[13] = position.y;
	translateMatrix.matrix[14] = position.z;

	//translateMatrix.identity();

	Matrix4 result = scaleMatrix * rotationMatrix * translateMatrix;

	return result;
}

GLfloat Transform::degreesToRadians(GLfloat degrees) {

	return degrees * (3.141593f / 180);
}

Vector2 Transform::getLeftAndRightX() {

	Vector2 result;
	
	result.vector[0] = position.x - (widthOver2 * scaleX);
	result.vector[1] = position.x + (widthOver2 * scaleX);

	return result;
}

Vector2 Transform::getLeftAndRightY() {


	Vector2 result;

	result.vector[0] = position.y - (heightOver2 * scaleY);
	result.vector[1] = position.y + (heightOver2 * scaleY);

	return result;
}

GLfloat Transform::getHeightOver2() {

	return heightOver2;
}

GLfloat Transform::getWidthOver2() {

	return widthOver2;
}

void Transform::changeHeightValue(float newHeight) {

	heightOver2 = newHeight/2;
}

void Transform::changeWidthValue(float newWidth) {

	widthOver2 = newWidth/2;
}

Vector3 Transform::getScale() {

	return Vector3(scaleX, scaleY, scaleZ);
}