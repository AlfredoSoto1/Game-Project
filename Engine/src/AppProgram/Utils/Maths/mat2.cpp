#include "AppProgram/Utils/Maths/mat2.h"

#include "AppProgram/Utils/Maths/vec2.h"

using namespace MathsUtils;

#define ADD  0
#define SUB  1
#define MUL  2
#define DIV  3
#define mMUL 4

mat2::mat2(float value) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = value;
}

mat2::mat2(float* matrixValues) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrixValues[i];
}

float& mat2::operator [] (unsigned int index) {
	return matrix[index];
}

float& mat2::operator () (unsigned int row, unsigned int col) {
	return matrix[row + col * this->col];
}

mat2::operator float* () {
	return matrix;
}

vec2 mat2::operator * (const vec2& vector) {
	float x = matrix[0] * vector.x + matrix[1] * vector.y;
	float y = matrix[2] * vector.x + matrix[3] * vector.y;
	return vec2(x, y);
}

mat2::mat2(const mat2& matrix1, const mat2& matrix2, float value, int param) {
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

mat2 mat2::operator + (const mat2& other) {
	return mat2(*this, other, 0, ADD);
}

mat2 mat2::operator - (const mat2& other) {
	return mat2(*this, other, 0, SUB);
}

mat2 mat2::operator * (const mat2& other) {
	return mat2(*this, other, 0, mMUL);
}

mat2 mat2::operator * (float factor) {
	return mat2(*this, *this, factor, MUL);
}

mat2 mat2::operator / (float factor) {
	return mat2(*this, *this, factor, DIV);
}

mat2& mat2::operator += (const mat2& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] + other.matrix[i];
	return *this;
}

mat2& mat2::operator -= (const mat2& other) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] - other.matrix[i];
	return *this;
}

mat2& mat2::operator *= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] * factor;
	return *this;
}

mat2& mat2::operator /= (float factor) {
	for (int i = 0; i < row * col; i++)
		matrix[i] = matrix[i] / factor;
	return *this;
}

bool mat2::operator == (const mat2& other) {
	for (int i = 0; i < row * col; i++) {
		if (matrix[i] != other.matrix[i])
			return false;
	}
	return true;
}
