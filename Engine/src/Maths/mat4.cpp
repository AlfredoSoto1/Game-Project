#include "mat4.h"

#include "vec4.h"

using namespace Maths;

#define ADD  0
#define SUB  1
#define MUL  2
#define DIV  3
#define mMUL 4

mat4::mat4(float value) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = value;
}

mat4::mat4(float* matrixValues) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrixValues[i];
}

float& mat4::operator [] (unsigned int index) {
	return matrix[index];
}

float& mat4::operator () (unsigned int row, unsigned int col) {
	return matrix[row + col * this->row];
}

mat4::operator float* () {
	return matrix;
}

vec4 mat4::operator * (const vec4& vector) {
	float x = matrix[0] * vector.x + matrix[1] * vector.y + matrix[2] * vector.z + matrix[3] * vector.w;
	float y = matrix[4] * vector.x + matrix[5] * vector.y + matrix[6] * vector.z + matrix[7] * vector.w;
	float z = matrix[8] * vector.x + matrix[9] * vector.y + matrix[10] * vector.z + matrix[11] * vector.w;
	float w = matrix[12] * vector.x + matrix[13] * vector.y + matrix[14] * vector.z + matrix[15] * vector.w;
	return vec4(x, y, z, w);
}

mat4::mat4(const mat4& matrix1, const mat4& matrix2, float value, int param) {
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

mat4 mat4::operator + (const mat4& other) {
	return mat4(*this, other, 0, ADD);
}

mat4 mat4::operator - (const mat4& other) {
	return mat4(*this, other, 0, SUB);
}

mat4 mat4::operator * (const mat4& other) {
	return mat4(*this, other, 0, mMUL);
}

mat4 mat4::operator * (float factor) {
	return mat4(*this, *this, factor, MUL);
}

mat4 mat4::operator / (float factor) {
	return mat4(*this, *this, factor, DIV);
}

mat4& mat4::operator += (const mat4& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] + other.matrix[i];
	return *this;
}

mat4& mat4::operator -= (const mat4& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] - other.matrix[i];
	return *this;
}

mat4& mat4::operator *= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] * factor;
	return *this;
}

mat4& mat4::operator /= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] / factor;
	return *this;
}

bool mat4::operator == (const mat4& other) {
	for (int i = 0; i < row * col; i++) {
		if (matrix[i] != other.matrix[i])
			return false;
	}
	return true;
}