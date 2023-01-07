#include "Operation.h"
#include "Constants.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "mat2.h"
#include "mat3.h"
#include "mat4.h"

#include <cmath>

using namespace Uranium;

float Uranium::sqrt(float number) {
	return inv_sqrt(number) * number;
}

float Uranium::inv_sqrt(float number) {
	int i;
	float x2, y;

	x2 = number * 0.5f;
	y = number;
	i = *(int*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5F - (x2 * y * y));
	//y = y * (1.5F - (x2 * y * y));
	return y;
}

double Uranium::toDegree(double radian) {
	return (180.0 / PI) * radian;
}

double Uranium::toRadians(double degree) {
	return (PI / 180.0) * degree;
}

float Uranium::toDegree(float radian) {
	return (180.0f / PI) * radian;
}

float Uranium::toRadians(float degree) {
	return (PI / 180.0f) * degree;
}

float Uranium::lengthSquared(const vec2& vector) {
	return dot(vector, vector);
}
	
float Uranium::lengthSquared(const vec3& vector) {
	return dot(vector, vector);
}
	
float Uranium::lengthSquared(const vec4& vector) {
	return dot(vector, vector);
}
	
float Uranium::length(const vec2& vector) {
	return Uranium::sqrt(lengthSquared(vector));
}
	
float Uranium::length(const vec3& vector) {
	return Uranium::sqrt(lengthSquared(vector));
}
	
float Uranium::length(const vec4& vector) {
	return Uranium::sqrt(lengthSquared(vector));
}
	
float Uranium::invLength(const vec2& vector) {
	return Uranium::inv_sqrt(lengthSquared(vector));
}
	
float Uranium::invLength(const vec3& vector) {
	return Uranium::inv_sqrt(lengthSquared(vector));
}
	
float Uranium::invLength(const vec4& vector) {
	return Uranium::inv_sqrt(lengthSquared(vector));
}
	
float Uranium::dot(const vec2& vectorA, const vec2& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}
	
float Uranium::dot(const vec3& vectorA, const vec3& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}
	
float Uranium::dot(const vec4& vectorA, const vec4& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z + vectorA.w * vectorB.w;
}
	
vec3 Uranium::cross(const vec3& vectorA, const vec3& vectorB) {
	return vec3(
		vectorA.y * vectorB.z - vectorA.z * vectorB.y,
		vectorA.z * vectorB.x - vectorA.x * vectorB.z,
		vectorA.x * vectorB.y - vectorA.y * vectorB.x);
}
	
void Uranium::negate(vec2* vector) {
	(*vector) *= -1.0;
}
	
void Uranium::negate(vec3* vector) {
	(*vector) *= -1.0;
}
	
void Uranium::negate(vec4* vector) {
	(*vector) *= -1.0;
}
	
vec2 Uranium::negate(const vec2& vector) {
	vec2 outVec(vector);
	return outVec *= -1.0;
}
	
vec3 Uranium::negate(const vec3& vector) {
	vec3 outVec(vector);
	return outVec *= 1.0;
}
	
vec4 Uranium::negate(const vec4& vector) {
	vec4 outVec(vector);
	return outVec *= 1.0;
}
	
void Uranium::normalize(vec2* vector) {
	*vector *= Uranium::inv_sqrt(lengthSquared(*vector));
}
	
void Uranium::normalize(vec3* vector) {
	*vector *= Uranium::inv_sqrt(lengthSquared(*vector));
}
	
void Uranium::normalize(vec4* vector) {
	*vector *= Uranium::inv_sqrt(lengthSquared(*vector));
}
	
vec2 Uranium::normalize(const vec2& vector) {
	vec2 outVec(vector);
	return outVec *= Uranium::inv_sqrt(lengthSquared(vector));
}
	
vec3 Uranium::normalize(const vec3& vector) {
	vec3 outVec(vector);
	return outVec *= Uranium::inv_sqrt(lengthSquared(vector));
}
	
vec4 Uranium::normalize(const vec4& vector) {
	vec4 outVec(vector);
	return outVec *= Uranium::inv_sqrt(lengthSquared(vector));
}
	
vec2 Uranium::projection(vec2& vectorA, vec2& vectorB) {
	float factor = vectorA * vectorB / lengthSquared(vectorB);
	vec2 outVec(vectorB);
	return vec2(outVec *= factor);
}
	
float Uranium::component(vec2& vectorA, vec2& vectorB) {
	return vectorA * vectorB / length(vectorB);
}
	
vec3 Uranium::getNormal(const vec3& point1, const vec3& point2, const vec3& point3) {
	return cross(point2 - point1, point3 - point1);
}





void Uranium::zero(mat2* matrix) {
	for (int i = 0; i < 4; i++)
		(*matrix)[0] = 0.0f;
}

void Uranium::zero(mat3* matrix) {
	for (int i = 0; i < 9; i++)
		(*matrix)[0] = 0.0f;
}

void Uranium::zero(mat4* matrix) {
	for (int i = 0; i < 16; i++)
		(*matrix)[0] = 0.0f;
}

