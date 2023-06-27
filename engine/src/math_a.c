#include "math_a.h"


// Vector4f Vector4f_summation(Vector4f vect1, *Vector4f *vect2) {
// 	return (Vector4f){vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z, vect1.w + vect2.w};
// }

// Vector4f Vector4f_subtracting(Vector4f *vect1, Vector4f *vect2) {
// 	return (Vector4f){vect1.x - vect2.x, vect1.y - vect2.y, vect1.z - vect2.z, vect1.w - vect2.w};
// }

// Vector4f Vector3f_to_Vector4f(Vector3f *vect) {
// 	return (Vector4f){vect.x, vect.y, vect.z, 1};
// }

// Vector4f Vector4f_normalize(Vector4f *vect) {
// 	return (Vector4f){vect.x / vect.w, vect.y / vect.w, vect.z / vect.w, 1};
// }

// Vector4f Vector4f_mul_Matrix(Vector4f *vect, Matrix *matrix) {
// 	return (Vector4f){
// 		vect.x * matrix.values[0] + vect.y * matrix.values[1] + vect.z * matrix.values[2] + vect.w * matrix.values[3],
// 		vect.x * matrix.values[4] + vect.y * matrix.values[5] + vect.z * matrix.values[6] + vect.w * matrix.values[7],
// 		vect.x * matrix.values[8] + vect.y * matrix.values[9] + vect.z * matrix.values[10] + vect.w * matrix.values[11],
// 		vect.x * matrix.values[12] + vect.y * matrix.values[13] + vect.z * matrix.values[14] + vect.w * matrix.values[15]
// 	};
// }

// Vector3f Vector3f_mul_Matrix(Vector3f *vect, Matrix *matrix) {
// 	Vector3f newVect;

// 	newVect.x = vect.x * matrix.values[0][0] + vect.y * matrix.values[0][1] + vect.z * matrix.values[0][2] + vect.w * matrix.values[0][3];
// 	newVect.y = vect.x * matrix.values[1][0] + vect.y * matrix.values[1][1] + vect.z * matrix.values[1][2] + vect.w * matrix.values[1][3];
// 	newVect.z = vect.x * matrix.values[2][0] + vect.y * matrix.values[2][1] + vect.z * matrix.values[2][2] + vect.w * matrix.values[2][3];
// 	double w = vect.x * matrix.values[3][0] + vect.y * matrix.values[3][1] + vect.z * matrix.values[3][2] + vect.w * matrix.values[3][3]; 

// 	newVect.x /= w;
// 	newVect.y /= w;
// 	newVect.z /= w;

// 	return newVect;
// }