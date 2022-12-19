#pragma once

namespace Maths {
	float sqrt(float number);
	float inv_sqrt(float number);

	double toDegree(double radian);
	double toRadians(double degree);

	float toDegree(float radian);
	float toRadians(float degree);

	struct vec2;
	struct vec3;
	struct vec4;

	float lengthSquared(const vec2& vector);
	float lengthSquared(const vec3& vector);
	float lengthSquared(const vec4& vector);
	
	float length(const vec2& vector);
	float length(const vec3& vector);
	float length(const vec4& vector);
	
	float invLength(const vec2& vector);
	float invLength(const vec3& vector);
	float invLength(const vec4& vector);
	
	float dot(const vec2& vector1, const vec2& vector2);
	float dot(const vec3& vector1, const vec3& vector2);
	float dot(const vec4& vector1, const vec4& vector2);
	
	vec3 cross(const vec3& vector1, const vec3& vector2);
	
	void negate(vec2* vector);
	void negate(vec3* vector);
	void negate(vec4* vector);
	
	vec2 negate(const vec2& vector);
	vec3 negate(const vec3& vector);
	vec4 negate(const vec4& vector);
	
	void normalize(vec2* vector);
	void normalize(vec3* vector);
	void normalize(vec4* vector);
	
	vec2 normalize(const vec2& vector);
	vec3 normalize(const vec3& vector);
	vec4 normalize(const vec4& vector);
	
	vec2 projection(vec2& vector1, vec2& vector2);
	float component(vec2& vector1, vec2& vector2);
	
	vec3 getNormal(const vec3& point1, const vec3& point2, const vec3& point3);

	struct mat2;
	struct mat3;
	struct mat4;

	void zero(mat2* matrix);
	void zero(mat3* matrix);
	void zero(mat4* matrix);

	void set(float value, mat2* matrix);
	void set(float value, mat3* matrix);
	void set(float value, mat4* matrix);

	void identity(mat2* matrix);
	void identity(mat3* matrix);
	void identity(mat4* matrix);

	void subMatOf(mat3& matrix, unsigned int row, unsigned int col, mat2* dest);
	void subMatOf(mat4& matrix, unsigned int row, unsigned int col, mat3* dest);

	float determinantOf(mat2& matrix);
	float determinantOf(mat3& matrix);
	float determinantOf(mat4& matrix);

	mat2 transpose(mat2& matrix);
	mat3 transpose(mat3& matrix);
	mat4 transpose(mat4& matrix);

	mat2 inverse(mat2& matrix);
	mat3 inverse(mat3& matrix);
	mat4 inverse(mat4& matrix);

	void rotate(mat4& src, mat4* dest, float angle, const vec3& axis);

	void scale(mat4& src, mat4* dest, const vec3& scaleVector);
	void translate(mat4& src, mat4* dest, const vec3& position);

	void project(mat4* projectionMatrix, double farDistance, double nearDistance, double fov, double width, double height);

	void transform(mat4* transformationMatrix, const vec3& position, const vec3& rotation, const vec3& scale);
}