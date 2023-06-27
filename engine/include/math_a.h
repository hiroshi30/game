#pragma once

#define PI 3.14159265


typedef struct Matrix {
	int height;
	int width;
	double *values;
} Matrix;

typedef struct Vector3f {
	double x, y, z;
} Vector3f;

typedef struct Vector4f {
	double x, y, z, w;
} Vector4f;

typedef struct Triangle {
	Vector3f points[3];
} Triangle;

typedef struct Mesh {
	int count;
	Triangle *triangles;
} Mesh;

// Vector4f Vector4f_summation(Vector4f *vect1, Vector4f *vect2);
// Vector4f Vector4f_subtracting(Vector4f *vect1, Vector4f *vect2);
// Vector4f Vector3f_to_Vector4f(Vector3f *vect);
// Vector4f Vector4f_normalize(Vector4f *vect);
// Vector4f Vector4f_mul_Matrix(Vector4f *vect, Matrix *matrix);
