#include "vec4.h"
#include "vec2.h"
#include "vec3.h"

using namespace Uranium;

vec4::vec4(const vec4& vector)
	: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
{
}
vec4::vec4(const vec3& vector, float w)
	: x(vector.x), y(vector.y), z(vector.z), w(w)
{
}
vec4::vec4(const vec2& vector, float z, float w)
	: x(vector.x), y(vector.y), z(z), w(w)
{
}
vec4::vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}
vec4::vec4(float xyzw)
	: x(xyzw), y(xyzw), z(xyzw), w(xyzw)
{
}

float& vec4::operator [] (unsigned int index) {
	return *((float*)this + index);
}

vec4 vec4::operator - () {
	return vec4(-x, -y, -z, -w);
}

vec4 vec4::operator + (const vec4& vector) const {
	return vec4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

vec4 vec4::operator - (const vec4& vector) const {
	return vec4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

vec4 vec4::operator * (const float factor) const {
	return vec4(x * factor, y * factor, z * factor, w * factor);
}

vec4 vec4::operator / (const float factor) const {
	return vec4(x / factor, y / factor, z / factor, w / factor);
}

float vec4::operator * (const vec4& vector) const {
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

vec4& vec4::operator += (const vec4& vector) {
	x = x + vector.x;
	y = y + vector.y;
	z = z + vector.z;
	w = w + vector.w;
	return *this;
}
vec4& vec4::operator -= (const vec4& vector) {
	x = x - vector.x;
	y = y - vector.y;
	z = z - vector.z;
	w = w - vector.w;
	return *this;
}
vec4& vec4::operator *= (const float factor) {
	for (int i = 0; i < 4; i++)
		(*this)[i] *= factor;
	return *this;
}
vec4& vec4::operator /= (const float factor) {
	for (int i = 0; i < 4; i++)
		(*this)[i] /= factor;
	return *this;
}

bool vec4::operator == (const float value) {
	return value == x && value == y && value == z && value == w;
}

bool vec4::operator == (const vec4& vector) {
	return vector.x == x && vector.y == y && vector.z == z && vector.w == w;
}

bool vec4::operator != (const vec4& vector) {
	return !(*this == vector);
}