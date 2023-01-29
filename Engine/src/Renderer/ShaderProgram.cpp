#include "ShaderProgram.h"

#define GLEW_STATIC
#include <GL/glew.h>

#define CATCH_OPENGL_ERROR
#include "UraniumApi.h"

#include "Shader.h"
#include "Texture.h"

#include "Utils/Maths/vec2.h"
#include "Utils/Maths/vec3.h"
#include "Utils/Maths/vec4.h"

#include "Utils/Maths/mat2.h"
#include "Utils/Maths/mat3.h"
#include "Utils/Maths/mat4.h"

using namespace Uranium;

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> _computeShader) 
	: vertShader(0), fragShader(0), availableUniformCount(0)
{
	program = glCreateProgram();

	glAttachShader(program, *_computeShader); // attach compute shader

	compShader = *_computeShader;

	// link and validate program
	glLinkProgram(program);
	glValidateProgram(program);

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workGroupMaxCount[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workGroupMaxCount[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workGroupMaxCount[2]);

	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workGroupMaxSize[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workGroupMaxSize[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workGroupMaxSize[2]);

	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workGroupInvocations);
}

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> _vertexShader, std::shared_ptr<Shader> _fragmentShader) 
	: compShader(0), availableUniformCount(0)
{
	program = glCreateProgram();

	glAttachShader(program, *_vertexShader);	// attach vertex shader
	glAttachShader(program, *_fragmentShader);	// attach fragment shader

	vertShader = *_vertexShader;
	fragShader = *_fragmentShader;

	// link and validate program
	glLinkProgram(program);
	glValidateProgram(program);

	viewMatrix = -1;
	projectionMatrix = -1;
	transformationMatrix = -1;

	containsViewMatrix = false;
	containsProjectionMatrix = false;
	containsTransformationMatrix = false;
	constainsColor = false;
	containsAlbedoSampler = false;
	containsNormalSampler = false;
	containsSpecularSampler = false;

	readAvailableUniforms();
}

ShaderProgram::~ShaderProgram() {
	// detach /delete shaders
	if (compShader != 0) {
		glDetachShader(program, compShader);
		glDeleteShader(compShader);
	}
	if (vertShader != 0) {
		glDetachShader(program, vertShader);
		glDeleteShader(vertShader);
	}
	if (fragShader != 0) {
		glDetachShader(program, fragShader);
		glDeleteShader(fragShader);
	}

	// delete shader program
	glDeleteProgram(program);
}