void Uranium::set(float value, mat2* matrix) {
	for (int i = 0; i < 4; i++)
		(*matrix)[0] = value;
}

void Uranium::set(float value, mat3* matrix) {
	for (int i = 0; i < 9; i++)
		(*matrix)[0] = value;
}

void Uranium::set(float value, mat4* matrix) {
	for (int i = 0; i < 16; i++)
		(*matrix)[0] = value;
}

void Uranium::identity(mat2* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void Uranium::identity(mat3* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void Uranium::identity(mat4* matrix) {
	for (int i = 0; i < (*matrix).row; i++)
		for (int j = 0; j < (*matrix).col; j++)
			if (i == j)
				(*matrix)[j + i * (*matrix).col] = 1.0f;
			else
				(*matrix)[j + i * (*matrix).col] = 0.0f;
}

void Uranium::subMatOf(mat3& matrix, unsigned int _row, unsigned int _col, mat2* dest) {
	int subRow = 0, subCol = 0;
	for (unsigned int row = 0; row < matrix.col; row++)
		for (unsigned int col = 0; col < matrix.col; col++)
			if (row != _row && col != _col) {
				(*dest)[subCol++ + subRow * (matrix.col - 1)] = matrix[col + row * matrix.col];
				if (subCol == matrix.col - 1) {
					subCol = 0;
					subRow++;
				}
			}
}

void Uranium::subMatOf(mat4& matrix, unsigned int _row, unsigned int _col, mat3* dest) {
	int subRow = 0, subCol = 0;
	for (unsigned int row = 0; row < matrix.col; row++)
		for (unsigned int col = 0; col < matrix.col; col++)
			if (row != _row && col != _col) {
				(*dest)[subCol++ + subRow * (matrix.col - 1)] = matrix[col + row * matrix.col];
				if (subCol == matrix.col - 1) {
					subCol = 0;
					subRow++;
				}
			}
}

float Uranium::determinantOf(mat2& matrix) {
	return matrix[0] * matrix[3] - matrix[1] * matrix[2];
}

float Uranium::determinantOf(mat3& matrix) {
	mat2 temp =  mat2();
	float determinant = 0.0f;
	for (int sign = 1, i = 0; i < matrix.col; i++) {
		subMatOf(matrix, 0, i, &temp);
		determinant += sign * matrix[i] * determinantOf(temp);
		sign = -sign;
	}
	return determinant;
}

float Uranium::determinantOf(mat4& matrix) {
	mat3 temp;
	float determinant = 0.0f;
	for (int sign = 1, i = 0; i < matrix.col; i++) {
		subMatOf(matrix, 0, i, &temp);
		determinant += matrix[i] * determinantOf(temp) * sign;
		sign = -sign;
	}
	return determinant;
}

mat2 Uranium::transpose(mat2& matrix) {
	mat2 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat3 Uranium::transpose(mat3& matrix) {
	mat3 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat4 Uranium::transpose(mat4& matrix) {
	mat4 temp;
	for (int i = 0; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++)
			temp[i + j * matrix.row] = matrix[j + i * matrix.col];
	return temp;
}

mat2 Uranium::inverse(mat2& matrix) {
	mat2 outMatrix;
	outMatrix[0] = matrix[3];
	outMatrix[1] = -matrix[1];
	outMatrix[2] = -matrix[2];
	outMatrix[3] = matrix[0];
	outMatrix /= determinantOf(matrix);
	return outMatrix;
}

mat3 Uranium::inverse(mat3& matrix) {
	mat3 adjointMatrix = mat3();
	mat2 temp = mat2();
	for (int i = 0, sign = 1; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++) {
			subMatOf(matrix, i, j, &temp);
			adjointMatrix[j + i * matrix.col] = determinantOf(temp) * sign;
			sign = -sign;
		}
	mat3 outMatrix = transpose(adjointMatrix);
	outMatrix /= determinantOf(matrix);
	return outMatrix;
}

mat4 Uranium::inverse(mat4& matrix) {
	mat4 adjointMatrix;
	mat3 temp;
	for (int i = 0, sign = 1; i < matrix.row; i++)
		for (int j = 0; j < matrix.col; j++) {
			subMatOf(matrix, i, j, &temp);
			adjointMatrix[j + i * matrix.col] = determinantOf(temp) * sign;
			sign = -sign;
		}
	mat4 outMatrix = transpose(adjointMatrix);
	outMatrix /= determinantOf(matrix);
	return outMatrix;
}

void Uranium::project(mat4* projectionMatrix, double farDistance, double nearDistance, double fov, double width, double height) {
	double aspectRatio = width / height;
	double y_scale = (float)(1.0 / tan(Uranium::toRadians(fov / 2.0)));
	double x_scale = (float)(y_scale / aspectRatio);
	double frustum_length = farDistance - nearDistance;
	projectionMatrix->operator()(0, 0) = (x_scale);
	projectionMatrix->operator()(1, 1) = (y_scale);
	projectionMatrix->operator()(2, 2) = (-((farDistance + nearDistance) / frustum_length));
	projectionMatrix->operator()(2, 3) = (-1);
	projectionMatrix->operator()(3, 2) = (-((2.0 * farDistance * nearDistance) / frustum_length));
	projectionMatrix->operator()(3, 3) = (0);
}

void Uranium::rotate(mat4& src, mat4* dest, float angle, const vec3& axis) {
	float c = cos(angle);
	float s = sin(angle);
	float oneminusc = 1.0f - c;
	float xy = axis.x * axis.y;
	float yz = axis.y * axis.z;
	float xz = axis.x * axis.z;
	float xs = axis.x * s;
	float ys = axis.y * s;
	float zs = axis.z * s;

	float f00 = axis.x * axis.x * oneminusc + c;
	float f01 = xy * oneminusc + zs;
	float f02 = xz * oneminusc - ys;
	// n[3] not used
	float f10 = xy * oneminusc - zs;
	float f11 = axis.y * axis.y * oneminusc + c;
	float f12 = yz * oneminusc + xs;
	// n[7] not used
	float f20 = xz * oneminusc + ys;
	float f21 = yz * oneminusc - xs;
	float f22 = axis.z * axis.z * oneminusc + c;

	float t00 = src(0, 0) * f00 + src(1, 0) * f01 + src(2, 0) * f02;
	float t01 = src(0, 1) * f00 + src(1, 1) * f01 + src(2, 1) * f02;
	float t02 = src(0, 2) * f00 + src(1, 2) * f01 + src(2, 2) * f02;
	float t03 = src(0, 3) * f00 + src(1, 3) * f01 + src(2, 3) * f02;
	float t10 = src(0, 0) * f10 + src(1, 0) * f11 + src(2, 0) * f12;
	float t11 = src(0, 1) * f10 + src(1, 1) * f11 + src(2, 1) * f12;
	float t12 = src(0, 2) * f10 + src(1, 2) * f11 + src(2, 2) * f12;
	float t13 = src(0, 3) * f10 + src(1, 3) * f11 + src(2, 3) * f12;
	(*dest)(2, 0) = src(0, 0) * f20 + src(1, 0) * f21 + src(2, 0) * f22;
	(*dest)(2, 1) = src(0, 1) * f20 + src(1, 1) * f21 + src(2, 1) * f22;
	(*dest)(2, 2) = src(0, 2) * f20 + src(1, 2) * f21 + src(2, 2) * f22;
	(*dest)(2, 3) = src(0, 3) * f20 + src(1, 3) * f21 + src(2, 3) * f22;
	(*dest)(0, 0) = t00;
	(*dest)(0, 1) = t01;
	(*dest)(0, 2) = t02;
	(*dest)(0, 3) = t03;
	(*dest)(1, 0) = t10;
	(*dest)(1, 1) = t11;
	(*dest)(1, 2) = t12;
	(*dest)(1, 3) = t13;
}

void Uranium::scale(mat4& src, mat4* dest, const vec3& scaleVector) {
	(*dest)(0, 0) = src(0, 0) * scaleVector.x;
	(*dest)(0, 1) = src(0, 1) * scaleVector.x;
	(*dest)(0, 2) = src(0, 2) * scaleVector.x;
	(*dest)(0, 3) = src(0, 3) * scaleVector.x;
	(*dest)(1, 0) = src(1, 0) * scaleVector.y;
	(*dest)(1, 1) = src(1, 1) * scaleVector.y;
	(*dest)(1, 2) = src(1, 2) * scaleVector.y;
	(*dest)(1, 3) = src(1, 3) * scaleVector.y;
	(*dest)(2, 0) = src(2, 0) * scaleVector.z;
	(*dest)(2, 1) = src(2, 1) * scaleVector.z;
	(*dest)(2, 2) = src(2, 2) * scaleVector.z;
	(*dest)(2, 3) = src(2, 3) * scaleVector.z;
}

void Uranium::translate(mat4& src, mat4* dest, const vec3& position) {
	(*dest)(3, 0) += src(0, 0) * position.x + src(1, 0) * position.y + src(2, 0) * position.z;
	(*dest)(3, 1) += src(0, 1) * position.x + src(1, 1) * position.y + src(2, 1) * position.z;
	(*dest)(3, 2) += src(0, 2) * position.x + src(1, 2) * position.y + src(2, 2) * position.z;
	(*dest)(3, 3) += src(0, 3) * position.x + src(1, 3) * position.y + src(2, 3) * position.z;
}

void Uranium::transform(mat4* transformationMatrix, const vec3& position, const vec3& rotation, const vec3& scaleVector) {
	identity(transformationMatrix);
	//apply translation
	translate(*transformationMatrix, transformationMatrix, position);
	//apply rotation
	rotate(*transformationMatrix, transformationMatrix, rotation.x, vec3(1.0, 0.0, 0.0));
	rotate(*transformationMatrix, transformationMatrix, rotation.y, vec3(0.0, 1.0, 0.0));
	rotate(*transformationMatrix, transformationMatrix, rotation.z, vec3(0.0, 0.0, 1.0));
	//apply scale
	scale(*transformationMatrix, transformationMatrix, scaleVector);
}

