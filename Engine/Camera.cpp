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

	projection.matrix[12] = -(right + left)/ (width);				// Trazer a câmera para o centro X (para o centro ficar no 0)
	projection.matrix[13] = - (top + bottom) / (height);			// Para o centro Y
	projection.matrix[14] = - (zFar + zNear) / (zFar - zNear);		// Eo centro Z
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
	view.matrix[13] = 0.f;
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