#include "vec3.h"

using namespace Maths;

vec3::vec3() : vec() {
}

vec3::vec3(float xyz) : vec() {
	component[0] = xyz;
	component[1] = xyz;
	component[2] = xyz;
}

vec3::vec3(float x, float y, float z) : vec() {
	component[0] = x;
	component[1] = y;
	component[2] = z;
}

vec3::vec3(const vec3& vector) : vec(vector) {

}

vec3 vec3::operator - () {
	vec<3U, float> cpy = vec::operator-();
	return *(vec3*)(&cpy);
}

vec3 vec3::operator + (const vec3& vector) const {
	vec<3U, float> cpy = vec::operator+(vector);
	return *(vec3*)(&cpy);
}
vec3 vec3::operator - (const vec3& vector) const {
	vec<3U, float> cpy = vec::operator-(vector);
	return *(vec3*)(&cpy);
}
vec3 vec3::operator * (const float factor) const {
	vec<3U, float> cpy = vec::operator*(factor);
	return *(vec3*)(&cpy);
}

vec3 vec3::operator / (const float factor) const {
	vec<3U, float> cpy = vec::operator/(factor);
	return *(vec3*)(&cpy);
}

vec3& vec3::operator += (const vec3& vector) {
	vec::operator+=(vector);
	return *this;
}

vec3& vec3::operator -= (const vec3& vector) {
	vec::operator-=(vector);
	return *this;
}

vec3& vec3::operator *= (const float factor) {
	vec::operator*=(factor);
	return *this;
}

vec3& vec3::operator /= (const float factor) {
	vec::operator/=(factor);
	return *this;
}