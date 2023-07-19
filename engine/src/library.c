#include <stdio.h>

#include "library.h"


void printVector3f(Vector3f *vect) {
	printf("Vector3f {\n  %lf,\n  %lf,\n  %lf\n}\n", vect->x, vect->y, vect->z);
}

void printVector4f(Vector4f *vect) {
	printf("Vector4f {\n  %lf,\n  %lf,\n  %lf,\n  %lf\n}\n", vect->x, vect->y, vect->z, vect->w);
}

void printMatrix(int height, int width, double *matrix) {
	printf("Matrix {\n");
	for (int i = 0; i < height; ++i) {
		printf("    {");
		for (int j = 0; j < width; ++j) {
			printf("%lf, ", matrix[i * width + j]);
		}
		printf(" },\n");
	}
	printf("}\n");
}

void Vector4f_summation(Vector4f *vect1, Vector4f *vect2, Vector4f *vect3) {
	vect3->x = vect1->x + vect2->x;
	vect3->y = vect1->y + vect2->y;
	vect3->z = vect1->z + vect2->z;
	vect3->w = vect1->w + vect2->w;
}

void Vector4f_subtracting(Vector4f *vect1, Vector4f *vect2, Vector4f *vect3) {
	vect3->x = vect1->x - vect2->x;
	vect3->y = vect1->y - vect2->y;
	vect3->z = vect1->z - vect2->z;
	vect3->w = vect1->w - vect2->w;
}

void Vector3f_to_Vector4f(Vector3f *vect1, Vector4f *vect2) {
	vect2->x = vect1->x;
	vect2->y = vect1->y;
	vect2->z = vect1->z;
	vect2->w = 1;
}

void Vector4f_normalize(Vector4f *vect1, Vector4f *vect2) {
	vect2->x = vect1->x / vect1->w;
	vect2->y = vect1->y / vect1->w;
	vect2->z = vect1->z / vect1->w;
	vect2->w = 1;
}

void Vector4f_mul_Matrix(Vector4f *vect1, double *matrix, Vector4f *vect2) {
	double x, y, z, w;

	x = vect1->x * matrix[0] + vect1->y * matrix[1] + vect1->z * matrix[2] + vect1->w * matrix[3];
	y = vect1->x * matrix[4] + vect1->y * matrix[5] + vect1->z * matrix[6] + vect1->w * matrix[7];
	z = vect1->x * matrix[8] + vect1->y * matrix[9] + vect1->z * matrix[10] + vect1->w * matrix[11];
	w = vect1->x * matrix[12] + vect1->y * matrix[13] + vect1->z * matrix[14] + vect1->w * matrix[15];

	vect2->x = x;
	vect2->y = y;
	vect2->z = z;
	vect2->w = w;
}

// void Vector3f_mul_Matrix(Vector3f *vect1, Matrix *matrix, Vector3f *vect2) {
// 	vect2->x = vect1->x * matrix[0] + vect1->y * matrix[1] + vect1->z * matrix[2] + 1 * matrix[3];
// 	vect2->y = vect1->x * matrix[4] + vect1->y * matrix[5] + vect1->z * matrix[6] + 1 * matrix[7];
// 	vect2->z = vect1->x * matrix[8] + vect1->y * matrix[9] + vect1->z * matrix[10] + 1 * matrix[11];
// 	double w = vect1->x * matrix[12] + vect1->y * matrix[13] + vect1->z * matrix[14] + 1 * matrix[15];

// 	vect2->x /= w;
// 	vect2->y /= w;
// 	vect2->z /= w;
// }