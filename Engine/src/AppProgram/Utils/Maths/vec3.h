#pragma once

namespace MathsUtils {

	struct vec2;

	struct vec3 {
	public:
		float x, y, z;

		vec3(float xyz);
		vec3(float x, float y, float z);
		vec3(const vec3& vector);
		vec3(const vec2& vector2, float z);

		float& operator [] (unsigned int index);

		vec3 operator - ();

		vec3 operator + (const vec3& vector) const;
		vec3 operator - (const vec3& vector) const;
		vec3 operator * (const float factor) const;
		vec3 operator / (const float factor) const;

		vec3& operator += (const vec3& vector);
		vec3& operator -= (const vec3& vector);
		vec3& operator *= (const float factor);
		vec3& operator /= (const float factor);

		float operator * (const vec3& vector) const;

		vec3 operator | (const vec3& vector);

		bool operator == (const float value);
		bool operator == (const vec3& vector);
		bool operator != (const vec3& vector);
	};
}