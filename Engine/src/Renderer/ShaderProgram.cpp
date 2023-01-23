#include "ShaderProgram.h"

#define GLEW_STATIC
#include <GL/glew.h>

#define CATCH_OPENGL_ERROR
#include "UraniumApi.h"

#include "Shader.h"

using namespace Uranium;

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> _computeShader) 
	: vertShader(0), fragShader(0)
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
	: compShader(0)
{
	program = glCreateProgram();

	glAttachShader(program, *_vertexShader);	// attach vertex shader
	glAttachShader(program, *_fragmentShader);	// attach fragment shader

	vertShader = *_vertexShader;
	fragShader = *_fragmentShader;

	// link and validate program
	glLinkProgram(program);
	glValidateProgram(program);
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

unsigned int ShaderProgram::getMaxCharUniform() {
	return maxCharUniform;
}

unsigned int ShaderProgram::getAvailableUniformCount() {
	return availableUniformCount;
}

ShaderProgram::operator unsigned int() const {
	return program;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getUniformFlags() {
	return uniformFlags;
}

std::unordered_map<std::string, std::pair<int, unsigned int>>& ShaderProgram::getUniformSamplers() {
	return uniformSamplers;
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
		if (type == GL_SAMPLER_2D) {
			uniformSamplers[name] = { glGetUniformLocation(program, name), type };
		}
		else {
			uniformFlags[name] = { glGetUniformLocation(program, name), type };
		}
	}
	unbind();

	delete[] name;
}

