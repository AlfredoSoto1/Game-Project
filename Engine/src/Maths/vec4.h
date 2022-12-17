#pragma once

#include "vec.h"

namespace Maths {
	struct vec4 : public vec<4U, float> {
	public:

		vec4();
		vec4(float xyzw);
		vec4(float x, float y, float z, float w);
		vec4(const vec4& vector);

		vec4 operator - ();

		float operator*(const vec4& vector) const;

		vec4 operator + (const vec4& vector) const;
		vec4 operator - (const vec4& vector) const;
		vec4 operator * (const float factor) const;
		vec4 operator / (const float factor) const;

		vec4& operator += (const vec4& vector);
		vec4& operator -= (const vec4& vector);
		vec4& operator *= (const float factor);
		vec4& operator /= (const float factor);
	};
}