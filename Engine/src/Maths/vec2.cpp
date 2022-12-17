#include "vec2.h"

using namespace Maths;

vec2::vec2() : vec() {
}

vec2::vec2(float xy) : vec() {
	component[0] = xy;
	component[1] = xy;
}

vec2::vec2(float x, float y) : vec() {
	component[0] = x;
	component[1] = y;
}

vec2::vec2(const vec2& vector) : vec(vector) {

}

vec2 vec2::operator - () {
	vec<2U, float> cpy = vec::operator-();
	return *(vec2*)(&cpy);
}

vec2 vec2::operator + (const vec2& vector) const {
	vec<2U, float> cpy = vec::operator+(vector);
	return *(vec2*)(&cpy);
}
vec2 vec2::operator - (const vec2& vector) const {
	vec<2U, float> cpy = vec::operator-(vector);
	return *(vec2*)(&cpy);
}
vec2 vec2::operator * (const float factor) const {
	vec<2U, float> cpy = vec::operator*(factor);
	return *(vec2*)(&cpy);
}
vec2 vec2::operator / (const float factor) const {
	vec<2U, float> cpy = vec::operator/(factor);
	return *(vec2*)(&cpy);
}

vec2& vec2::operator += (const vec2& vector) {
	vec::operator+=(vector);
	return *this;
}

vec2& vec2::operator -= (const vec2& vector) {
	vec::operator-=(vector);
	return *this;
}

vec2& vec2::operator *= (const float factor) {
	vec::operator*=(factor);
	return *this;
}

vec2& vec2::operator /= (const float factor) {
	vec::operator/=(factor);
	return *this;
}