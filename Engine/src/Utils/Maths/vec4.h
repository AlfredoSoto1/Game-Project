#pragma once

namespace MathsUtils {

	struct vec2;
	struct vec3;

	struct vec4 {
	public:
		float x, y, z, w;

		vec4(const vec4& vector);
		vec4(const vec3& vector3, float w);
		vec4(const vec2& vector2, float z, float w);
		vec4(float x, float y, float z, float w);
		vec4(float xyzw);

		float& operator [] (unsigned int index);

		vec4 operator - ();

		vec4 operator + (const vec4& vector) const;
		vec4 operator - (const vec4& vector) const;
		vec4 operator * (const float factor) const;
		vec4 operator / (const float factor) const;

		float operator * (const vec4& vector) const;

		vec4& operator += (const vec4& vector);
		vec4& operator -= (const vec4& vector);
		vec4& operator *= (const float factor);
		vec4& operator /= (const float factor);

		bool operator == (const float value);
		bool operator == (const vec4& vector);
		bool operator != (const vec4& vector);
	};
}