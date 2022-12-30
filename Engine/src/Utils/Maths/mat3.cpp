#include "Utils/Maths/mat3.h"
#include "Utils/Maths/vec3.h"

using namespace MathsUtils;

#define ADD  0
#define SUB  1
#define MUL  2
#define DIV  3
#define mMUL 4

mat3::mat3(float value) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = value;
}

mat3::mat3(float* matrixValues) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrixValues[i];
}

float& mat3::operator [] (unsigned int index) {
	return matrix[index];
}

float& mat3::operator () (unsigned int row, unsigned int col) {
	return matrix[row + col * this->col];
}

mat3::operator float* () {
	return matrix;
}

vec3 mat3::operator * (const vec3& vector) {
	float x = matrix[0] * vector.x + matrix[1] * vector.y + matrix[2] * vector.z;
	float y = matrix[3] * vector.x + matrix[4] * vector.y + matrix[5] * vector.z;
	float z = matrix[6] * vector.x + matrix[7] * vector.y + matrix[8] * vector.z;
	return vec3(x, y, z);
}

mat3::mat3(const mat3& matrix1, const mat3& matrix2, float value, int param) {
	//zero
	for (int i = 0; i < row * col; i++)
		matrix[i] = 0.0;
	//apply arigmethic
	switch (param) {
	case ADD:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] + matrix2.matrix[i];
		break;
	case SUB:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] - matrix2.matrix[i];
		break;
	case MUL:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] * value;
		break;
	case DIV:
		for (int i = 0; i < row * col; i++)
			matrix[i] = matrix1.matrix[i] / value;
		break;
	case mMUL:
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				float element = 0.0f;
				for (int k = 0; k < row; k++)
					element += matrix1.matrix[k + j * row] * matrix2.matrix[i + k * col];
				matrix[i + j * col] = element;
			}
		break;
	}
}

mat3 mat3::operator + (const mat3& other) {
	return mat3(*this, other, 0, ADD);
}

mat3 mat3::operator - (const mat3& other) {
	return mat3(*this, other, 0, SUB);
}

mat3 mat3::operator * (const mat3& other) {
	return mat3(*this, other, 0, mMUL);
}

mat3 mat3::operator * (float factor) {
	return mat3(*this, *this, factor, MUL);
}

mat3 mat3::operator / (float factor) {
	return mat3(*this, *this, factor, DIV);
}

mat3& mat3::operator += (const mat3& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] + other.matrix[i];
	return *this;
}

mat3& mat3::operator -= (const mat3& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] - other.matrix[i];
	return *this;
}

mat3& mat3::operator *= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] * factor;
	return *this;
}

mat3& mat3::operator /= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] / factor;
	return *this;
}

bool mat3::operator == (const mat3& other) {
	for (int i = 0; i < row * col; i++) {
		if (matrix[i] != other.matrix[i])
			return false;
	}
	return true;
}
