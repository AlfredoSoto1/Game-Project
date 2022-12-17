#include "vec4.h"

using namespace Maths;


vec4::vec4() : vec() {
}

vec4::vec4(float xyzw) : vec() {
	component[0] = xyzw;
	component[1] = xyzw;
	component[2] = xyzw;
	component[3] = xyzw;
}

vec4::vec4(float x, float y, float z, float w) : vec() {
	component[0] = x;
	component[1] = y;
	component[2] = z;
	component[3] = w;
}

vec4::vec4(const vec4& vector) : vec(vector) {

}

vec4 vec4::operator - () {
	vec<4U, float> cpy = vec::operator-();
	return *(vec4*)(&cpy);
}

vec4 vec4::operator + (const vec4& vector) const {
	vec<4U, float> cpy = vec::operator+(vector);
	return *(vec4*)(&cpy);
}
vec4 vec4::operator - (const vec4& vector) const {
	vec<4U, float> cpy = vec::operator-(vector);
	return *(vec4*)(&cpy);
}
vec4 vec4::operator * (const float factor) const {
	vec<4U, float> cpy = vec::operator*(factor);
	return *(vec4*)(&cpy);
}

vec4 vec4::operator / (const float factor) const {
	vec<4U, float> cpy = vec::operator/(factor);
	return *(vec4*)(&cpy);
}

vec4& vec4::operator += (const vec4& vector) {
	vec::operator+=(vector);
	return *this;
}

vec4& vec4::operator -= (const vec4& vector) {
	vec::operator-=(vector);
	return *this;
}

vec4& vec4::operator *= (const float factor) {
	vec::operator*=(factor);
	return *this;
}

vec4& vec4::operator /= (const float factor) {
	vec::operator/=(factor);
	return *this;
}