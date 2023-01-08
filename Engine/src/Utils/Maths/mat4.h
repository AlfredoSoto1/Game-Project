#pragma once

namespace Uranium {

	struct vec4;

	struct mat4 {
	public:
		static const int row = 4;
		static const int col = 4;

		mat4(float value = 0.0f);
		mat4(float* matrixValues);

		float& operator [] (unsigned int index);
		float& operator () (unsigned int row, unsigned int col);

		operator float* ();

		vec4 operator * (const vec4& vector);

		mat4 operator + (const mat4& other);
		mat4 operator - (const mat4& other);
		mat4 operator * (const mat4& other);
		mat4 operator * (float factor);
		mat4 operator / (float factor);

		mat4& operator += (const mat4& other);
		mat4& operator -= (const mat4& other);
		mat4& operator *= (float factor);
		mat4& operator /= (float factor);

		bool operator == (const mat4& other);

	private:
		float matrix[row * col];
		mat4(const mat4& matrix1, const mat4& matrix2, float value, int param);
	};
}