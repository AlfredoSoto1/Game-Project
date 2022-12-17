#pragma once

#include "vec.h"

namespace Maths {
	struct vec2 : public vec<2U, float> {
	public:

		vec2();
		vec2(float xy);
		vec2(float x, float y);
		vec2(const vec2& vector);

		vec2 operator - ();

		vec2 operator + (const vec2& vector) const;
		vec2 operator - (const vec2& vector) const;
		vec2 operator * (const float factor) const;
		vec2 operator / (const float factor) const;

		vec2& operator += (const vec2& vector);
		vec2& operator -= (const vec2& vector);
		vec2& operator *= (const float factor);
		vec2& operator /= (const float factor);

	};
}