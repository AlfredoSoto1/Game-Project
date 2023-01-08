#pragma once

namespace Uranium {

	struct vec2 {
	public:
		float x, y;

		vec2(float xy = 0.0f);
		vec2(float x, float y);
		vec2(const vec2& vector);

		float& operator [] (unsigned int index);

		vec2 operator - ();

		vec2 operator + (const vec2& vector) const;
		vec2 operator - (const vec2& vector) const;
		vec2 operator * (const float factor) const;
		vec2 operator / (const float factor) const;

		float operator * (const vec2& vector) const;

		vec2& operator += (const vec2& vector);
		vec2& operator -= (const vec2& vector);
		vec2& operator *= (const float factor);
		vec2& operator /= (const float factor);

		bool operator == (const float value);
		bool operator == (const vec2& vector);
		bool operator != (const vec2& vector);
	};
}