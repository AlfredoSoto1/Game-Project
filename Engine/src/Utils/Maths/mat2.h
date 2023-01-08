#pragma once

namespace Uranium {

	struct vec2;

	struct mat2 {
	public:
		static const unsigned int row = 2;
		static const unsigned int col = 2;

		mat2(float value = 0.0f);
		mat2(float* matrixValues);

		float& operator [] (unsigned int index);
		float& operator () (unsigned int row, unsigned int col);

		operator float* ();

		vec2 operator * (const vec2& vector);

		mat2 operator + (const mat2& other);
		mat2 operator - (const mat2& other);
		mat2 operator * (const mat2& other);
		mat2 operator * (float factor);
		mat2 operator / (float factor);

		mat2& operator += (const mat2& other);
		mat2& operator -= (const mat2& other);
		mat2& operator *= (float factor);
		mat2& operator /= (float factor);

		bool operator == (const mat2& other);

	private:
		float matrix[row * col];
		mat2(const mat2& matrix1, const mat2& matrix2, float value, int param);
	};
}