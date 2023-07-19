#pragma once

#define PI 3.14159265


typedef struct Vector3f {
	double x, y, z;
} Vector3f;

void printVector3f(Vector3f *vect);

typedef struct Vector4f {
	double x, y, z, w;
} Vector4f;

void printVector4f(Vector4f *vect);

void printMatrix(int height, int width, double *matrix);

void Vector4f_summation(Vector4f *vect1, Vector4f *vect2, Vector4f *vect3);
void Vector4f_subtracting(Vector4f *vect1, Vector4f *vect2, Vector4f *vect3);
void Vector3f_to_Vector4f(Vector3f *vect1, Vector4f *vect2);
void Vector4f_normalize(Vector4f *vect1, Vector4f *vect2);
void Vector4f_mul_Matrix(Vector4f *vect1, double *matrix, Vector4f *vect2);