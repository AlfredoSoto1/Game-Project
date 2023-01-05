#define UR_OPENGL
#define UR_CONTENT_API
#include "Engine.h"

#include "Shader.h"
#include "ShaderProgram.h"
using namespace Uranium;

ShaderProgram::ShaderProgram(const Shader& _compShader) 
	: vertShader(0), fragShader(0)
{
	program = glCreateProgram();
	
	glAttachShader(program, _compShader);
	compShader = _compShader;

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

ShaderProgram::ShaderProgram(const Shader& _vertShader, const Shader& _fragShader)
	: compShader(0)
{
	program = glCreateProgram();

	glAttachShader(program, _vertShader);
	glAttachShader(program, _fragShader);

	vertShader = _vertShader;
	fragShader = _fragShader;

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

ShaderProgram::operator uint32() const {
	return program;
}

void ShaderProgram::bind() const {
	// start shader
	glUseProgram(program);
}

void ShaderProgram::unbind() const {
	// stop shader
	glUseProgram(0);
}

void ShaderProgram::dispatchCompute(uint32 groupX, uint32 groupY, uint32 groupZ, uint32 barrier) const {
	//GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT <-- barrier
	bind();
	glDispatchCompute(
		groupX > workGroupMaxCount[0] ? workGroupMaxCount[0] : groupX,
		groupY > workGroupMaxCount[1] ? workGroupMaxCount[1] : groupY,
		groupZ > workGroupMaxCount[2] ? workGroupMaxCount[2] : groupZ);
	glMemoryBarrier(barrier);
	unbind();
}


