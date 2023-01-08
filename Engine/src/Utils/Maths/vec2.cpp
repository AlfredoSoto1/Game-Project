#include "vec2.h"

using namespace Uranium;

vec2::vec2(float xy)
	: x(xy), y(xy)
{
}

vec2::vec2(float x, float y)
	: x(x), y(y)
{
}

vec2::vec2(const vec2& vector)
	: x(vector.x), y(vector.y)
{
}

float& vec2::operator [] (unsigned int index) {
	return *((float*)this + index);
}

vec2 vec2::operator - () {
	return vec2(-x, -y);
}

vec2 vec2::operator + (const vec2& vector) const {
	return vec2(x + vector.x, y + vector.y);
}

vec2 vec2::operator - (const vec2& vector) const {
	return vec2(x - vector.x, y - vector.y);
}

vec2 vec2::operator * (const float factor) const {
	return vec2(x * factor, y * factor);
}

vec2 vec2::operator / (const float factor) const {
	return vec2(x / factor, y / factor);
}

float vec2::operator * (const vec2& vector) const {
	return x * vector.x + y * vector.y;
}

vec2& vec2::operator += (const vec2& vector) {
	x = x + vector.x;
	y = y + vector.y;
	return *this;
}

vec2& vec2::operator -= (const vec2& vector) {
	x = x - vector.x;
	y = y - vector.y;
	return *this;
}

vec2& vec2::operator *= (const float factor) {
	for (int i = 0; i < 2; i++)
		(*this)[i] *= factor;
	return *this;
}

vec2& vec2::operator /= (const float factor) {
	for (int i = 0; i < 2; i++)
		(*this)[i] /= factor;
	return *this;
}

bool vec2::operator == (const float value) {
	return value == x && value == y;
}

bool vec2::operator == (const vec2& vector) {
	return vector.x == x && vector.y == y;
}

bool vec2::operator != (const vec2& vector) {
	return !(*this == vector);
}