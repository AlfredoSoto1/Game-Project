#pragma once

#include "vec.h"

namespace Maths {
	struct vec3 : public vec<3U, float> {
	public:

		vec3();
		vec3(float xyz);
		vec3(float x, float y, float z);
		vec3(const vec3& vector);
		   
		vec3 operator - ();

		float operator*(const vec3& vector) const;
		   
		vec3 operator + (const vec3& vector) const;
		vec3 operator - (const vec3& vector) const;
		vec3 operator * (const float factor) const;
		vec3 operator / (const float factor) const;
		   
		vec3& operator += (const vec3& vector);
		vec3& operator -= (const vec3& vector);
		vec3& operator *= (const float factor);
		vec3& operator /= (const float factor);
	};
}