ShaderProgram::operator unsigned int() const {
	return program;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getVec2_fs() {
	return vec2_f;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getVec3_fs() {
	return vec3_f;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getVec4_fs() {
	return vec4_f;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getMat2_fs() {
	return mat2_f;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getMat3_fs() {
	return mat3_f;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getMat4_fs() {
	return mat4_f;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getSampler_2ds() {
	return sampler_2d;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getSampler_3ds() {
	return sampler_3d;
}

bool ShaderProgram::hasViewMatrix() {
	return containsViewMatrix;
}

bool ShaderProgram::hasProjectionMatrix() {
	return containsProjectionMatrix;
}

bool ShaderProgram::hasTransformationMatrix() {
	return containsTransformationMatrix;
}

bool ShaderProgram::hasColor() {
	return constainsColor;
}

bool ShaderProgram::hasAlbedoSampler() {
	return containsAlbedoSampler;
}

bool ShaderProgram::hasNormalSampler() {
	return containsNormalSampler;
}

bool ShaderProgram::hasSpecularSampler() {
	return containsSpecularSampler;
}

void ShaderProgram::setViewMatrix(mat4& _mat4) const {
	glUniformMatrix4fv(viewMatrix, 1, GL_TRUE, _mat4);
}

void ShaderProgram::setProjectionMatrix(mat4& _mat4) const {
	glUniformMatrix4fv(projectionMatrix, 1, GL_TRUE, _mat4);
}

void ShaderProgram::setTransformationMatrix(mat4& _mat4) const {
	glUniformMatrix4fv(transformationMatrix, 1, GL_TRUE, _mat4);
}

void ShaderProgram::setColor(const vec4& _color) {
	glUniform4f(color, _color.x, _color.y, _color.z, _color.w);
}

void ShaderProgram::setAlbedoSampler(std::shared_ptr<Texture> _albedo, int _bindingId) {
	glUniform1i(albedoSampler, _bindingId);
}

void ShaderProgram::setNormalSampler(std::shared_ptr<Texture> _normal, int _bindingId) {
	glUniform1i(color, *_normal);
}

void ShaderProgram::setSpecularSampler(std::shared_ptr<Texture> _specular, int _bindingId) {
	glUniform1i(color, *_specular);
}

void ShaderProgram::bind() const {
	glUseProgram(program);
}

void ShaderProgram::unbind() const {
	glUseProgram(0);
}
//
//void ShaderProgram::dispatchCompute(unsigned int _groupX, unsigned int _groupY, unsigned int _groupZ, unsigned int _barrier) const {
//	//GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT <-- barrier
//	bind();
//	glDispatchCompute(
//		_groupX > workGroupMaxCount[0] ? workGroupMaxCount[0] : _groupX,
//		_groupY > workGroupMaxCount[1] ? workGroupMaxCount[1] : _groupY,
//		_groupZ > workGroupMaxCount[2] ? workGroupMaxCount[2] : _groupZ);
//	glMemoryBarrier(_barrier);
//	unbind();
//}

void ShaderProgram::readAvailableUniforms() {
	// get current active uniforms
	GLint uniformCount;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);

	availableUniformCount = uniformCount;

	// gets max length of uniform name in program
	GLint maxCharLength;
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxCharLength);

	maxCharUniform = maxCharLength;

	GLint size;
	GLint length;
	GLuint type;

	GLchar* name = new GLchar[maxCharLength];

	bind();
	// get uniform location, uniform name and type
	for (GLuint i = 0; i < uniformCount; i++) {
		glGetActiveUniform(program, i, maxCharLength, &length, &size, &type, name);

		Uniform location = glGetUniformLocation(program, name);

		switch (type) {
		case GL_FLOAT_VEC2: 
			vec2_f[name] = { location, type }; 
			break;
		case GL_FLOAT_VEC3:
			vec3_f[name] = { location, type };
			break;
		case GL_FLOAT_VEC4: 
			vec4_f[name] = { location, type }; 
			if (name == "color") {
				color = location;
				constainsColor = true;
			}
			break;
		case GL_FLOAT_MAT2:
			mat2_f[name] = { location, type }; 
			break;
		case GL_FLOAT_MAT3: 
			mat3_f[name] = { location, type }; 
			break;
		case GL_FLOAT_MAT4: 
			mat4_f[name] = { location, type }; 
			if (name == "viewMatrix") {
				viewMatrix = location;
				containsViewMatrix = true;
			}
			else if (name == "projectionMatrix") {
				projectionMatrix = location;
				containsProjectionMatrix = true;
			}
			break;
		case GL_SAMPLER_2D: 
			sampler_2d[name] = { location, type }; 
			if (name == "albedoSampler") {
				albedoSampler = location;
				containsAlbedoSampler = true;
			}
			else if (name == "normalSampler") {
				normalSampler = location;
				containsNormalSampler = true;
			}
			else if (name == "specularSampler") {
				specularSampler = location;
				containsSpecularSampler = true;
			}
			break;
		case GL_SAMPLER_3D: 
			sampler_3d[name] = { location, type };
			break;
		}
	}
	unbind();

	delete[] name;
}

void ShaderProgram::setSampler(const Sampler& _sampler, unsigned int _samplerId) const {
	glUniform1i(_sampler, _samplerId);
}

void ShaderProgram::setVec2(Uniform _uniform, const vec2& _vec2) const {
	glUniform2f(_uniform, _vec2.x, _vec2.y);
}

void ShaderProgram::setVec3(Uniform _uniform, const vec3& _vec3) const {
	glUniform3f(_uniform, _vec3.x, _vec3.y, _vec3.z);
}

void ShaderProgram::setVec4(Uniform _uniform, const vec4& _vec4) const {
	glUniform4f(_uniform, _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void ShaderProgram::setMat2(Uniform _uniform, mat2& _mat2) const {
	glUniformMatrix2fv(_uniform, 1, GL_TRUE, _mat2);
}

void ShaderProgram::setMat3(Uniform _uniform, mat3& _mat3) const {
	glUniformMatrix3fv(_uniform, 1, GL_TRUE, _mat3);
}

void ShaderProgram::setMat4(Uniform _uniform, mat4& _mat4) const {
	glUniformMatrix4fv(_uniform, 1, GL_TRUE, _mat4);
}
