#define GLFW_STATIC
#include <GL/glew.h>

#include "AccesibleShader.h"

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Maths/mat2.h"
#include "Utils/Maths/mat3.h"
#include "Utils/Maths/mat4.h"

using namespace Uranium;

Sampler AccesibleShader::getSampler(unsigned int _program, const char* _name) const {
	Sampler outSampler = glGetUniformLocation(_program, _name);
	print_warning(outSampler < 0, "Sampler Uniform not used.");
	return outSampler;
}

Uniform AccesibleShader::getUniform(unsigned int _program, const char* _name) const {
	Uniform outUniform = glGetUniformLocation(_program, _name);
	print_warning(outUniform <= 0, "Uniform not used.");
	return outUniform;
}

void AccesibleShader::setSampler(const Sampler& _sampler, unsigned int _samplerId) const {
	glUniform1i(_sampler, _samplerId);
}

void AccesibleShader::setVec2(Uniform _uniform, const vec2& _vec2) const {
	glUniform2f(_uniform, _vec2.x, _vec2.y);
}

void AccesibleShader::setVec3(Uniform _uniform, const vec3& _vec3) const {
	glUniform3f(_uniform, _vec3.x, _vec3.y, _vec3.z);
}

void AccesibleShader::setVec4(Uniform _uniform, const vec4& _vec4) const {
	glUniform4f(_uniform, _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void AccesibleShader::setMat2(Uniform _uniform, mat2& _mat2) const {
	glUniformMatrix2fv(_uniform, 1, GL_TRUE, _mat2);
}

void AccesibleShader::setMat3(Uniform _uniform, mat3& _mat3) const {
	glUniformMatrix3fv(_uniform, 1, GL_TRUE, _mat3);
}

void AccesibleShader::setMat4(Uniform _uniform, mat4& _mat4) const {
	glUniformMatrix4fv(_uniform, 1, GL_TRUE, _mat4);
}