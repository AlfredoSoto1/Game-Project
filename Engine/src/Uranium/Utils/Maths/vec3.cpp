#include "vec3.h"
#include "vec2.h"

using namespace Uranium;

vec3::vec3(float xyz)
	: x(xyz), y(xyz), z(xyz)
{
}
vec3::vec3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}
vec3::vec3(const vec3& vector)
	: x(vector.x), y(vector.y), z(vector.z)
{
}
vec3::vec3(const vec2& vector, float z)
	: x(vector.x), y(vector.y), z(z)
{
}

float& vec3::operator [] (unsigned int index) {
	return *((float*)this + index);
}

vec3 vec3::operator - () {
	return vec3(-x, -y, -z);
}

vec3 vec3::operator + (const vec3& vector) const {
	return vec3(x + vector.x, y + vector.y, z + vector.z);
}

vec3 vec3::operator - (const vec3& vector) const {
	return vec3(x - vector.x, y - vector.y, z - vector.z);
}

vec3 vec3::operator * (const float factor) const {
	return vec3(x * factor, y * factor, z * factor);
}

vec3 vec3::operator / (const float factor) const {
	return vec3(x / factor, y / factor, z / factor);
}

float vec3::operator * (const vec3& vector) const {
	return x * vector.x + y * vector.y + z * vector.z;
}

vec3& vec3::operator += (const vec3& vector) {
	x = x + vector.x;
	y = y + vector.y;
	z = z + vector.z;
	return *this;
}

vec3& vec3::operator -= (const vec3& vector) {
	x = x - vector.x;
	y = y - vector.y;
	z = z - vector.z;
	return *this;
}

vec3& vec3::operator *= (const float factor) {
	for (int i = 0; i < 3; i++)
		(*this)[i] *= factor;
	return *this;
}

vec3& vec3::operator /= (const float factor) {
	for (int i = 0; i < 3; i++)
		(*this)[i] /= factor;
	return *this;
}

vec3 vec3::operator | (const vec3& vector) {
	return vec3(
		y * vector.z - z * vector.y,
		z * vector.x - x * vector.z,
		x * vector.y - y * vector.x);
}

bool vec3::operator == (const float value) {
	return value == x && value == y && value == z;
}

bool vec3::operator == (const vec3& vector) {
	return vector.x == x && vector.y == y && vector.z == z;
}

bool vec3::operator != (const vec3& vector) {
	return !(*this == vector);
}