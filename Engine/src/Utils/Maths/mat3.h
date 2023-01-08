#pragma once

namespace Uranium {

	struct vec3;

	struct mat3 {
	public:
		static const int row = 3;
		static const int col = 3;

		mat3(float value = 0.0f);
		mat3(float* matrixValues);

		float& operator [] (unsigned int index);
		float& operator () (unsigned int row, unsigned int col);

		operator float* ();

		vec3 operator * (const vec3& vector);

		mat3 operator + (const mat3& other);
		mat3 operator - (const mat3& other);
		mat3 operator * (const mat3& other);
		mat3 operator * (float factor);
		mat3 operator / (float factor);

		mat3& operator += (const mat3& other);
		mat3& operator -= (const mat3& other);
		mat3& operator *= (float factor);
		mat3& operator /= (float factor);

		bool operator == (const mat3& other);

	private:
		float matrix[row * col];
		mat3(const mat3& matrix1, const mat3& matrix2, float value, int param);
	};
}